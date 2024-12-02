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
[ ehvm_chip_cpp_impl.h ] - RH850U2A implementation header file
****************************************************************************/
#ifndef EHVM_CHIP_CPP_IMPL_H
#define EHVM_CHIP_CPP_IMPL_H

/* Timer Array Unit Base Address */
#define TAUDN_BASE(n)   ((0xFFBF4000) + ((n) * 0x1000))
#define TAUJN_BASE(n)   ((0xFFBF7000) + ((n) * 0x0200))

#endif /* #ifndef EHVM_CHIP_CPP_IMPL_H */
