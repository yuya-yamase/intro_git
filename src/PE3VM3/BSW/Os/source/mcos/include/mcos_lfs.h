/*
    Copyright (C) 2013 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_lfs.h ] - LFS definitions
****************************************************************************/
#ifndef MCOS_LFS_H
#define MCOS_LFS_H

#include "mcos_cmn.h"

#include <mcos_lfs_limits.h>
#include <posix/lfs.cfg>        /* public configuration */

#if (MCOS_CFG_LFS_FILE_NUM < MCOS_LFS_FILE_NUM_MIN)
#error MCOS_CFG_LFS_FILE_NUM is too small.
#endif
#if (MCOS_CFG_LFS_FILE_NUM > MCOS_LFS_FILE_NUM_MAX)
#error MCOS_CFG_LFS_FILE_NUM is too large.
#endif

#if MCOS_CFG_LFS_USE_DEV_PFS

#if (MCOS_CFG_LFS_PFS_NUM < MCOS_LFS_PFS_NUM_MIN)
#error MCOS_CFG_LFS_PFS_NUM is too small.
#endif
#if (MCOS_CFG_LFS_PFS_NUM > MCOS_LFS_PFS_NUM_MAX)
#error MCOS_CFG_LFS_PFS_NUM is too large.
#endif

#endif /* #if MCOS_CFG_LFS_USE_DEV_PFS */

#if (MCOS_CFG_LFS_USE_IP_SOCKETS || MCOS_CFG_LFS_USE_UNIX_SOCKETS)

#if (MCOS_CFG_LFS_SOCKET_NUM < MCOS_LFS_SOCKET_NUM_MIN)
#error MCOS_CFG_LFS_SOCKET_NUM is too small.
#endif
#if (MCOS_CFG_LFS_SOCKET_NUM > MCOS_LFS_SOCKET_NUM_MAX)
#error MCOS_CFG_LFS_SOCKET_NUM is too large.
#endif

#endif /* #if (MCOS_CFG_LFS_USE_IP_SOCKETS || MCOS_CFG_LFS_USE_UNIX_SOCKETS) */

#if MCOS_CFG_LFS_PIPE_NUM

#if (MCOS_CFG_LFS_PIPE_NUM < MCOS_LFS_PIPE_NUM_MIN)
#error MCOS_CFG_LFS_PIPE_NUM is too small.
#endif
#if (MCOS_CFG_LFS_PIPE_NUM > MCOS_LFS_PIPE_NUM_MAX)
#error MCOS_CFG_LFS_PIPE_NUM is too large.
#endif

#endif /* #if MCOS_CFG_LFS_PIPE_NUM */

#if MCOS_CFG_LFS_SHMEM_NUM

#if (MCOS_CFG_LFS_SHMEM_NUM < MCOS_LFS_SHMEM_NUM_MIN)
#error MCOS_CFG_LFS_SHMEM_NUM is too small.
#endif
#if (MCOS_CFG_LFS_SHMEM_NUM > MCOS_LFS_SHMEM_NUM_MAX)
#error MCOS_CFG_LFS_SHMEM_NUM is too large.
#endif

#endif /* #if MCOS_CFG_LFS_SHMEM_NUM */

void lfs_create_server(const mkcb_t *mkcb);

#endif /* #ifndef MCOS_LFS_H */
