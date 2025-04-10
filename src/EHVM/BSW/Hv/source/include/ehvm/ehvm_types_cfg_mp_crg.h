/*
    Copyright (C) 2022 eSOL Co.,Ltd. All rights reserved.

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
 [ ehvm_types_cfg_mp_crg.h ] - CRG module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_MP_CRG_H
#define EHVM_TYPES_CFG_MP_CRG_H

#include "ehvm_types_stdint.h"

/* type definitions */

typedef struct {
    ehvm_uint32_t                    Spid;
} ehvm_crg_spid_t;

typedef struct {
    ehvm_uint32_t                    CsgBad;
    ehvm_uint32_t                    CsgAdv;
    ehvm_uint32_t                    CsgProt;
} ehvm_csg_prot_t;

typedef struct {
    ehvm_uint32_t                    CrgBad;
    ehvm_uint32_t                    CrgAdv;
    ehvm_uint32_t                    CrgProt;
} ehvm_crg_prot_t;

typedef struct {
    ehvm_uint32_t                    CsgChannelNumber;
    ehvm_uint32_t                    CrgNumOfCSGSpid;
    EhvmConst ehvm_crg_spid_t*      CrgCSGSpidPtr;
    ehvm_uint32_t                    CsgNumOfProt;
    EhvmConst ehvm_csg_prot_t*      CsgProtPtr;
} ehvm_csg_info_t;

typedef struct {
    ehvm_uint32_t                    CrgChannelNumber;
    ehvm_uint32_t                    CrgNumOfCRGSpid;
    EhvmConst ehvm_crg_spid_t*      CrgCRGSpidPtr;
    ehvm_uint32_t                    CrgNumOfProt;
    EhvmConst ehvm_crg_prot_t*      CrgProtPtr;
} ehvm_crg_info_t;

typedef struct {
    ehvm_uint32_t                    CrgNumOfCRG;
    EhvmConst ehvm_crg_info_t*      CrgCRGPtr;
    ehvm_uint32_t                    CrgNumOfCSG;
    EhvmConst ehvm_csg_info_t*      CrgCSGPtr;
} ehvm_crg_config_t;

#endif /* EHVM_TYPES_CFG_MP_CRG_H */
