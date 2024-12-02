/*
    Copyright (C) 2018 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_kprof.h] - MCOS kernel profile API interface header
****************************************************************************/
#ifndef MCOS_KPROF_H
#define MCOS_KPROF_H

#include "mcos/mcos.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    uint32_t max_used_stksz;
} mcos_kprof_thrstk_info_t;

mcos_er_t mcos_kprof_threadstack_get_info(mcos_id_t tid, mcos_kprof_thrstk_info_t *thrstk_info);

#ifdef __cplusplus
}
#endif

#endif /* MCOS_KPROF_H */
