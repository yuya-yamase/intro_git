/*
    Copyright (C) 2017 By eSOL Co.,Ltd. Tokyo, Japan

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
[mcos_ar_hook_code.h] - MCOS autosar hook interface header
****************************************************************************/
#ifndef MCOS_AR_HOOK_CODE_H
#define MCOS_AR_HOOK_CODE_H

#define MCOS_HOOK_PRODUCT_AUTOSAR   0x02000000UL

#define MCOS_HOOK_MODULE_AR_SRC                (MCOS_HOOK_PRODUCT_AUTOSAR | 0x00010000UL)
#define MCOS_HOOK_FILE_AR_MULTICORE            (MCOS_HOOK_MODULE_AR_SRC | 0x00000100UL)
#define MCOS_HOOK_FILE_AR_START_OS             (MCOS_HOOK_MODULE_AR_SRC | 0x00000200UL)
#define MCOS_HOOK_FILE_AR_SVC_IF               (MCOS_HOOK_MODULE_AR_SRC | 0x00000300UL)
#define MCOS_HOOK_FILE_AR_SUPPORT              (MCOS_HOOK_MODULE_AR_SRC | 0x00000400UL)
#define MCOS_HOOK_AR_MULTICORE_CALLBACK        (MCOS_HOOK_FILE_AR_MULTICORE | 0x00000001UL)
#define MCOS_HOOK_AR_MULTICORE_SHUTDOWN        (MCOS_HOOK_FILE_AR_MULTICORE | 0x00000002UL)
#define MCOS_HOOK_AR_START_INIT_1              (MCOS_HOOK_FILE_AR_START_OS | 0x00000001UL)
#define MCOS_HOOK_AR_START_INIT_2              (MCOS_HOOK_FILE_AR_START_OS | 0x00000002UL)
#define MCOS_HOOK_AR_START_INIT_3              (MCOS_HOOK_FILE_AR_START_OS | 0x00000003UL)
#define MCOS_HOOK_AR_START_APPMODE_INVALID     (MCOS_HOOK_FILE_AR_START_OS | 0x00000004UL)
#define MCOS_HOOK_AR_START_OS                  (MCOS_HOOK_FILE_AR_START_OS | 0x00000005UL)
#define MCOS_HOOK_AR_START_CORE                (MCOS_HOOK_FILE_AR_START_OS | 0x00000006UL)
#define MCOS_HOOK_AR_START_NON_AUTOSAR_CORE    (MCOS_HOOK_FILE_AR_START_OS | 0x00000007UL)
#define MCOS_HOOK_AR_START_INIT_SYSTEM_COUNTER (MCOS_HOOK_FILE_AR_START_OS | 0x00000008UL)
#define MCOS_HOOK_AR_START_INIT_C1ISR          (MCOS_HOOK_FILE_AR_START_OS | 0x00000009UL)
#define MCOS_HOOK_AR_START_INIT_C2ISR          (MCOS_HOOK_FILE_AR_START_OS | 0x0000000AUL)
#define MCOS_HOOK_AR_SYSCALL_ERROR             (MCOS_HOOK_FILE_AR_SVC_IF | 0x00000001UL)
#define MCOS_HOOK_AR_INCONSISTENT_ERROR        (MCOS_HOOK_FILE_AR_SUPPORT | 0x00000001UL)


#endif /* #ifndef MCOS_AR_HOOK_CODE_H */
