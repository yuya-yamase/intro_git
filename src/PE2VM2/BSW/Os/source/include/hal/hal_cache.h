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
[ hal_cache.h ] - HAL cache interfaces
****************************************************************************/
#ifndef HAL_CACHE_H
#define HAL_CACHE_H

#include <hal/hal_basic.h>

/* flush cache */
void hal_cache_flush(
    hal_uint_t addr,
    hal_uint_t size);

/* invalidate data cache */
void hal_cache_invalidate(
    hal_uint_t addr,
    hal_uint_t size);

/* purge data cache */
void hal_cache_purge(
    hal_uint_t addr,
    hal_uint_t size);

/* write-back data cache */
void hal_cache_writeback(
    hal_uint_t addr,
    hal_uint_t size);

#endif /* #ifndef HAL_CACHE_H */
