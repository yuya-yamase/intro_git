/*
    Copyright (C) 2012 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_ns_defs.h] - MCOS Name Service definitions
****************************************************************************/
#ifndef MCOS_NS_DEFS_H
#define MCOS_NS_DEFS_H

#include "mcos_basic.h"
#include "mcos/mcos_ns_id.h"

/* Lookup name in NS store (Internal API) */
mcos_erid_t mcos_ns_store_lookup(const char* name, mcos_id_t nsid);

/* Add a thread name to NS store (Internal API)*/
mcos_er_t mcos_ns_store_add(const char* name, mcos_id_t tid, mcos_id_t nsid);

/* Delete a thread name from NS store (Intrnal API) */
mcos_er_t mcos_ns_store_del(const char* name, mcos_id_t tid, mcos_id_t nsid);

/* Update a thread name in NS store (Internal API) */
mcos_er_t mcos_ns_store_update(const char* name, mcos_id_t tid, mcos_id_t nsid);

/* Initialization */
void mcos_create_name_server(mcos_id_t lcid);

#endif /* #ifndef MCOS_NS_DEFS_H */
