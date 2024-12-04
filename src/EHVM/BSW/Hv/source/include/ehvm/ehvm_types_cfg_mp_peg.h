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
 [ ehvm_types_cfg_mp_peg.h ] - PEG module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_MP_PEG_H
#define EHVM_TYPES_CFG_MP_PEG_H

/* type definitions */

typedef struct {
    ehvm_uint32_t                    PegSpid;
} ehvm_peg_spid_t;

typedef struct {
    ehvm_uint32_t                    PegBad;
    ehvm_uint32_t                    PegAdv;
    ehvm_uint32_t                    PegProt;
} ehvm_peg_prot_t;

typedef struct {
    ehvm_uint32_t                    PegNumOfSpid;
    EhvmConst ehvm_peg_spid_t*      PegSpidPtr;
    ehvm_uint32_t                    PegNumOfProt;
    EhvmConst ehvm_peg_prot_t*      PegProtPtr;
} ehvm_peg_config_t;

#endif /* EHVM_TYPES_CFG_MP_PEG_H */
