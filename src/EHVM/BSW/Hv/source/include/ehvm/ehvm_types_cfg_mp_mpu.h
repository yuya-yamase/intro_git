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
 [ ehvm_types_cfg_mp_mpu.h ] - MPU module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_MP_MPU_H
#define EHVM_TYPES_CFG_MP_MPU_H

/* type definitions */

typedef struct {
    ehvm_uint32_t                   MpuMplaAddr;
    ehvm_uint32_t                   MpuMpuaAddr;
    ehvm_uint32_t                   MpuMemoryProtectionArea;
} ehvm_mpu_memory_entry_t;

typedef struct {
    EhvmConst ehvm_mpu_memory_entry_t*  MpuHostEntry;
} ehvm_mpu_host_memory_t;

typedef struct {
    ehvm_spid_t                     MpuSpid;
} ehvm_mpu_guest_spid_t;

typedef struct {
    ehvm_gpid_t                     MpuGpid;
    ehvm_uint32_t                   MpuNumOfGuestSpid;
    EhvmConst ehvm_mpu_guest_spid_t*    MpuGuestSpid;
} ehvm_mpu_guest_memory_t;

typedef struct {
    ehvm_uint32_t                   MpuNumOfGuest;
    EhvmConst ehvm_mpu_guest_memory_t*  MpuGuestMemory;
    ehvm_uint32_t                   MpuNumOfVariableHostMemory;
    EhvmConst ehvm_mpu_host_memory_t*   MpuVariableHostMemory;
    ehvm_uint32_t                   MpuNumOfFixedHostEntry;
    EhvmConst ehvm_mpu_memory_entry_t*  MpuFixedHostEntry;
} ehvm_mpu_config_t;

typedef struct {
    ehvm_uint32_t MmRomramLowerAddr;
    ehvm_uint32_t MmRomramUpperAddr;
} ehvm_mm_romram_area_t;

typedef struct {
    EhvmConst ehvm_mm_romram_area_t* MmRomramArea;
    ehvm_uint8_t                     MmNumOfRomramArea;
} ehvm_mm_common_config_t;

#endif /* EHVM_TYPES_CFG_MP_MPU_H */
