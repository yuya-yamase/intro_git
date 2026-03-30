/*
    Copyright (C) 2018 By eSOL Co.,Ltd. Tokyo, Japan

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
[ar_ioc_local.h] - IOC local header
****************************************************************************/

#ifndef AR_IOC_LOCAL_H
#define AR_IOC_LOCAL_H

#include "ar_ioc.h"

#ifdef OS_CFG_H
#if (AR_OS_EXIST_IOC == STD_ON)

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_ioc_config_t            ar_ioc_configs[AR_OS_NUM_IOC_COMMUNICATIONS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const void * const               ar_ioc_initial_values_table[AR_OS_NUM_IOC_COMMUNICATIONS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_ioc_receiver_config_t   ar_ioc_receiver_configs[AR_OS_NUM_IOC_RECEIVERS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_ioc_sender_config_t     ar_ioc_sender_configs[AR_OS_NUM_IOC_SENDERS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#if (AR_OS_EXIST_QUEUED_IOC == STD_ON)

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern ar_ioccb_t * const               ar_ioccb_ptr_table[AR_OS_NUM_QUEUED_IOCS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #if (AR_OS_EXIST_QUEUED_IOC == STD_ON) */
#endif /* #if (AR_OS_EXIST_IOC == STD_ON) */
#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_ioc_config_t            ar_ioc_configs[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const void * const               ar_ioc_initial_values_table[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_ioc_receiver_config_t   ar_ioc_receiver_configs[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_ioc_sender_config_t     ar_ioc_sender_configs[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern ar_ioccb_t * const               ar_ioccb_ptr_table[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define AR_IOC_LOCAL_ENABLE

#endif /* #ifdef OS_CFG_H */


#ifdef AR_IOC_LOCAL_ENABLE

AR_LOCAL_FORCE_INLINE mcos_id_t ar_get_ioc_receiver_core_id(
    const ar_ioc_receiver_config_t * const p_receiver_config);

AR_LOCAL_FORCE_INLINE mcos_id_t ar_get_ioc_receiver_core_id(
    const ar_ioc_receiver_config_t * const p_receiver_config)
{
    return p_receiver_config->p_osapconfig->lcid;
}


#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
AR_LOCAL_FORCE_INLINE void ar_ioc_call_pullcb_main(
    const mkcb_t * const mkcb,
    const ar_ioc_receiver_config_t  *p_receiver_config);
AR_LOCAL_FORCE_INLINE void ar_ioc_call_pullcb_main(
    const mkcb_t * const mkcb,
    const ar_ioc_receiver_config_t  *p_receiver_config)
{
    uint16          inest;

    inest = mcos_mkcc_inest_get(mkcb);
    if ((uint32)inest != (uint32)0U)
    {
        /* called from mkmsg */
        void*   prev_stack_addr;
        uint32  prev_stack_size;
        uint32  prev_mpu_stack_info1;
        uint32  prev_mpu_stack_info2;
        uint32  prev_mpu_stack_info3;
        clscb_t *clscb;

        clscb = mcos_mkcc_get_clscb(mkcb);
        /* save current stack setting in MPU */
        xmcos_ar_get_mpu_region_stack(clscb, &prev_stack_addr, &prev_stack_size,
                                    &prev_mpu_stack_info1, &prev_mpu_stack_info2, &prev_mpu_stack_info3);

        p_receiver_config->receiver_pullcb();

        xmcos_ar_set_mpu_region_stack(clscb, prev_stack_addr, prev_stack_size,
                                        prev_mpu_stack_info1, prev_mpu_stack_info2, prev_mpu_stack_info3);
    }
    else
    {
        /* called from task */
        p_receiver_config->receiver_pullcb();
    }
}
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */


AR_LOCAL_FORCE_INLINE void ar_ioc_call_pullcb(
    const mkcb_t * const mkcb,
    const IocType receiver_id);
AR_LOCAL_FORCE_INLINE void ar_ioc_call_pullcb(
    const mkcb_t * const mkcb,
    const IocType receiver_id)
{
    const ar_ioc_receiver_config_t  *p_receiver_config;

    p_receiver_config = &ar_ioc_receiver_configs[receiver_id];

    if (p_receiver_config->receiver_pullcb != NULL)
    {
        clscb_t                 *clscb;
        const ar_osap_config_t  *p_runosap_saved;
        const ar_osap_config_t  *p_currentosap_saved;

        clscb = mcos_mkcc_get_clscb(mkcb);

        /*
         * Call ReceiverPullCB
         */
        AR_CALL_LEVEL_ENTER(clscb, AR_CL_RCVPLCB);
        clscb->aroscb.in_rcvplcb = TRUE;

        p_runosap_saved = clscb->aroscb.p_runosap;
        p_currentosap_saved = clscb->aroscb.p_currentosap;
        clscb->aroscb.p_runosap = p_receiver_config->p_osapconfig;
        clscb->aroscb.p_currentosap = p_receiver_config->p_osapconfig;

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

        ar_ioc_call_pullcb_main(mkcb, p_receiver_config);

#else
        p_receiver_config->receiver_pullcb();
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

        clscb->aroscb.p_runosap = p_runosap_saved;
        clscb->aroscb.p_currentosap = p_currentosap_saved;

        AR_CALL_LEVEL_EXIT(clscb, AR_CL_RCVPLCB);
        clscb->aroscb.in_rcvplcb = FALSE;
    }
    else
    {
        /* Nothing to do */
    }
}

AR_LOCAL_FORCE_INLINE IocType ar_get_ioc_id_by_ar_ioc_config(
    const ar_ioc_config_t *p_config);
AR_LOCAL_FORCE_INLINE IocType ar_get_ioc_id_by_ar_ioc_config(
    const ar_ioc_config_t *p_config)
{
    return (IocType)(((uint32_t)p_config - (uint32_t)ar_ioc_configs) / sizeof(ar_ioc_config_t));
}

#endif /* #ifdef AR_IOC_LOCAL_ENABLE */

#endif /* AR_IOC_LOCAL_H */
