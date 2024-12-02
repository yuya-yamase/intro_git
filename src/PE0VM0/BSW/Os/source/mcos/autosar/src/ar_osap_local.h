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
[ar_osap_local.h] - OSApplication local header
****************************************************************************/

#ifndef AR_OSAP_LOCAL_H
#define AR_OSAP_LOCAL_H

#include "ar_osap.h"
#include "ar_kernel_impl.h"
#include "mcos_stack_magic.h"

struct ar_osap_stack_info_st {
    void    *address;   /* stack lower address */
    uint32  size;       /* in bytes */
};
typedef struct ar_osap_stack_info_st ar_osap_stack_info_t;

#ifdef OS_CFG_H
#if (AR_OS_EXIST_OSAP == STD_ON)

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_osap_config_t           ar_osap_configs[AR_OS_NUM_OSAPPLICATIONS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_osap_stack_info_t       ar_osap_stack_table[AR_OS_NUM_OSAPPLICATIONS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #if (AR_OS_EXIST_OSAP == STD_ON) */
#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_osap_config_t           ar_osap_configs[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_osap_stack_info_t       ar_osap_stack_table[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */


#define AR_GET_OSAPCONFIG(id) (&ar_osap_configs[(id)])


#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)
#ifdef OS_CFG_H

#if (AR_OS_EXIST_TRUSTED_FUNCTION == STD_ON)

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_tfn_config_t ar_tfn_configs[AR_OS_NUM_TRUSTED_FUNCTIONS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #if (AR_OS_EXIST_TRUSTED_FUNCTION == STD_ON) */

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const ar_tfn_config_t ar_tfn_configs[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */


#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || (AR_OS_USE_MULTICORE == STD_ON)
#ifdef OS_CFG_H

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern ar_osapcb_t* const ar_osapcb_ptr_table[AR_OS_NUM_OSAPPLICATIONS];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#else /* #ifdef OS_CFG_H */

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern ar_osapcb_t* const ar_osapcb_ptr_table[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#endif /* #ifdef OS_CFG_H */
#endif /* #if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) || (AR_OS_USE_MULTICORE == STD_ON) */


#if ( (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) && (AR_OS_USE_STACKMONITORING == STD_ON) )
/*---------------------------------------------------------------------------
  ar_check_osap_isr_stack_size

  Input     :   p_osapconfig
            :   size
  Output    :   none
  Return    :   none
  Note      :
 ---------------------------------------------------------------------------*/
LOCAL_INLINE void ar_check_osap_isr_stack_size(const ar_osap_config_t *p_osapconfig, uint32 size);
LOCAL_INLINE void ar_check_osap_isr_stack_size(const ar_osap_config_t *p_osapconfig, uint32 size)
{
    uint32          stack_top;
    uint32          stack_bottom;
    uint32          reserved;
    ApplicationType osapid;
    uint32          sp;

    osapid = p_osapconfig->osap_id;

    /*
     * Get osap stack sp
     */
    sp = (uint32)p_osapconfig->p_osapcb->osap_sp;
    stack_top = (uint32)ar_osap_stack_table[osapid].address;
    stack_bottom = stack_top + (uint32)ar_osap_stack_table[osapid].size;

    reserved = stack_top + size;
    if ( (sp <= stack_top) || (stack_bottom < sp) || (sp <= reserved) )
    {
        /* Restore osap stack magic */
        *((uint32 *)stack_top) = (uint32_t)MCOS_STACK_MAGIC;
        ar_stack_overflow();
    }
    else
    {
        /* Nothing to do */
    }
}

/*---------------------------------------------------------------------------
  ar_check_osap_hook_stack_size

  Input     :   p_osapconfig
  Output    :   none
  Return    :   none
  Note      :
 ---------------------------------------------------------------------------*/
LOCAL_INLINE void ar_check_osap_hook_stack_size(const ar_osap_config_t *p_osapconfig);
LOCAL_INLINE void ar_check_osap_hook_stack_size(const ar_osap_config_t *p_osapconfig)
{
    uint32          stack_top;
    uint32          stack_bottom;
    uint32          reserved;
    ApplicationType osapid;
    uint32          sp;

    osapid = p_osapconfig->osap_id;

    /*
     * Get osap stack sp
     */
    sp = (uint32)p_osapconfig->p_osapcb->osap_sp;
    stack_top = (uint32)ar_osap_stack_table[osapid].address;
    stack_bottom = stack_top + (uint32)ar_osap_stack_table[osapid].size;

    reserved = stack_top + (uint32)USER_CFG_MCOS_CFG_AR_HOOK_STACKSIZE();
    if ( (sp <= stack_top) || (stack_bottom < sp) || (sp <= reserved) )
    {
        /* Restore osap stack magic */
        *((uint32 *)stack_top) = (uint32_t)MCOS_STACK_MAGIC;
        ar_stack_overflow();
    }
    else
    {
        /* Nothing to do */
    }
}

/*---------------------------------------------------------------------------
  ar_check_osap_stack_magic_number

  Input     :   p_osapconfig
  Output    :   none
  Return    :   none
  Note      :
 ---------------------------------------------------------------------------*/
LOCAL_INLINE void ar_check_osap_stack_magic_number(const ar_osap_config_t *p_osapconfig);
LOCAL_INLINE void ar_check_osap_stack_magic_number(const ar_osap_config_t *p_osapconfig)
{
    uint32          stack_top;
    ApplicationType osapid;

    osapid = p_osapconfig->osap_id;

    /*
     * Get osap stack sp
     */
    stack_top = (uint32)ar_osap_stack_table[osapid].address;
    if (*((const uint32 *)stack_top) != (uint32_t)MCOS_STACK_MAGIC)
    {
        /* Restore osap stack magic */
        *((uint32 *)stack_top) = (uint32_t)MCOS_STACK_MAGIC;
        ar_stack_overflow();
    }
    else
    {
        /* Nothing to do */
    }
}
#endif /* ( (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) && (AR_OS_USE_STACKMONITORING == STD_ON) ) */

#endif /* AR_OSAP_LOCAL_H */
