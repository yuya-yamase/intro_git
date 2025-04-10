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
[ ehvm_bios_cpp_impl.h ] - BIOS RH850 imprementation
****************************************************************************/
#ifndef EHVM_BIOS_CPP_IMPL_H
#define EHVM_BIOS_CPP_IMPL_H

#define BIOS_RH850U2A_TMR_LENGTH_MAX    0xFFFFFFFF

#define ehvm_bios_rh850u2a_barrier_SYNC_CINIT         0x01
#define ehvm_bios_rh850u2a_barrier_SYNC_EHVM_BOOT     0x02
#define ehvm_bios_rh850u2a_barrier_SYNC_AR_SLAVE      0x03
#define ehvm_bios_rh850u2a_barrier_SYNC_BIOS_INIT     0x04

#endif /* #ifndef EHVM_BIOS_CPP_IMPL_H */
