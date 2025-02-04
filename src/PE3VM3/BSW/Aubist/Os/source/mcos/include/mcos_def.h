/*
    Copyright (C) 2011 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_def.h] - MCOS micro-kernel define header
****************************************************************************/
#ifndef MCOS_DEF_H
#define MCOS_DEF_H

#include <mcos/mcos.cfg>
#include <mcos/mcos_ds.cfg>
#include <mcos/mcos_kprof.cfg>
#include <mcos/mcos_hwcl.cfg>
#include <mcos/system.cfg>

#include "mcos_mk_config.h"

/* defined */
#define TID_NONE        ((mcos_id_t)0x00U) /* thread id is not specified */
#define TID_SELF        ((mcos_id_t)0x00U) /* current thread id is specified */
#define TID_CSR         ((mcos_id_t)-1)    /* it means csr */
#define LCID_NONE       ((mcos_id_t)0x00U) /* core id is not specified */
#define LCID_UNCERTAIN  ((mcos_id_t)0x00U) /* floating core id */
#define LCID_INVALID    ((mcos_id_t)-3)    /* invalid core id (the value is a duplicate of MCOS_LCID_INVALID) */

/* parameter check */
#define WORD_SIZE       (0x04U)
#define WORD_SIZE_MASK  (0x03U)
#define USHORT_MAX      (65535U)
#define BIT8_MAX        (255)

#define TPRI_MAX        (254)       /* max thread priority */
#define TPRI_MIN        (1)         /* mimimum thread priority */
#define MPRI_MAX        (254)       /* max message priority */
#define MPRI_MIN        (0)         /* mimimum message priority */

#define ARYNUM_OK       (1)
#define ARYNUM_ERR      (-1)

#if MCOS_AUTOSAR

#define MCOS_BASE_LCID  ((int32_t)1)
#define MCOS_BASE_LCID_U  ((uint32_t)1)

#else /* if !MCOS_AUTOSAR */

#define MCOS_BASE_LCID  ((((int32_t)MCOS_CFG_HWCL_ID - (int32_t)1) * (int32_t)MCOS_CFG_GLB_CORE_PER_HWCL_MAX) + (int32_t)1)

#endif /* if !MCOS_AUTOSAR */

/* fixed value */
#define BOOT_CORE_LCID  (MCOS_BASE_LCID)           /* Boot core id */

/* dependency value */
#define CCNT_PER_CLST   (MP_CONTROL_CORE_COUNT)    /* core count per cluster */

#if !defined(MCOS_SINGLE_CORE)
#if (MP_CONTROL_CORE_COUNT == 1U)
#define MCOS_SINGLE_CORE   1U
#else /* #if (MP_CONTROL_CORE_COUNT == 1U) */
#define MCOS_SINGLE_CORE   0U
#endif
#endif

/* Available HW cluster or not */
#define MCOS_HWCL           (MCOS_CFG_GLB_HWCL_MAX > 1U)

/* service name prefix definitions */
#define MCOS_SYSTEM_PREFIX      "sys."


#ifdef MCOS_USE_TKAPI
#define MCOS_TK_API  (1U)                /* enable TK API layer dependent code */
#else
#define MCOS_TK_API  (0U)
#endif  /* MCOS_USE_TKAPI */

#ifdef MCOS_USE_PTAPI
#define MCOS_PT_API  (1U)                /* enable PT API layer dependent code */
#else
#define MCOS_PT_API  (0U)
#endif  /* MCOS_USE_PTAPI */

#if (defined(MCOS_USE_MSGPROF) || MCOS_CFG_DS_MSGPROF_ENABLE)
#define MCOS_MSGPROF  (1U)               /* enable Message Profiler hook code */
#if MCOS_CFG_DS_MSGPROF_ENABLE
#define MCOS_MSGPROF_FOR_DAEMON (1U)
#else /* MCOS_CFG_DS_MSGPROF_ENABLE */
#define MCOS_MSGPROF_FOR_DAEMON (0U)
#endif /* MCOS_CFG_DS_MSGPROF_ENABLE */
#else
#define MCOS_MSGPROF  (0U)
#endif  /* #if (defined(MCOS_USE_MSGPROF) || MCOS_CFG_DS_MSGPROF_ENABLE) */

