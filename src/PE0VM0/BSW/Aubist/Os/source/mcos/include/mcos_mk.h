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
[mcos_mk.h] - MCOS micro-kernel header
****************************************************************************/
#ifndef MCOS_MK_H
#define MCOS_MK_H

#include "mcos_basic.h"
#include "mcos_cmn.h"

#if defined __V850__
#include "arch/v850/mcos_v850.h"

#elif defined __tile__ /* #if defined __V850__ */
#if defined __GNUC__
#include "arch/tile/mcos_tile.h"
#endif /* defined __GNUC__ */

#elif defined __K1__ /* #elif defined __tile__ */
#if defined __GNUC__
#include "arch/kalray1/mcos_kalray1.h"
#endif /* defined __GNUC__ */

#elif defined __MICROBLAZE__ /* #elif defined __K1__ */
#if defined __GNUC__
#include "arch/microblaze/mcos_microblaze.h"
#endif /* defined __GNUC__ */

#elif defined __arm__ /* defined __MICROBLAZE__ */

#if defined __ghs__
#include "arch/armv7m/mcos_armv7m.h" /* for arm-ghs */
#elif defined __GNUC__ /* defined __ghs__ */
#include "arch/armv8r/mcos_armv8r.h" /* for arm-gcc */
#endif /* #if defined __GNUC__ */

#elif defined __ARMCC_VERSION /* #if defined __GNUC__ */

#if defined __GNUC__
#include "arch/armv8r/mcos_armv8r.h" /* for armclang */
#else  /* #if defined __GNUC__ */
#include "arch/arm/mcos_arm.h" /* for ARMCT5.0x */
#endif /* #if defined __GNUC__ */

#elif defined __Tricore /* __ARMCC_VERSION */

#include "arch/tc162/mcos_tc162.h"

#else /* #elif defined __Tricore */

#endif /* #else */

#include "mcos_cls.h"
#include "mcos_mkmsg.h"
#if !MCOS_AUTOSAR
#include "mcos_clmm.h"
#include "mcos_ns_defs.h"
#include "mcos_ltm.h"
#include "mcos_memcfg.h"

#include "mcos_errno.h"
#include "mcos_memm.h"
#include "mcos_heap.h"
#include "mcos_heapsrv.h"
#include "mcos_timesrv.h"
#include "mcos_lfs.h"
#endif  /* MCOS_AUTOSAR */

#if MCOS_AUTOSAR
void mcos_hwl_mk_sp_error(void);
#endif /* MCOS_AUTOSAR */

#define MSG_RRMSG_MAX_SIZE (((uint32_t)MCOS_CFG_RRMSG_BUFSIZE) \
                            + (sizeof(msg_rrmsnd_t)))

/*
 * In a multi-cluster system using message routing feature, the message property header
 * as an inter-cluster routing message is needed additionally for a normal message unit.
 */

#if MCOS_HWCL
#define MSG_MSG_MAX_SIZE   (((uint32_t)MCOS_CFG_MSG_SIZE_MAX) \
                            + (sizeof(msg_msnd_t))                  \
                            + (sizeof(msg_msnd_size_t)))
#else /* #if MCOS_HWCL */
#define MSG_MSG_MAX_SIZE   (((uint32_t)MCOS_CFG_MSG_SIZE_MAX) \
                            + (sizeof(msg_msnd_t)))
#endif /* #if MCOS_HWCL */

#define MSG_MAX_SIZE  ((MSG_RRMSG_MAX_SIZE > MSG_MSG_MAX_SIZE) ? \
                        MSG_RRMSG_MAX_SIZE : MSG_MSG_MAX_SIZE)


#ifndef MCOS_INTM_BPRI_SHIFT
#error The value of MCOS_INTM_BPRI_SHIFT must be specified.
#endif

