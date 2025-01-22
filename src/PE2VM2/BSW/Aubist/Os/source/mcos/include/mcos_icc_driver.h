/*
    Copyright (C) 2018 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_icc_driver.h ] - Inter-Cluster Communication driver header
****************************************************************************/
#ifndef MCOS_ICC_DRIVER_H
#define MCOS_ICC_DRIVER_H

#include <mcos/mcos.h>

#if MCOS_CFG_GLB_CLMM_ENABLE

/* ICC driver model */
#define MCOS_ICC_DRIVER_MODEL_POLLING           0x00000000
#define MCOS_ICC_DRIVER_MODEL_CALLBACK          0x00000001

#define MCOS_ICC_DRIVER_MODEL_SERVER            0x00000000
#define MCOS_ICC_DRIVER_MODEL_DIRECT            0x00000002

/* type definitions */
typedef struct mcos_icc_driver_info             mcos_icc_driver_info_t;
typedef struct mcos_icc_driver_callback_info    mcos_icc_driver_callback_info_t;
typedef struct mcos_icc_driver_start            mcos_icc_driver_start_t;
typedef struct mcos_icc_driver                  mcos_icc_driver_t;

/* Initialize ICC driver */
typedef mcos_er_t (*mcos_icc_driver_func_init_t)(uint32_t rcidx);

/* Finalize ICC driver */
typedef void (*mcos_icc_driver_func_fini_t)(uint32_t rcidx);

/* Start ICC driver */
typedef mcos_er_t (*mcos_icc_driver_func_start_t)(uint32_t rcidx, const mcos_icc_driver_start_t *start_data);

/* Send data to hardware cluster */
typedef mcos_er_t (*mcos_icc_driver_func_send_t)(mcos_id_t hwclid, const void **data, const uint32_t *sizes, const uint32_t count, uint32_t icc_parameter);

/* Receive data from hardware cluster */
typedef mcos_er_t (*mcos_icc_driver_func_recv_t)(void *data, uint32_t *size);

/* Send data to core in other hardware clusters */
typedef mcos_er_t (*mcos_icc_driver_func_send_direct_t)(mcos_id_t hwclid, uint32_t rcidx, const void **data, const uint32_t *sizes, const uint32_t count, uint32_t icc_parameter);

/* Receive data from hardware cluster */
typedef mcos_er_t (*mcos_icc_driver_func_recv_direct_t)(uint32_t rcidx, void *data, uint32_t *size);

/* Get ICC driver information */
typedef const mcos_icc_driver_info_t* (*mcos_icc_driver_func_get_info_t)(void);

/* Callback function of received data */
typedef void (*mcos_icc_driver_func_callback_t)(mcos_id_t iid, uintptr_t data);

/* ICC driver information */
struct mcos_icc_driver_info {
    uint32_t model;
    int32_t max_send;
};

/* ICC driver callback information */
struct mcos_icc_driver_callback_info
{
    mcos_icc_driver_func_callback_t func;
    uintptr_t data;
};

/* ICC driver start setting */
struct mcos_icc_driver_start
{
    mcos_icc_driver_callback_info_t rcv_callback_info;
};

/* ICC driver table */
struct mcos_icc_driver
{
    mcos_icc_driver_func_init_t         init;
    mcos_icc_driver_func_fini_t         fini;
    mcos_icc_driver_func_start_t        start;
    mcos_icc_driver_func_send_t         send;
    mcos_icc_driver_func_recv_t         recv;
    mcos_icc_driver_func_send_direct_t  send_direct;
    mcos_icc_driver_func_recv_direct_t  recv_direct;
    mcos_icc_driver_func_get_info_t     getinfo;

    /*
     * The following restrictions exist in the ICC driver using the polling model.
     *
     * - The sender thread must be placed on the same core as the core where the
     *   CLMM server thread resides.
     * - The receiver thread must be placed on the different core than the core
     *   where the CLMM server thread resides.
     * - Processing that occupies the CPU must not be executed by the core in
     *   which the receiver thread is placed.
     * - Only one receiver thread can be placed in one core when using multiple
     *   ICC drivers.
     */
    mcos_id_t                           send_thread_lcid;
    mcos_id_t                           recv_thread_lcid;
};

#ifdef __cplusplus
extern "C"
{
#endif

/* ICC driver tables */
extern const mcos_icc_driver_t mcos_icc_driver_table[];

#ifdef __cplusplus
}
#endif

#endif  /* MCOS_CFG_GLB_CLMM_ENABLE */

#endif /* MCOS_ICC_DRIVER_H */