#ifdef MCOS_USE_RTPROF
#define MCOS_RTPROF  (1U)                /* enable Realtime Profiler dependent code */
#else
#define MCOS_RTPROF  (0U)
#endif  /* #ifdef MCOS_USE_RTPROF */

/* check defined value */
#if !(BUILD_LIB || USE_OSLIB)

#if (MCOS_CFG_SCCL_NUM < 1U)
#error MCOS_CFG_SCCL_NUM is too small.
#endif /* #if (MCOS_CFG_SCCL_NUM < 1U) */

#if (MCOS_CFG_SCCL_NUM > MP_CONTROL_CORE_COUNT)
#error MCOS_CFG_SCCL_NUM is too large.
#endif /* #if (MCOS_CFG_SCCL_NUM > MP_CONTROL_CORE_COUNT) */

#if ((MCOS_CFG_THR_DEFAULT_STACKSIZE & WORD_SIZE_MASK) != 0U)
#error MCOS_CFG_THR_DEFAULT_STACKSIZE is not word align.
#endif /* #if ((MCOS_CFG_THR_DEFAULT_STACKSIZE & (WORD_SIZE - 1)) != 0U) */

#if ((MCOS_CFG_SYS_STACKSIZE & WORD_SIZE_MASK) != 0U)
#error MCOS_CFG_SYS_STACKSIZE is not word align.
#endif /* #if ((MCOS_CFG_SYS_STACKSIZE & (WORD_SIZE - 1)) != 0U) */

#if ((MCOS_CFG_MSG_SIZE_MAX / WORD_SIZE) < 1U)
#error MCOS_CFG_MSG_SIZE_MAX is too small.
#endif /* #if ((MCOS_CFG_MSG_SIZE_MAX / WORD_SIZE) < 1U) */

#if ((MCOS_CFG_MSG_SIZE_MAX & WORD_SIZE_MASK) != 0U)
#error MCOS_CFG_MSG_SIZE_MAX is not word align.
#endif /* #if ((MCOS_CFG_MSG_SIZE_MAX & (WORD_SIZE - 1)) != 0U) */

#if ((MCOS_CFG_MSG_BUFSIZE & WORD_SIZE_MASK) != 0U)
#error MCOS_CFG_MSG_BUFSIZE is not word align.
#endif /* #if ((MCOS_CFG_MSG_BUFSIZE & (WORD_SIZE - 1)) != 0U) */

#if (MCOS_CFG_FMSG_BUFSIZE > 1024U)
#error MCOS_CFG_FMSG_BUFSIZE is too large.
#endif /* #if (MCOS_CFG_FMSG_BUFSIZE > 1024U) */

#if (MCOS_CFG_FMSG_BUFSIZE < 16U)
#error MCOS_CFG_FMSG_BUFSIZE is too small.
#endif /* #if (MCOS_CFG_FMSG_BUFSIZE < 16U) */

#if ((MCOS_CFG_FMSG_BUFSIZE & WORD_SIZE_MASK) != 0U)
#error MCOS_CFG_FMSG_BUFSIZE is not word align.
#endif /* #if ((MCOS_CFG_FMSG_BUFSIZE & (WORD_SIZE - 1)) != 0U) */

#if (MCOS_CFG_MSG_PENDING_COUNT_MAX < 1U)
#error MCOS_CFG_MSG_PENDING_COUNT_MAX is too small.
#endif /* #if (MCOS_CFG_MSG_PENDING_COUNT_MAX < 1U) */

