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
[ mcos_tpm.h ] - eMCOS/MK thread-pool local header
****************************************************************************/
#ifndef MCOS_TPM_H
#define MCOS_TPM_H

#if !MCOS_AUTOSAR

#include "mcos_mk.h"

/* thread-pool control block */
typedef struct
{
    uint16_t    tpid;               /* thread-pool id */
    uint16_t    owner;              /* owner thread id */
    uint8_t     tpri;               /* request thread's priority */
    uint8_t     state;              /* current state */
    uint16_t    tcnt;               /* max request thread count */
    uint16_t    atcnt;              /* assigned request thread count */
    uint16_t    reqid;              /* next assignable request id */
    uint16_t    dest;               /* next destination request thread's index */
    uint16_t    rest;               /* rest request count */
    uint16_t    reqtid[CCNT_PER_CLST];  /* assigned request thread id */
    uint8_t     attr;               /* attribute see mcos.h */
    msg_t       *msg;               /* pending received message */
} tpcb_t;

/* thread-pool manager control block */
struct tpmcb_st
{
    tpcb_t          tpcb[MCOS_CFG_TPOOL_MAX];
    /* filter for receiving reply */
    mcos_id_t       reqtid[CCNT_PER_CLST + 1];
};


/* thread-pool manager interface functions */
#if MCOS_CFG_TPOOL_MAX > 0U
void mcos_tpm_init(const mkcb_t *mkcb);
mcos_erid_t mcos_tpm_create(uint32_t tcnt, uint8_t tpri, uint8_t attr);
mcos_er_t mcos_tpm_delete(mcos_id_t tpid);
mcos_erid_t mcos_tpm_execute(mcos_id_t tpid, uint8_t mode, uint8_t reqcnt, mcos_tpool_req_t *req);
mcos_erid_t mcos_tpm_wait(mcos_id_t tpid, uint8_t mode, uint8_t reqcnt, mcos_tpool_req_t *req);
mcos_erid_t mcos_tpm_activate(mcos_id_t tpid);
mcos_er_t mcos_tpm_deactivate(mcos_id_t tpid);
void mcos_tpm_reqt_main(uint32_t param, mcos_uintptr_t exinf);
void mcos_tpm_reqt_deactivate(mcos_id_t lcid);
#else
#define mcos_tpm_init(x)
#define mcos_tpm_create(x, y, z)            (MCOS_ENOMEM)
#define mcos_tpm_delete(x)                  (MCOS_EPAR)
#define mcos_tpm_execute(a, b, c, d)        (MCOS_EPAR)
#define mcos_tpm_wait(a, b, c, d)           (MCOS_EPAR)
#define mcos_tpm_activate(x)                (MCOS_EPAR)
#define mcos_tpm_deactivate(x)              (MCOS_EPAR)
#define mcos_tpm_reqt_deactivate(x)
#endif

#endif /* !MCOS_AUTOSAR */

#endif /* #ifndef MCOS_TPM_H */
