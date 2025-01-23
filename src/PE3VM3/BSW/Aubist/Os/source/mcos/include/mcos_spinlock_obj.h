/*
    Copyright (C) 2022 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_spinlock_obj.h] - MCOS spinlock object header
****************************************************************************/
#ifndef MCOS_SPINLOCK_OBJ_H
#define MCOS_SPINLOCK_OBJ_H

#include "mcos_basic.h"

#if defined __V850__
#include "arch/v850/mcos_spinlock_obj_v850.h"

#elif defined __arm__ /* defined __V850__ */
#if defined __ghs__
#include "arch/armv7m/mcos_spinlock_obj_armv7m.h" /* for arm-ghs */

#elif defined __ARMCC_VERSION /* #if defined __ghs__ */
#if __ARMCC_VERSION >= 6000000U
#include "arch/armv8r/mcos_spinlock_obj_armv8r.h" /* for armclang */

#else /* #if __ARMCC_VERSION >= 6000000U */
#endif /* #else */

#endif /* #elif defined __ARMCC_VERSION */

#elif defined __Tricore /* #elif defined __arm__ */

#else /* #elif defined __Tricore */

#endif /* #else */



#endif /* #ifndef MCOS_SPINLOCK_OBJ_H */

