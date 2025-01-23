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
[ar_svc_id.h] - SVC ID (index) for ar_svc_table
****************************************************************************/

#ifndef AR_SVC_ID_H_
#define AR_SVC_ID_H_

#define AR_SVCID_NUM                            68  /* use in assembly source code */

#define AR_SVCID_ENABLEALLINTERRUPTS            (0x00U)
#define AR_SVCID_DISABLEALLINTERRUPTS           (0x01U)
#define AR_SVCID_RESUMEALLINTERRUPTS            (0x02U)
#define AR_SVCID_SUSPENDALLINTERRUPTS           (0x03U)
#define AR_SVCID_RESUMEOSINTERRUPTS             (0x04U)
#define AR_SVCID_SUSPENDOSINTERRUPTS            (0x05U)
#define AR_SVCID_DISABLEINTERRUPTSOURCE         (0x06U)
#define AR_SVCID_ENABLEINTERRUPTSOURCE          (0x07U)
#define AR_SVCID_CHECKTASKMEMORYACCESS          (0x08U)
#define AR_SVCID_CHECKISRMEMORYACCESS           (0x09U)
#define AR_SVCID_CHECKOBJECTACCESS              (0x0AU)
#define AR_SVCID_CHECKOBJECTOWNERSHIP           (0x0BU)
#define AR_SVCID_CONTROLIDLE                    (0x0CU)
#define AR_SVCID_GETAPPLICATIONSTATE            (0x0DU)
#define AR_SVCID_GETACTIVEAPPLICATIONMODE       (0x0EU)
/* (0x0FU) */
/* (0x10U) */
#define AR_SVCID_AR_GET_ERRHK_SVCID             (0x11U)
#define AR_SVCID_AR_GET_ERRHK_PARAM             (0x12U)
#define AR_SVCID_SHUTDOWNOS                     (0x13U)
#define AR_SVCID_SHUTDOWNALLCORES               (0x14U)
#define AR_SVCID_GETNUMBEROFACTIVATEDCORES      (0x15U)
#define AR_SVCID_ACTIVATETASK                   (0x16U)
#define AR_SVCID_TERMINATETASK                  (0x17U)
#define AR_SVCID_CHAINTASK                      (0x18U)
#define AR_SVCID_SCHEDULE                       (0x19U)
#define AR_SVCID_GETTASKSTATE                   (0x1AU)
#define AR_SVCID_AR_ILLEGAL_EXIT_TASK           (0x1BU)
#define AR_SVCID_SETEVENT                       (0x1CU)
#define AR_SVCID_CLEAREVENT                     (0x1DU)
#define AR_SVCID_GETEVENT                       (0x1EU)
#define AR_SVCID_WAITEVENT                      (0x1FU)
#define AR_SVCID_GETRESOURCE                    (0x20U)
#define AR_SVCID_RELEASERESOURCE                (0x21U)
#define AR_SVCID_INCREMENTCOUNTER               (0x22U)
#define AR_SVCID_GETCOUNTERVALUE                (0x23U)
#define AR_SVCID_GETELAPSEDVALUE                (0x24U)
#define AR_SVCID_GETALARMBASE                   (0x25U)
#define AR_SVCID_GETALARM                       (0x26U)
#define AR_SVCID_SETRELALARM                    (0x27U)
#define AR_SVCID_SETABSALARM                    (0x28U)
#define AR_SVCID_CANCELALARM                    (0x29U)
#define AR_SVCID_CALLTRUSTEDFUNCTION            (0x2AU)
#define AR_SVCID_AR_IOC_SEND                    (0x2BU)
#define AR_SVCID_AR_IOC_WRITE                   (0x2CU)
#define AR_SVCID_AR_IOC_RECEIVE                 (0x2DU)
#define AR_SVCID_AR_IOC_READ                    (0x2EU)
#define AR_SVCID_AR_IOC_EMPTY_QUEUE             (0x2FU)
#define AR_SVCID_GETSPINLOCK                    (0x30U)
#define AR_SVCID_RELEASESPINLOCK                (0x31U)
#define AR_SVCID_TRYTOGETSPINLOCK               (0x32U)
#define AR_SVCID_RAISEINTERCOREINTERRUPT        (0x33U)
#define AR_SVCID_GETSPINLOCKSKIPERRORCHK        (0x34U)
#define AR_SVCID_RELEASESPINLOCKSKIPERRORCHK    (0x35U)
#define AR_SVCID_TRYTOGETSPINLOCKSKIPERRORCHK   (0x36U)
#define AR_SVCID_AR_ERRORHOOK_CALL              (0x37U)
#define AR_SVCID_ACTIVATETASKASYN               (0x38U)
#define AR_SVCID_SETEVENTASYN                   (0x39U)
#define AR_SVCID_CLEARPENDINGINTERRUPT          (0x3AU)
#define AR_SVCID_READPERIPHERAL8                (0x3BU)
#define AR_SVCID_READPERIPHERAL16               (0x3CU)
#define AR_SVCID_READPERIPHERAL32               (0x3DU)
#define AR_SVCID_WRITEPERIPHERAL8               (0x3EU)
#define AR_SVCID_WRITEPERIPHERAL16              (0x3FU)
#define AR_SVCID_WRITEPERIPHERAL32              (0x40U)
#define AR_SVCID_MODIFYPERIPHERAL8              (0x41U)
#define AR_SVCID_MODIFYPERIPHERAL16             (0x42U)
#define AR_SVCID_MODIFYPERIPHERAL32             (0x43U)

#endif /* AR_SVC_ID_H_ */

