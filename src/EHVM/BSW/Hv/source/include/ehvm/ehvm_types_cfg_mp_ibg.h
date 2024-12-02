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
 [ ehvm_types_cfg_mp_ibg.h ] - IBG module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_MP_IBG_H
#define EHVM_TYPES_CFG_MP_IBG_H

/* type definitions */

typedef struct {
    ehvm_uint32_t                    IbgProt_0;
    ehvm_uint32_t                    IbgProt_1;
} ehvm_ibg_prot_t;

typedef struct {
    ehvm_uint32_t                    Ibg_NumOfTptm_n;
    EhvmConst ehvm_ibg_prot_t*      Ibg_Tptm_n_Ptr;
    ehvm_uint32_t                    Ibg_NumOfTptm_8;
    EhvmConst ehvm_ibg_prot_t*      Ibg_Tptm_8_Ptr;
    ehvm_uint32_t                    Ibg_NumOfTptm_9;
    EhvmConst ehvm_ibg_prot_t*      Ibg_Tptm_9_Ptr;
} ehvm_ibg_tptm_t;

typedef struct {
    ehvm_uint32_t                    Ibg_NumOfBarr;
    EhvmConst ehvm_ibg_prot_t*      Ibg_BarrPtr;
    ehvm_uint32_t                    Ibg_NumOfBarr16;
    EhvmConst ehvm_ibg_prot_t*      Ibg_Barr16Ptr;
} ehvm_ibg_barr_t;

typedef struct {
    ehvm_uint32_t                    Ibg_NumOfRn;
    EhvmConst ehvm_ibg_prot_t*      Ibg_RnPtr;
    ehvm_uint32_t                    Ibg_NumOfTn;
    EhvmConst ehvm_ibg_prot_t*      Ibg_TnPtr;
    ehvm_uint32_t                    Ibg_NumOf4;
    EhvmConst ehvm_ibg_prot_t*      Ibg_4Ptr;
} ehvm_ibg_ipir_t;

typedef struct {
    ehvm_uint32_t                    Ibg_NumOfIPIR;
    EhvmConst ehvm_ibg_ipir_t*      Ibg_IPIRPtr;
    ehvm_uint32_t                    Ibg_NumOfBARR;
    EhvmConst ehvm_ibg_barr_t*      Ibg_BARRPtr;
    ehvm_uint32_t                    Ibg_NumOfTPTM;
    EhvmConst ehvm_ibg_tptm_t*      Ibg_TPTMPtr;
} ehvm_ibg_config_t;

#endif /* EHVM_TYPES_CFG_MP_IBG_H */
