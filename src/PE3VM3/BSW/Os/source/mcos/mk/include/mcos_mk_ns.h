/*
    Copyright (C) 2016 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_mk_ns.h ] - eMCOS/MK name service local header
****************************************************************************/
#ifndef MCOS_MK_NS_H
#define MCOS_MK_NS_H

#if !MCOS_AUTOSAR

#include "mcos_mk.h"

/* Name Service configuration structure */
typedef struct
{
    mcos_id_t hwclid;      /* HWCL id of this NS */
    mcos_id_t rcidx;       /* relative core index */
    uint16_t  nent;        /* up to 65535 entries */
    uint16_t  attr;        /* attribites */
} mcos_ns_cfg_t;

/* Shared cluster Name Cache configuration structure */
typedef struct
{
    mcos_id_t nsid;        /* Manager nsid (no cache if 0) */
    uint16_t  nent;        /* Cache entries (power of 2) */
} mcos_dnc_cfg_t;

/* Number of defined Name Servers */
extern const uint32_t mcos_ns_server_num;
#define MCOS_NS_SERVER_NUM  mcos_ns_server_num

/* Static config array */
extern const mcos_ns_cfg_t mcos_ns_cfg[MCOS_NS_NUM];

/* Run-time filled Name Servers IDs */
extern volatile uint32_t mcos_ns_tid[sizeof(mcos_ns_cfg)/sizeof(mcos_ns_cfg[0])];

/* Get Name Server lcid from zero-based server index */
MCOS_INLINE mcos_id_t nscfg_getServerLcid(int32_t i)
{
    return MCOS_HWCL_RCIDX2LCID(mcos_ns_cfg[i].hwclid, mcos_ns_cfg[i].rcidx);
}

/* Get Name Server hwclid from zero-based server index */
MCOS_INLINE mcos_id_t nscfg_getServerHwclid(int32_t i)
{
    return mcos_ns_cfg[i].hwclid;
}

/* Get Name Server rcidx from zero-based server index */
MCOS_INLINE mcos_id_t nscfg_getServerRcidx(int32_t i)
{
    return mcos_ns_cfg[i].rcidx;
}

/* Get Name Server TID from 1-based server NSID */
MCOS_INLINE mcos_erid_t mcos_ns_server_getid(mcos_id_t nsid)
{
 /* Argument should be checked by API caller */
    return (mcos_erid_t)mcos_hwl_coherent_load32(&mcos_ns_tid[nsid - 1]);
}

/* Set Name Server TID with 1-based server NSID */
MCOS_INLINE void mcos_ns_server_setid(mcos_id_t nsid, mcos_id_t tid)
{
 /* Argument should be checked by API caller */
    mcos_hwl_coherent_store32(&mcos_ns_tid[nsid - 1], (uint32_t)tid);
}

/* Get tid by name */
mcos_erid_t mcos_thread_getid_by_name_internal(const mcos_char_t* name);

/* Regsater name */
mcos_er_t mcos_name_register_internal(const mcos_char_t* name, mcos_generic_id_t id, mcos_id_t nsid);

mcos_er_t mcos_name_unregister_internal(const mcos_char_t* name, mcos_id_t nsid);
mcos_generic_id_t mcos_name_lookup_internal(const mcos_char_t* name, mcos_id_t nsid);

#endif /* !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_MK_NS_H */