#if (MCOS_INTM_BPRI_SHIFT == 0U)
#define MCOS_INTM_BPRI_TO_ADJ(bpri) ( (bpri) )
#define MCOS_INTM_BPRI_ADJ_TO_BPRI(bpri_adj) ( (bpri_adj) )
#else   /* #if (MCOS_INTM_BPRI_SHIFT == 0U) */
#define MCOS_INTM_BPRI_TO_ADJ(bpri) ( (bpri) / (MCOS_INTM_BPRI_COEFT) )
#define MCOS_INTM_BPRI_ADJ_TO_BPRI(bpri_adj) ( (bpri_adj) * (MCOS_INTM_BPRI_COEFT) )
#endif  /* #if (MCOS_INTM_BPRI_SHIFT == 0U) */

#define MCOS_INTM_BPRI_ADJ_MIN  MCOS_INTM_BPRI_TO_ADJ(MCOS_INTM_BPRI_MIN)
#define MCOS_INTM_BPRI_ADJ_MAX  MCOS_INTM_BPRI_TO_ADJ(MCOS_INTM_BPRI_MAX)


#if (MCOS_INTM_BPRI_ADJ_MAX > MCOS_INTM_BPRI_ADJ_MIN)

#if (MCOS_INTM_BPRI_ADJ_MAX > 0U)
/* convert BIOS cpu priority into AUTOSAR cpu priority */
#define MCOS_INTM_BPRI_TO_APRI(bpri)   ((int32_t)MCOS_INTM_BPRI_ADJ_MIN - MCOS_INTM_BPRI_TO_ADJ(bpri))
/* convert AUTOSAR cpu priority into BIOS cpu priority */
#define MCOS_INTM_APRI_TO_BPRI(apri)   MCOS_INTM_BPRI_ADJ_TO_BPRI( -((int32_t)MCOS_INTM_BPRI_ADJ_MIN + (apri)) )
/* maximam AUTOSAR cpu priority */
#define MCOS_INTM_APRI_MAX   (MCOS_INTM_BPRI_ADJ_MIN - MCOS_INTM_BPRI_ADJ_MAX)
#else /* #if (MCOS_INTM_BPRI_ADJ_MIN > 0U) */
#error MCOS_INTM_BPRI_MIN and/or MCOS_INTM_BPRI_MAX are wrongly specified.
#endif /* #if (MCOS_INTM_BPRI_ADJ_MAX > 0U) */

#else /* #if (MCOS_INTM_BPRI_ADJ_MAX > MCOS_INTM_BPRI_ADJ_MIN) */

#if (MCOS_INTM_BPRI_ADJ_MIN > 0U)
/* convert BIOS cpu priority into AUTOSAR cpu priority */
#define MCOS_INTM_BPRI_TO_APRI(bpri)   (MCOS_INTM_BPRI_TO_ADJ(bpri) - (int32_t)MCOS_INTM_BPRI_ADJ_MIN)
/* convert AUTOSAR cpu priority into BIOS cpu priority */
#define MCOS_INTM_APRI_TO_BPRI(apri)   MCOS_INTM_BPRI_ADJ_TO_BPRI((int32_t)MCOS_INTM_BPRI_ADJ_MIN + (apri))
/* maximam AUTOSAR cpu priority */
#define MCOS_INTM_APRI_MAX   (MCOS_INTM_BPRI_ADJ_MAX - MCOS_INTM_BPRI_ADJ_MIN)
#else /* #if (MCOS_INTM_BPRI_ADJ_MIN > 0U) */
#error MCOS_INTM_BPRI_MIN and/or MCOS_INTM_BPRI_MAX are wrongly specified.
#endif /* #if (MCOS_INTM_BPRI_ADJ_MIN > 0U) */

#endif /* #if (MCOS_INTM_BPRI_ADJ_MAX > MCOS_INTM_BPRI_ADJ_MIN) */

#define MCOS_INTM_APRI_MIN       0

#if !MCOS_AUTOSAR
/* partition reboot */
mcos_er_t mcos_hwl_partition_reboot(mcos_id_t partid);
#endif /* #if !MCOS_AUTOSAR */

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

void mcos_main(const void * const ptr);
void mcos_main_slave(const int32_t pcid, const void * const ptr);

/* ar init */
void ar_init(void);
void ar_indirect_call_idle_loop(const mkcb_t *mkcb);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"


#endif /* #ifndef MCOS_MK_H */

