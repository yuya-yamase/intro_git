/*
    Copyright(C) 2022 eSOL Co., Ltd. All rights reserved.

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
[ mcos_spinlcok_obj_v850.h ] - MCOS SPINLOCK OBJ for V850
****************************************************************************/
#ifndef MCOS_SPINLOCK_OBJ_V850_H
#define MCOS_SPINLOCK_OBJ_V850_H

/* Spinlock configuration */
#define AR_SPINLOCK_PADDING1_N      7U
#define AR_SPINLOCK_PADDING2_N      7U
#define AR_IOC_SPINLOCK_PADDING1_N  7U
#define AR_IOC_SPINLOCK_PADDING2_N  7U


/* Spinlock type for the ticket algorithm */
typedef struct
{
    volatile uint16_t now_serving;
    volatile uint16_t next_ticket;
} mcos_spinlock_ticket_tickets_t;

typedef volatile union mcos_spinlock_ticket
{
    volatile uint32_t spinlock;
    mcos_spinlock_ticket_tickets_t tickets;
} mcos_spinlock_ticket_t;

struct mcos_spinlock_obj_st {
    mcos_spinlock_ticket_t ticket;
};

#endif /* #ifndef MCOS_SPINLOCK_OBJ_V850_H */