#if (MCOS_CFG_MSG_RESOLVE_COUNT_MAX < 1U)
#error MCOS_CFG_MSG_RESOLVE_COUNT_MAX is too small.
#endif /* #if (MCOS_CFG_MSG_RESOLVE_COUNT_MAX < 1U) */

#if MCOS_CFG_TS_LOAD_BALANCING_CYCLE < 0U
#error MCOS_CFG_TS_LOAD_BALANCING_CYCLE is too small.
#endif /* #if (MCOS_CFG_TS_LOAD_BALANCING_CYCLE < 0U) */

#if MCOS_CFG_HEAP_BLOCKSIZE < 0x400U
#error MCOS_CFG_HEAP_BLOCKSIZE is too small.
#endif /* #if MCOS_CFG_HEAP_BLOCKSIZE < 0x400U */

#if MCOS_CFG_HEAP_BLOCKSIZE > 0x40000000U
#error MCOS_CFG_HEAP_BLOCKSIZE is too large.
#endif /* #if MCOS_CFG_HEAP_BLOCKSIZE > 0x40000000U */

#if MCOS_CFG_HEAP_SPOOLSIZE_MIN < 0x400U
#error MCOS_CFG_HEAP_SPOOLSIZE_MIN is too small.
#endif /* #if MCOS_CFG_HEAP_SPOOLSIZE_MIN < 0x400U */

#if MCOS_CFG_HEAP_SPOOLSIZE_MIN > 0x40000000U
#error MCOS_CFG_HEAP_SPOOLSIZE_MIN is too large.
#endif /* #if MCOS_CFG_HEAP_SPOOLSIZE_MIN > 0x40000000U */

#if MCOS_CFG_HEAP_SPOOLSIZE_MAX < 0x800U
#error MCOS_CFG_HEAP_SPOOLSIZE_MAX is too small.
#endif /* #if MCOS_CFG_HEAP_SPOOLSIZE_MAX < 0x800U */

#if MCOS_CFG_HEAP_SPOOLSIZE_MAX > 0x80000000U
#error MCOS_CFG_HEAP_SPOOLSIZE_MAX is too large.
#endif /* #if MCOS_CFG_HEAP_SPOOLSIZE_MAX > 0x80000000U */

#if MCOS_CFG_HEAP_SPOOLSIZE_MIN < MCOS_CFG_HEAP_BLOCKSIZE
#error MCOS_CFG_HEAP_SPOOLSIZE_MIN must be greater than or equal to MCOS_CFG_HEAP_BLOCKSIZE.
#endif /* #if MCOS_CFG_HEAP_SPOOLSIZE_MIN < MCOS_CFG_HEAP_BLOCKSIZE */

#if MCOS_CFG_HEAP_SPOOLSIZE_MAX < (MCOS_CFG_HEAP_SPOOLSIZE_MIN * 2U)
#error MCOS_CFG_HEAP_SPOOLSIZE_MAX should be at least twice MCOS_CFG_HEAP_SPOOLSIZE_MIN.
#endif /* #if MCOS_CFG_HEAP_SPOOLSIZE_MAX < (MCOS_CFG_HEAP_SPOOLSIZE_MIN * 2U) */

#if MCOS_CFG_THR_DEFAULT_PRI < 17U
#error MCOS_CFG_THR_DEFAULT_PRI is too small.
#endif /* MCOS_CFG_THR_DEFAULT_PRI < */

#if MCOS_CFG_THR_DEFAULT_PRI > 254U
#error MCOS_CFG_THR_DEFAULT_PRI is too large.
#endif /* MCOS_CFG_THR_DEFAULT_PRI > */

#if (MCOS_CFG_RRMSG_BUFSIZE < 16U)
#error MCOS_CFG_RRMSG_BUFSIZE is too small.
#endif /* #if (MCOS_CFG_RRMSG_BUFSIZE < 0U) */

