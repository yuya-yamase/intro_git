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
[ mcos_heapsrv.h ] - MCOS heap server header
****************************************************************************/
#ifndef MCOS_HEAPSRV_H
#define MCOS_HEAPSRV_H

#include "mcos_mk.h"
#include "mcos_heap_align.h"
#include <mcos/mcos_syssrv.cfg>

#if MCOS_CFG_HEAPSRV_ENABLE != 0

/* heap method table (client request) */
typedef struct
{
    /* function to allcate from server */
    void * (* allocate)(mcos_id_t servid, size_t size);

    /* function to free to server */
    void (* free)(mcos_id_t servid, void * addr);

    /* function to reference server */
    mcos_er_t (* reference)(mcos_id_t servid, mcos_heap_mem_info_t * mem_ref);

    /* function to debug server */
    void (* debug)(mcos_id_t servid);
} heap_server_request_t;

/* create heap management server thread */
void mcos_heapsrv_create_server (const mkcb_t *mkcb);

/* delete heap management server thread */
void mcos_heapsrv_delete_server (void);

/* get server request vtbl */
const heap_server_request_t * mcos_heapsrv_get_request (void);

#endif /* #if MCOS_CFG_HEAPSRV_ENABLE != 0 */

#endif /* #ifndef MCOS_HEAPSRV_H */
