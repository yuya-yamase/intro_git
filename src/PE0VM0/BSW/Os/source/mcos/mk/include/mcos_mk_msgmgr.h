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
[ mcos_mk_msgmgr.h ] - eMCOS/MK core local scheduler local header
****************************************************************************/
#ifndef MCOS_MK_MSGMGR_H
#define MCOS_MK_MSGMGR_H

#if !MCOS_AUTOSAR

#include <mcos/system.cfg>
#include <mcos/mcos_hwcl.cfg>
#include "mcos_mk.h"

#define MRC_HWCL_TID_MASK       (0xffffUL)
#define MRC_HWCL_LCID_SHIFT     (16U)
#define MRC_HWCL_DATA_NONE      (0U)

MCOS_INLINE void consume_pending_requests(const mkcb_t *mkcb, clscb_t *clscb);
MCOS_INLINE void msgm_set_dstlcid(const mkcb_t *mkcb, mcos_id_t tid, mcos_id_t lcid);
MCOS_INLINE void set_dstlcid(msgmcb_t *msgmcb, mcos_id_t tid, mcos_id_t lcid);

MCOS_INLINE void
consume_pending_requests(const mkcb_t *mkcb, clscb_t *clscb)
{
    bios_int_t sr;

    sr = bios_cpu_lockInt();
    while (clscb->clsreq != 0)
    {
        msg_t *msg;

        /* get cls pending message */
        msg = clscb->clsreq;
        clscb->clsreq = msg->next;
        msg->next = 0;
        bios_cpu_unlockInt(sr);

        sr = bios_cpu_lockInt();
        /* do cls */
        mcos_cls_accept_message(mkcb, msg->data, msg->size, 0);

        /* release message */
        mcos_memm_release_message(mkcb, msg);
    }
    bios_cpu_unlockInt(sr);
}

 /*---------------------------------------------------------------------------
  msgm_set_dstlcid
     set destination core id
  Input     :   mkcb    control block
            :   tid     thread id
            :   lcid    core id
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE void
msgm_set_dstlcid(const mkcb_t *mkcb, mcos_id_t tid, mcos_id_t lcid)
{
    msgmcb_t *msgmcb;

    msgmcb = mcos_mkcc_get_msgmcb(mkcb);
    set_dstlcid(msgmcb, tid, lcid);
}

 /*---------------------------------------------------------------------------
  set_dstlcid
     set lcid by tid
  Input     :   tid     thread id
  Output    :   none
  Return    :   core id
  Note  :   none
 ---------------------------------------------------------------------------*/
MCOS_INLINE void
set_dstlcid(msgmcb_t *msgmcb, mcos_id_t tid, mcos_id_t lcid)
{
#if MCOS_HWCL
    if (lcid == LCID_NONE)
    {
        /* clear the MRC entry */
        if (mcos_util_tid_to_hwclid(tid) != MCOS_CFG_HWCL_ID)
        {
            /* target thread is in the other-cluster (tid is always migratable) */
            int32_t i;
            for (i = 0; i < MCOS_CFG_GLB_HWCL_MAX; ++i)
            {
                if ((msgmcb->mrc_hwcl_data[i] & MRC_HWCL_TID_MASK) == (uint32_t)tid)
                {
                    msgmcb->mrc_hwcl_data[i] = MRC_HWCL_DATA_NONE;
                }
            }
        }
        else
        {
            /* target thread is in the self-cluster */
            if (tid >= HWCL_BASE_MTID)
            {
                /* target thread is migratable */
                msgmcb->mrc[mcos_util_tid_to_tindex(tid)] = LCID_NONE;
            }
        }
    }
    else
    {
        /* set the MRC entry */
        if (LCID2HWCLID_NC(lcid) != MCOS_CFG_HWCL_ID)
        {
            /* target thread is in the other-cluster (tid is always migratable) */
            msgmcb->mrc_hwcl_data[msgmcb->mrc_hwcl_index] = ((uint32_t)lcid << MRC_HWCL_LCID_SHIFT) | (uint32_t)tid;
            msgmcb->mrc_hwcl_index = (msgmcb->mrc_hwcl_index + 1) % MCOS_CFG_GLB_HWCL_MAX;
        }
        else
#endif /* MCOS_HWCL */
        {
            /* target thread is in the self-cluster */
            if (tid >= HWCL_BASE_MTID)
            {
                /* target thread is migratable */
                msgmcb->mrc[mcos_util_tid_to_tindex(tid)] = lcid;
            }
        }
#if MCOS_HWCL
    }
#endif /* MCOS_HWCL */
}

#endif /* #if !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_MK_MSGMGR_H */
