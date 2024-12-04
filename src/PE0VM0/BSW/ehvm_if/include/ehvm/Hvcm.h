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
[Hvcm.h] - Hvcm module's header
****************************************************************************/

#ifndef HVCM_H
#define HVCM_H

#include "ehvm_types.h"

/* denylist Bit denylist */
#define EHVM_DENYLIST_0_BITPOS_VCC_TX                        (0x00000001U)
#define EHVM_DENYLIST_0_BITPOS_VCC_RX                        (0x00000002U)
#define EHVM_DENYLIST_0_BITPOS_VWDT_SETMODE                  (0x00000004U)
#define EHVM_DENYLIST_0_BITPOS_VWDT_SETTRIGGER               (0x00000008U)
#define EHVM_DENYLIST_0_BITPOS_VM_EXIT                       (0x00000010U)
#define EHVM_DENYLIST_0_BITPOS_VM_RESET_FACTOR               (0x00000020U)
#define EHVM_DENYLIST_0_BITPOS_EM_RX                         (0x00000040U)
#define EHVM_DENYLIST_0_BITPOS_VCC_RINGBUFFER_CLEAR          (0x00000080U)
#define EHVM_DENYLIST_0_BITPOS_VCC_DETECT_OVERWRITE          (0x00000100U)
#define EHVM_DENYLIST_0_BITPOS_SETDENYLIST                   (0x00000200U)
#define EHVM_DENYLIST_0_BITPOS_GETDENYLIST                   (0x00000400U)
#define EHVM_DENYLIST_0_BITPOS_SET_SCHTBL                    (0x00000800U)
#define EHVM_DENYLIST_0_BITPOS_GET_SCHTBL                    (0x00001000U)
#define EHVM_DENYLIST_0_BITPOS_VM_ENABLE_SUPPRESS_VM_NORMAL  (0x00002000U)
#define EHVM_DENYLIST_0_BITPOS_VM_DISABLE_SUPPRESS_VM_NORMAL (0x00004000U)
#define EHVM_DENYLIST_0_BITPOS_VM_GET_STARTUP_STATUS         (0x00008000U)
#define EHVM_DENYLIST_0_BITPOS_VM_RESET_VM                   (0x00010000U)
#define EHVM_DENYLIST_0_BITPOS_VCC_CLEAR_CHANNEL             (0x00020000U)
#define EHVM_DENYLIST_0_BITPOS_VM_GET_WAKEUP_FACTOR          (0x00040000U)
#define EHVM_DENYLIST_0_BITPOS_VM_SET_WAKEUP_FACTOR          (0x00080000U)
#define EHVM_DENYLIST_0_BITPOS_VM_CLEAR_WAKEUP_FACTOR        (0x00100000U)
#define EHVM_DENYLIST_0_BITPOS_VM_ENABLE_WAKEUP_FACTOR       (0x00200000U)
#define EHVM_DENYLIST_0_BITPOS_VM_DISABLE_WAKEUP_FACTOR      (0x00400000U)
#define EHVM_DENYLIST_0_BITPOS_VM_VM_STATUSCHK               (0x00800000U)
#define EHVM_DENYLIST_0_BITPOS_DISABLE_VM_SWITCH             (0x01000000U)
#define EHVM_DENYLIST_0_BITPOS_ENABLE_VM_SWITCH              (0x02000000U)

extern ehvm_std_return_t  ehvm_hvc_set_access_deny_list( EhvmConstR ehvm_context_id_t contextId, EhvmConstR ehvm_uint32_t * EhvmConstR denylist );
extern ehvm_std_return_t  ehvm_hvc_get_access_deny_list( EhvmConstR ehvm_context_id_t contextId, ehvm_uint32_t * EhvmConstR denylist );

#endif /* HVCM_H */
