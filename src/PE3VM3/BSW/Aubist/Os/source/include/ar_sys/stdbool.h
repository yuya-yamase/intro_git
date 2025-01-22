/*
    Copyright (C) 2016 By eSOL Co.,Ltd. Tokyo, Japan

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
[stdbool.h] - C99 boolean types header
****************************************************************************/
#ifndef STDBOOL_H_AUTOSAR
#define STDBOOL_H_AUTOSAR

#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined   1

#ifndef __cplusplus

#define bool    _Bool
#define true    1
#define false   0

#endif /* #ifndef __cplusplus */

#endif /* #ifndef __bool_true_false_are_defined */

#endif /* #ifndef STDBOOL_H_AUTOSAR */
