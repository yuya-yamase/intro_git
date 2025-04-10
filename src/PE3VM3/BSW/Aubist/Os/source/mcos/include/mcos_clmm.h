/*
    Copyright (C) 2014 eSOL Co.,Ltd. Tokyo, Japan

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
[ mcos_clmm.h ] -  MCOS cluster manager header
****************************************************************************/
#ifndef MCOS_CLMM_H
#define MCOS_CLMM_H

#include <mcos/mcos_syssrv.cfg>

#if MCOS_CFG_GLB_CLMM_ENABLE

#include "mcos_basic.h"

/* type definitions */
typedef struct mcos_clmm_routing_info       mcos_clmm_routing_info_t;

/* CLMM  */
#define MCOS_CLMM_COM_FORMAT_LOCAL          0U
#define MCOS_CLMM_COM_FORMAT_STANDARD       1U

/* CLMM routing information */
struct mcos_clmm_routing_info {
    mcos_id_t dest_start_cluster_hwclid;
    mcos_id_t dest_end_cluster_hwclid;
    mcos_id_t fwd_cluster_hwclid;
    mcos_id_t icc_driver_index;
    uint32_t  icc_driver_parameter;
    uint32_t  routing_flag;
};

#ifdef __cplusplus
extern "C"
{
#endif

/* Get CLMM lcid for this cluster */
mcos_id_t mcos_clmm_get_lcid(void);

/* Get CLMM sid for this cluster */
mcos_id_t mcos_clmm_get_sid(void);

/* create CLMM server */
void mcos_clmm_create_server(mcos_id_t lcid);

/* convert to standard format from local format */
uint32_t mcos_clmm_convert_format_standard(void *std, void *local, uint32_t size);

/* convert to standard format from local format */
uint32_t mcos_clmm_convert_format_local(void *local, void *std, uint32_t size);

/* determine the cluster uses CLMM server */
mcos_bool_t mcos_clmm_is_server(mcos_id_t hwclid);

/* CLMM routing table */
extern const mcos_clmm_routing_info_t mcos_clmm_routing_table[];

#ifdef __cplusplus
}
#endif

#endif /* #if MCOS_CFG_GLB_CLMM_ENABLE */

#endif /* #ifndef MCOS_CLMM_H */
