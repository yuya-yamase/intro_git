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
 [ ehvm_types_api_em.h ] - EHVM API EM types header
****************************************************************************/

#ifndef EHVM_TYPES_API_EM_H
#define EHVM_TYPES_API_EM_H

/****************************************************************************
    macro definitions
****************************************************************************/

#define EHVM_EM_ERROR_CAUSE_SYSERR                     (0x00000010U)
#define EHVM_EM_ERROR_CAUSE_FETRAP                     (0x00000030U)
#define EHVM_EM_ERROR_CAUSE_RIE                        (0x00000060U)
#define EHVM_EM_ERROR_CAUSE_FPE                        (0x00000070U)
#define EHVM_EM_ERROR_CAUSE_UCPOP                      (0x00000080U)
#define EHVM_EM_ERROR_CAUSE_MDPMIP                     (0x00000090U)
#define EHVM_EM_ERROR_CAUSE_PIE                        (0x000000A0U)
#define EHVM_EM_ERROR_CAUSE_MAE                        (0x000000C0U)
#define EHVM_EM_ERROR_CAUSE_BGFEINT                    (0x000000D0U)
#define EHVM_EM_ERROR_CAUSE_FENMI                      (0x000000E0U)
#define EHVM_EM_ERROR_CAUSE_FEINT                      (0x000000F0U)
#define EHVM_EM_ERROR_CAUSE_VWDT                       (0x00000100U)
#define EHVM_EM_ERROR_CAUSE_HVC                        (0x00000200U)
#define EHVM_EM_ERROR_CAUSE_MM_ACC                     (0x00000300U)
#define EHVM_EM_ERROR_CAUSE_DISABLE_VM_SWITCH_TIMEOUT  (0x00000400U)
#define EHVM_EM_ERROR_CAUSE_UC_SPID                    (0x00000500U)
#define EHVM_EM_ERROR_CAUSE_UC_MM_ACC                  (0x00000600U)

#endif  /* EHVM_TYPES_API_EM_H */
