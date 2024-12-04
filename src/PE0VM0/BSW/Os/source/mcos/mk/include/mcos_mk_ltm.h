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
[ mcos_mk_ltm.h ] - eMCOS/MK local timwer local header
****************************************************************************/
#ifndef MCOS_MK_LTM_H
#define MCOS_MK_LTM_H

#if !MCOS_AUTOSAR

#include "mcos_mk.h"
#include "mcos_timerdrv.h"

/* csrid bit definition */
#define LTM_IDINFO_CSRINDEX_SHIFT   (0)
#define LTM_IDINFO_CSRINDEX_MASK    (0x001F)
#define LTM_IDINFO_LCID_SHIFT       (5U)
#define LTM_IDINFO_LCID_MASK        (0x03FF)

/* csr flag bit (public) */
#define LTM_FLAG_SRVALLOC       (0x00000001)

/* check defined value */
#if (MCOS_CFG_CSR_MAX < 0U)
#error MCOS_CFG_CSR_MAX must be greater than or equal to 0.
#endif /* (MCOS_CFG_CSR_MAX < 0U) */

#if (MCOS_CFG_CSR_MAX > (1U << LTM_IDINFO_LCID_SHIFT))
#error MCOS_CFG_CSR_MAX must be less than or equal to 32.
#endif /* (MCOS_CFG_CSR_MAX > (1U << LTM_IDINFO_LCID_SHIFT)) */


/* csr function */
typedef void (*ltm_csr_callback_t)(mcos_id_t csrid, mcos_uintptr_t param);

typedef struct
{
    mcos_link_t         link;       /* Queue structure */
    kernel_time_t       uptime;     /* system time to release thread from wait or to launch CSR */
} ltm_csr_link_t;

/* Cyclic service information */
typedef struct
{
    ltm_csr_link_t      timelink;   /* csr link structure */
    ltm_csr_callback_t  entry;      /* entry address of CSR */
    void                *stackaddr; /* stack address */
    mcos_uintptr_t           param;      /* entry parameter */
    uint32_t            flag;       /* flag */
    mcos_reltime_t      cycle;      /* cycle time */
} cyclic_services_t;


/* local time manager control block */
struct ltmcb_st
{
    kernel_time_t querytime;    /* local query time */
    kernel_time_t uptime;       /* local up time */
    mcos_queue_t cscb_use;      /* cscb use-queue top */
    mcos_queue_t cscb_free;     /* cscb free-queue top */
    cyclic_services_t cscb[MCOS_CFG_CSR_MAX];  /* cscb table */
    uint32_t     csr_stksize;   /* CSR stack size */
    void         *csr_stkaddr;  /* CSR stack address */
    uint8_t      csr_num;       /* number of CSRs which use CSR stack */
    uint8_t      flag;          /* flag */
    uint16_t     status;        /* LTM status */
    tmdrvcb_t tmdrvcb;          /* timer driver control block */
};


/*
 * convert csrid to lcid
 *
 * Input     :   csrid           csr id
 * Output    :   none
 * Return    :   lcid
 * Note  :   none
 */
MCOS_INLINE mcos_id_t
mcos_ltm_convert_to_lcid(mcos_id_t csrid)
{
    return (csrid >> LTM_IDINFO_LCID_SHIFT);
}

/*
 * convert csrid to csr index
 * Input     :   csrid           csr id
 * Output    :   none
 * Return    :   csr index
 * Note  :   none
 */
MCOS_INLINE mcos_id_t
mcos_ltm_convert_to_csridx(mcos_id_t csrid)
{
    return (csrid & LTM_IDINFO_CSRINDEX_MASK);
}

/*
 * convert (lcid, csrindex) to csrid
 * Input     :   lcid            lcid
 *           :   csridx          csr index
 * Output    :   none
 * Return    :   csrid
 * Note  :   none
 */
MCOS_INLINE mcos_id_t
mcos_ltm_convert_to_csrid(mcos_id_t lcid, mcos_id_t csridx)
{
    return ((lcid << LTM_IDINFO_LCID_SHIFT) | csridx);
}


/*** domain public function ***/
extern void mcos_ltm_init(const mkcb_t *mkcb);
extern void mcos_ltm_start(const mkcb_t *mkcb);
extern void mcos_ltm_stop(const mkcb_t *mkcb);
extern void mcos_ltm_set_localtime(const mkcb_t *mkcb, const kernel_time_t *current);
extern mcos_er_t mcos_ltm_get_localtime(const mkcb_t *mkcb, kernel_time_t *current);
extern mcos_er_t mcos_ltm_get_localtime_detail(const mkcb_t *mkcb, kernel_time_t *current, uint32_t *remaind_val);
extern mcos_er_t mcos_ltm_get_uptime(const mkcb_t *mkcb, kernel_time_t *current);
extern mcos_er_t mcos_ltm_get_uptime_detail(const mkcb_t *mkcb, kernel_time_t *current, uint32_t *remaind_val);
extern void mcos_ltm_add_localtime(const mkcb_t *mkcb, uint32_t passtime);
extern mcos_erid_t mcos_ltm_set_csr(const mkcb_t *mkcb, msg_csrcre_body_t *req, void **rel_stack);
extern mcos_er_t mcos_ltm_clear_csr(const mkcb_t *mkcb, msg_csrdel_body_t *req, void **rel_stack);


mcos_er_t mcos_time_set_internal(const mcos_systime_t *currenttime);
mcos_er_t mcos_time_get_internal(mcos_systime_t *currenttime);
mcos_er_t mcos_time_get_nano_internal(mcos_systime_t *currenttime, uint32_t *nano);
mcos_er_t mcos_uptime_get_internal(mcos_systime_t *uptime);
mcos_erid_t mcos_cyclic_create_internal(const mcos_cyc_cre_t *ccp);
mcos_er_t mcos_cyclic_delete_internal(mcos_id_t csrid);

#endif /* !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_MK_LTM_H */
