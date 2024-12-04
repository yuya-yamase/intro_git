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
[ ehvm_bios_cmn_impl.h ] - BIOS common definitions for implementations
****************************************************************************/
#ifndef EHVM_BIOS_CMN_IMPL_H
#define EHVM_BIOS_CMN_IMPL_H

#include <bios/ehvm_bios.h>
#include <bios/ehvm_bios_basic_impl.h>
#include <bios/ehvm_bios_dep_impl.h>

/* initialize BIOS HW for slave core (later ver.2.2 rev0) */
extern void ehvm_bios_hw_initialize_slave(void);

/* initialize BIOS HW for master core (later ver2.2 rev0) */
extern void ehvm_bios_hw_initialize_master(void);

#endif /* #ifndef EHVM_BIOS_CMN_IMPL_H */