#if (MCOS_CFG_RRMSG_BUFSIZE > 64U)
#error MCOS_CFG_RRMSG_BUFSIZE is too large.
#endif /* #if (MCOS_CFG_RRMSG_BUFSIZE > 64U) */

#if ((MCOS_CFG_RRMSG_BUFSIZE & WORD_SIZE_MASK) != 0U)
#error MCOS_CFG_RRMSG_BUFSIZE is not word align.
#endif /* #if ((MCOS_CFG_RRMSG_BUFSIZE & (WORD_SIZE - 1)) != 0U) */


/* If using HW cluster LCID/CID mapping */
#if MCOS_HWCL
#if (MCOS_CFG_HWCL_ID <= 0U) || (MCOS_CFG_HWCL_ID > MCOS_CFG_GLB_HWCL_MAX)
#error MCOS_CFG_HWCL_ID is invalid
#endif
#if (MCOS_CFG_GLB_HWCL_MAX <= 0U) || (MCOS_CFG_GLB_HWCL_MAX > 32U)
#error MCOS_CFG_GLB_HWCL_MAX is invalid
#endif
#if (MCOS_CFG_GLB_THR_PER_CORE_MAX < TCB_CNT)
#error MCOS_CFG_GLB_THR_PER_CORE_MAX is invalid
#endif
#if (MCOS_CFG_GLB_CORE_PER_HWCL_MAX < MP_CONTROL_CORE_COUNT)
#error MCOS_CFG_GLB_CORE_PER_HWCL_MAX is invalid
#endif
#endif /* #if MCOS_HWCL */

#endif /* #if !(BUILD_LIB || USE_OSLIB) */

/*
 * The size check when compiling
 *
 * COMPILETIME_SIZECHECK_X(XX)(identifier, val, expected)
 *   identifier : identifier. It's necessary to put the unique name in the
                  file scope.
 *   val        : size
 *   expected   : expected size
 *
 *   X(XX)      : LE (less than or equal to)
 *              : GE (greater than or equal to)
 *              : LT (less than)
 *              : GT (greater than)
 *              : EQ (equal to)
 *              : NE (not equal to)
 *
 *  These macro functions are used when preprocesser is not able to check
 *  magnitude relationship like sizeof.
 *  When 'val' and 'expected' don't meet the condition designated in X(XX),
 *  it'll be a compile error.
 */
#define COMPILETIME_SIZECHECK_LE(identifier, val, expected)   \
    typedef int8_t mcos_sizecheck_le_##identifier[((val) <= (expected)) ? ARYNUM_OK : ARYNUM_ERR] /* NOTE: If a compilation error occurs here, see above comment */

#define COMPILETIME_SIZECHECK_GE(identifier, val, expected)   \
    typedef int8_t mcos_sizecheck_ge_##identifier[((val) >= (expected)) ? ARYNUM_OK : ARYNUM_ERR] /* NOTE: If a compilation error occurs here, see above comment */

#define COMPILETIME_SIZECHECK_LT(identifier, val, expected)   \
    typedef int8_t mcos_sizecheck_lt_##identifier[((val) < (expected)) ? ARYNUM_OK : ARYNUM_ERR] /* NOTE: If a compilation error occurs here, see above comment */

#define COMPILETIME_SIZECHECK_GT(identifier, val, expected)   \
    typedef int8_t mcos_sizecheck_gt_##identifier[((val) > (expected)) ? ARYNUM_OK : ARYNUM_ERR] /* NOTE: If a compilation error occurs here, see above comment */

#define COMPILETIME_SIZECHECK_EQ(identifier, val, expected)   \
    typedef int8_t mcos_sizecheck_eq_##identifier[((val) == (expected)) ? ARYNUM_OK : ARYNUM_ERR] /* NOTE: If a compilation error occurs here, see above comment */

