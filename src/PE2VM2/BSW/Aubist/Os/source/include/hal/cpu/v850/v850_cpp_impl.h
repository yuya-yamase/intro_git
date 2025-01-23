/*
    Copyright(C) 2019 eSOL Co., Ltd. All rights reserved.

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
[ v850_cpp_impl.h ] - V850 implementation header file
****************************************************************************/
#ifndef V850_CPP_IMPL_H
#define V850_CPP_IMPL_H

#define PSW_UM_MASK     0x40000000U
#define PSW_UM_HI_MASK  0x4000
#define PSW_UM_SHIFT    2
#define PSW_ID_MASK     0x20

#define PSW_EIMASK_MASK 0x03F00000U
#define PSW_EIMASK_SHIFT 20

#define PSW_EBV_MASK    0x00008000U
#define PSW_EBV_ENA     0x00008000U
#define PSW_EBV_DIS     0x00000000U

#define PSW_CU210_MASK  0x00070000U

/* default psw w/o CU */
#define DEFAULT_PSW     0x03F08000U
#define DEFAULT_PSW_UM  (PSW_UM_MASK | DEFAULT_PSW)

/*
 *  default R20-R21 for thread startup
 */
#define DEFAULT_R20 (255)
#define DEFAULT_R21 (65535)

/* MPU */
#define MPU_MPM_MPE_MASK    0x00000001U

#define MPU_MPAT_UR         0x00000001U
#define MPU_MPAT_UW         0x00000002U
#define MPU_MPAT_UX         0x00000004U
#define MPU_MPAT_SR         0x00000008U
#define MPU_MPAT_SW         0x00000010U
#define MPU_MPAT_SX         0x00000020U
#define MPU_MPAT_E          0x00000080U
#define MPU_MPAT_RG         0x00004000U
#define MPU_MPAT_WG         0x00008000U

#define MPU_MPLA_RSV_MASK   0x00000003UL
#define MPU_MPUA_RSV_MASK   0x00000003UL

#define MPU_MPCFG_BE_MASK   0x00003f00UL
#define MPU_MPCFG_BE_SHIFT  0x8UL

#define SVLOCK_SVL          0x1

/* EBASE */
#define REG_EBASE_EBASE_MASK    0xFFFFFE00U
#define REG_EBASE_DV_MASK       0x00000002U
#define REG_EBASE_RINT_MASK     0x00000001U

#define REG_EBASE_DV_ENA        0x00000002U
#define REG_EBASE_DV_DIS        0x00000000U

#define REG_EBASE_RINT_ENA      0x00000001U
#define REG_EBASE_RINT_DIS      0x00000000U

/* INTBP */
#define INTBP_MASK          0xFFFFFE00U

/* INTCFG */
#define INTCFG_EPL_ISPC_BITS    0x00000003UL
#define INTCFG_EPL_ON           0x00000002UL
#define INTCFG_ISPC_OFF         0x00000000UL
#define INTCFG_EPL_ISPC_VAL     (INTCFG_EPL_ON|INTCFG_ISPC_OFF)

#endif /* #ifndef V850_CPP_IMPL_H */
