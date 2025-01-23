/*
    Copyright (C) 2019 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_mk_dsm.h ] - eMCOS/MK Distributed Shared Memory local header
****************************************************************************/
#ifndef MCOS_MK_DSM_H
#define MCOS_MK_DSM_H

#if !MCOS_AUTOSAR

/* validate configuration */
#if (MCOS_CFG_DSM_MAX < 0U)
#error MCOS_CFG_DSM_MAX must be greater than or equal to 0.
#endif /* (MCOS_CFG_DSM_MAX < 0U) */

#if (MCOS_CFG_DSM_MAX > 32U)
#error MCOS_CFG_DSM_MAX must be less than or equal to 32.
#endif /* (MCOS_CFG_DSM_MAX > 32U) */

#if (MCOS_CFG_DSM_ATTACH_MAX <= 0U)
#error MCOS_CFG_DSM_ATTACH_MAX must be greater than 0.
#endif /* (MCOS_CFG_DSM_ATTACH_MAX <= 0U) */

#if MCOS_CFG_DSM_MAX > 0U
/* DSM entry */
typedef struct dsm_entry
{
    mcos_link_t link;
    void *buffer;
    uint32_t size;
    mcos_dsm_create_attr_t attr;
    mcos_queue_t attach_use;
    mcos_queue_t attach_waitatt;
} dsm_entry_t;

/* DSM attach entry */
typedef struct dsm_attach_entry
{
    mcos_link_t link;
    dsm_entry_t *dsm_entry;
    void *area;
    mcos_dsm_attach_mode_t mode;
    uint32_t offset;
    uint32_t size;
    mcos_id_t owner_chid;
    mcos_id_t client_chid;
    mcos_id_t client_tid;
} dsm_attach_entry_t;

/* DSM manager control block */
typedef struct dsm_manager_cb
{
    /* DSM entry queue & table */
    mcos_queue_t dsm_use;
    mcos_queue_t dsm_free;
    dsm_entry_t dsm_entry[MCOS_CFG_DSM_MAX];

    /* DSM attach entry queue & table */
    mcos_queue_t attach_free;
    dsm_attach_entry_t attach_entry[MCOS_CFG_DSM_ATTACH_MAX];
} dsm_manager_cb_t;

/* DSM control block */
struct dsmcb_st
{
    dsm_manager_cb_t *dsmmgr;
};

uint8_t * mcos_dsmmgr_init(const mkcb_t *mkcb, uint8_t *end);
mcos_erid_t mcos_dsmmgr_create(const mkcb_t *mkcb, msg_dsmcre_t *req);
mcos_er_t mcos_dsmmgr_delete(const mkcb_t *mkcb, msg_dsmdel_t *req, void **buffer);
mcos_erid_t mcos_dsmmgr_attach(const mkcb_t *mkcb, msg_dsmatt_t *req);
mcos_er_t mcos_dsmmgr_reattach(const mkcb_t *mkcb, msg_dsmrat_t *req, msg_dsm_section_info_t *sinfo, void **buf_recv, void **buf_send, mcos_id_t *dindex, uint32_t *num_rel);
mcos_er_t mcos_dsmmgr_detach(const mkcb_t *mkcb, msg_dsmdet_t *req, msg_dsm_section_info_t *sinfo, void **buf_recv, mcos_id_t *dindex, uint32_t *num_rel);
mcos_er_t mcos_dsmmgr_get_info(const mkcb_t *mkcb, msg_dsminf_t *req, mcos_dsm_info_t *dinfo);
void mcos_dsmmgr_release_wait(const mkcb_t *mkcb, mcos_id_t dindex, uint32_t num_rel);


#else /* MCOS_CFG_DSM_MAX > 0U */
/* DSM control block */
struct dsmcb_st
{
    /* nothing */
};

#define mcos_dsmmgr_init(mkcb, end)     (end)
#endif /* MCOS_CFG_DSM_MAX > 0U */

#endif /* !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_MK_DSM_H */