#define COMPILETIME_SIZECHECK_NE(identifier, val, expected)   \
    typedef int8_t mcos_sizecheck_ne_##identifier[((val) != (expected)) ? ARYNUM_OK : ARYNUM_ERR] /* NOTE: If a compilation error occurs here, see above comment */

#if !MCOS_HWCL
/* No clustering. Revert to base definitions */
#undef  MCOS_CFG_GLB_HWCL_MAX
#undef  MCOS_CFG_GLB_CORE_PER_HWCL_MAX
#undef  MCOS_CFG_GLB_THR_PER_CORE_MAX
#define MCOS_CFG_GLB_HWCL_MAX   (MCOS_CFG_HWCL_ID)

#if !MCOS_AUTOSAR
#define MCOS_CFG_GLB_CORE_PER_HWCL_MAX  (MP_CONTROL_CORE_COUNT)
#define MCOS_CFG_GLB_THR_PER_CORE_MAX   (MCOS_CFG_THR_MAX)
#else /* #if !MCOS_AUTOSAR */
#define MCOS_CFG_GLB_CORE_PER_HWCL_MAX  (mcos_mkconfig.control_core_count)
#define MCOS_CFG_GLB_THR_PER_CORE_MAX   (mcos_mkconfig.thr_max)
#endif /* #if !MCOS_AUTOSAR */
#endif /* #if !MCOS_HWCL */

/* Max TCB per HW cluster */
#define MCOS_TCB_HWCL       (MCOS_CFG_GLB_THR_PER_CORE_MAX * MCOS_CFG_GLB_CORE_PER_HWCL_MAX)

/* MAX TID per HW cluster (migratable TID follow affinity */
#define MCOS_TID_HWCL       (2 * MCOS_TCB_HWCL)

/* Make HWCLID 1 if it is 0 */
#define HWCL_HWCLID     MCOS_CFG_HWCL_ID

/* Base and end LCID for this cluster */
#define HWCL_BASE_LCID  (((HWCL_HWCLID - 1) * MCOS_CFG_GLB_CORE_PER_HWCL_MAX) + 1)
#if !MCOS_AUTOSAR
#define HWCL_END_LCID   (HWCL_BASE_LCID + MP_CONTROL_CORE_COUNT - 1)
#else /* #if !MCOS_AUTOSAR */
#define HWCL_END_LCID   (HWCL_BASE_LCID + (mcos_mkconfig.control_core_count) - 1)
#endif /* #if !MCOS_AUTOSAR */

/* Base and end TID for this cluster */
#if (HWCL_HWCLID == 1U)
#define HWCL_BASE_TID           (1)
#else  /* (HWCL_HWCLID == 1U) */
#define HWCL_BASE_TID           (((HWCL_HWCLID - 1) * MCOS_TID_HWCL) + 1)
#endif  /* (HWCL_HWCLID == 1U) */

#define HWCL_END_TID            (HWCL_BASE_TID + MCOS_TCB_HWCL - 1)

/* Migratable TIDs base and end for this cluster */
#define HWCL_BASE_MTID          (HWCL_BASE_TID + MCOS_TCB_HWCL)
#define HWCL_END_MTID           (HWCL_BASE_MTID + MCOS_TCB_HWCL - 1)


/* Max TCB on self cluster */
#define MCOS_TCB_HWCL_SELF      (MCOS_CFG_GLB_THR_PER_CORE_MAX * MP_CONTROL_CORE_COUNT)

/* Base and end TID for self cluster */
#define HWCL_BASE_TID_SELF      HWCL_BASE_TID
#define HWCL_END_TID_SELF       (HWCL_BASE_TID + MCOS_TCB_HWCL_SELF - 1)

/* Migratable TIDs base and end for self cluster */
#define HWCL_BASE_MTID_SELF     HWCL_BASE_MTID
#define HWCL_END_MTID_SELF      (HWCL_BASE_MTID_SELF + MCOS_TCB_HWCL_SELF - 1)


#endif /* #ifndef MCOS_DEF_H */
