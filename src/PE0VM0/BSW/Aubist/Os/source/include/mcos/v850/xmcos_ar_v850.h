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
[xmcos_ar_v850.h] - MCOS interface header
****************************************************************************/
#ifndef XMCOS_AR_V850_H
#define XMCOS_AR_V850_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <mcos/mcos_ar_switch.h>

#include <hal/cpu/v850/hal/hal_v850_cfg.h>
#include "ar_user_cfg_def.h"

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

/*
 * MPU configuratin table
 */
struct v850_memory_region_cfg_st
{
    uint32 lower_addr;
    uint32 upper_addr;
    uint32 mpat;
};
typedef struct v850_memory_region_cfg_st v850_memory_region_cfg_t;


#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const v850_memory_region_cfg_t * const ar_osap_regions_table[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern v850_memory_region_cfg_t * const ar_osap_regions_table_ram[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const uint32 ar_appid_mode_table[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"


typedef struct {
    uint32 start;       /* lower address */
    uint32 end_size;    /* upper address or size*/
} xmcos_ar_region_info;


#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const void * const __ghsbeginos_rsv1_region;

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const void * const __ghsendos_rsv1_region;

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"


#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const xmcos_ar_region_info ar_reserved_region_table[];

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_32
#include "Os_MemMap.h"

extern const uint32 ar_mpu_region_usage;

#define OS_STOP_SEC_CONST_32
#include "Os_MemMap.h"


AR_LOCAL_FORCE_INLINE uint32 xmcos_ar_get_memprotect_group_id(ApplicationType osap_id);
AR_LOCAL_FORCE_INLINE void xmcos_ar_set_mpu_regions(ApplicationType osap_id);

#if (AR_ENABLE_CHECK_TASK_MEMORY_ACCESS != 0U) || (AR_ENABLE_CHECK_ISR_MEMORY_ACCESS != 0U)

AR_LOCAL_FORCE_INLINE AccessType xmcos_ar_get_memory_permissions(
    boolean         can_fullaccess,
    const ar_osap_config_t *p_osapconfig,
    ConstMemoryStartAddressType start, MemorySizeType size,
    ConstMemoryStartAddressType stack_lower, MemorySizeType stack_size);
AR_LOCAL_FORCE_INLINE AccessType xmcos_convert_permissions(uint32 mpat, boolean is_supervisor);

AR_LOCAL_FORCE_INLINE boolean xmcos_ar_spacea_contains_spaceb(
    ConstMemoryStartAddressType lower_addr_a,
    MemorySizeType         size_a,
    ConstMemoryStartAddressType lower_addr_b,
    MemorySizeType         size_b);

AR_LOCAL_FORCE_INLINE boolean xmcos_is_contained_in_stack_space(
    ConstMemoryStartAddressType stack_lower_addr,
    MemorySizeType         stack_size,
    ConstMemoryStartAddressType check_lower_addr,
    MemorySizeType         check_size);
AR_LOCAL_FORCE_INLINE boolean xmcos_is_contained_in_os_rgn1(
    ConstMemoryStartAddressType check_lower_addr,
    MemorySizeType         check_size);
AR_LOCAL_FORCE_INLINE boolean xmcos_is_contained_in_os_rgn2(
    ConstMemoryStartAddressType check_lower_addr,
    MemorySizeType         check_size,
    CoreIdType             coreid);

#endif /* #if (AR_ENABLE_CHECK_TASK_MEMORY_ACCESS != 0U) || (AR_ENABLE_CHECK_ISR_MEMORY_ACCESS != 0U) */

AR_LOCAL_FORCE_INLINE boolean xmcos_ar_can_call_fnc_service(void);
#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#if (AR_OS_USE_ERRORHOOK == STD_ON)
AR_LOCAL_FORCE_INLINE boolean xmcos_ar_can_call_errorhook(void);
#endif  /* (AR_OS_USE_ERRORHOOK == STD_ON) */

#if (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON)

#define OS_START_SEC_CODE
#include "Os_MemMap.h"

extern void xmcos_ar_initialize_mpu(CoreIdType coreid);
extern void ar_cpu_update_regions(const v850_memory_region_cfg_t * const regions);
extern void xmcos_ar_update_mpu_rgn_sysstk(const mkcb_t *mkcb, clscb_t *clscb);
extern void xmcos_ar_update_mpu_region_osap_stack(clscb_t *clscb, ApplicationType osap_id);
extern void xmcos_ar_set_mpu_region_stack(clscb_t* clscb,
    void const *addr, uint32 size, uint32 mpu_info1, uint32 mpu_info2, uint32 mpu_info3);
extern void xmcos_ar_set_mpu_region_task_stack(clscb_t* clscb,
    void const *addr, uint32 size, const ar_tcb_t * const p_atcb);
extern void xmcos_ar_get_mpu_region_stack(clscb_t const *clscb,
    void **p_addr, uint32 *p_size, uint32 *p_mpu_info1, uint32 *p_mpu_info2, uint32 *p_mpu_info3);
extern mcos_bool_t xmcos_ar_check_mpu_os_rsv1_region(void);
extern void xmcos_ar_update_mpu_osrsv1_rgn(void);
extern mcos_bool_t xmcos_ar_check_mpu_os_rsv2_region(CoreIdType coreid);
extern void xmcos_ar_update_mpu_osrsv2_rgn(CoreIdType coreid);
extern mcos_bool_t xmcos_ar_check_mpu_ram_table(CoreIdType coreid);
extern void xmcos_ar_update_mpu_ram_table(CoreIdType coreid);


#if (XMCOS_AR_USE_APPLICATION_CHANGED == STD_ON)
extern void xmcos_ar_application_changed(ApplicationType osap_id);
#endif /* #if (XMCOS_AR_USE_APPLICATION_CHANGED == STD_ON) */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"


 /*---------------------------------------------------------------------------
  xmcos_ar_get_memprotect_group_id
     Initialize MPU device
  Input     :   applicaiton ID
  Output    :   none
  Return    :   prs pattern
  Note  :   none
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE uint32
xmcos_ar_get_memprotect_group_id(ApplicationType osap_id)
{
    return ar_appid_mode_table[osap_id];
}

/*---------------------------------------------------------------------------
  xmcos_ar_set_mpu_regions
     Set MPU region for OsApplication
  Input     :   applicaiton ID
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE void
xmcos_ar_set_mpu_regions(ApplicationType osap_id)
{
    sint32  lock;
    lock = hal_cpu_lockAllInt();
    /* osap user regions */
    ar_cpu_update_regions(ar_osap_regions_table_ram[osap_id]);

    hal_cpu_unlockAllInt(lock);
}

#if (AR_ENABLE_CHECK_TASK_MEMORY_ACCESS != 0U) || (AR_ENABLE_CHECK_ISR_MEMORY_ACCESS != 0U)

/*---------------------------------------------------------------------------
  xmcos_convert_permissions

  Input     :   mpat
  Output    :   none
  Return    :   access
  Note  :   none
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE AccessType
xmcos_convert_permissions(uint32 mpat, boolean is_supervisor)
{
    AccessType  access;

    access = (AccessType)AP_NoAccess;

    if (is_supervisor == (boolean)TRUE)
    {
        if ((mpat & (uint32)MPU_MPAT_SX) != 0UL)
        {
            access |= (AccessType)AP_Executable;
        }
        else
        {
            /* Nothing to do */
        }

        if ((mpat & (uint32)MPU_MPAT_SW) != 0UL)
        {
            access |= (AccessType)AP_Writable;
        }
        else
        {
            /* Nothing to do */
        }

        if ((mpat & (uint32)MPU_MPAT_SR) != 0UL)
        {
            access |= (AccessType)AP_Readable;
        }
        else
        {
            /* Nothing to do */
        }
    }
    else
    {
        if ((mpat & (uint32)MPU_MPAT_UX) != 0UL)
        {
            access |= (AccessType)AP_Executable;
        }
        else
        {
            /* Nothing to do */
        }

        if ((mpat & (uint32)MPU_MPAT_UW) != 0UL)
        {
            access |= (AccessType)AP_Writable;
        }
        else
        {
            /* Nothing to do */
        }

        if ((mpat & (uint32)MPU_MPAT_UR) != 0UL)
        {
            access |= (AccessType)AP_Readable;
        }
        else
        {
            /* Nothing to do */
        }
    }
    
    return access;
}

/*---------------------------------------------------------------------------
  xmcos_ar_spacea_contains_spaceb
     return the check result of whether full space 'A' contains sub space 'B' or not
  Input     :   lower_addr_a  lower address of space 'A'
            :   size_a        size of space 'A'
            :   lower_addr_b  lower address of space 'B'
            :   size_b         size of space 'B'
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE boolean
xmcos_ar_spacea_contains_spaceb(
    ConstMemoryStartAddressType lower_addr_a,
    MemorySizeType         size_a,
    ConstMemoryStartAddressType lower_addr_b,
    MemorySizeType         size_b
)
{
    ConstMemoryStartAddressType upper_addr_a;
    ConstMemoryStartAddressType upper_addr_b;
    boolean ret;

    upper_addr_a = (ConstMemoryStartAddressType)((MemorySizeType)(lower_addr_a) + size_a);
    upper_addr_b = (ConstMemoryStartAddressType)((MemorySizeType)(lower_addr_b) + size_b);

    if( (lower_addr_a <= lower_addr_b) &&
        (upper_addr_b <= upper_addr_a) )
    {
        ret = (boolean)TRUE;
    }
    else
    {
        ret = (boolean)FALSE;
    }

    return ret;
}

AR_LOCAL_FORCE_INLINE boolean xmcos_is_contained_in_stack_space(
    ConstMemoryStartAddressType stack_lower_addr,
    MemorySizeType         stack_size,
    ConstMemoryStartAddressType check_lower_addr,
    MemorySizeType         check_size)
{
    return xmcos_ar_spacea_contains_spaceb(
        stack_lower_addr,
        stack_size,
        check_lower_addr,
        check_size);
}

AR_LOCAL_FORCE_INLINE boolean xmcos_is_contained_in_os_rgn1(
    ConstMemoryStartAddressType check_lower_addr,
    MemorySizeType         check_size)
{
    ConstMemoryStartAddressType  osrsv1_lower_addr;
    ConstMemoryStartAddressType  osrsv1_upper_addr;
    MemorySizeType          osrsv1_size;

    osrsv1_lower_addr = (ConstMemoryStartAddressType)(&__ghsbeginos_rsv1_region);
    osrsv1_upper_addr = (ConstMemoryStartAddressType)(&__ghsendos_rsv1_region);
    osrsv1_size = (MemorySizeType)osrsv1_upper_addr - (MemorySizeType)osrsv1_lower_addr;

    return xmcos_ar_spacea_contains_spaceb(
        osrsv1_lower_addr,
        osrsv1_size,
        check_lower_addr,
        check_size);
}

AR_LOCAL_FORCE_INLINE boolean xmcos_is_contained_in_os_rgn2(
    ConstMemoryStartAddressType check_lower_addr,
    MemorySizeType         check_size,
    CoreIdType             coreid)
{
    ConstMemoryStartAddressType  osrsv2_lower_addr;
    ConstMemoryStartAddressType  osrsv2_upper_addr;
    MemorySizeType          osrsv2_size;

    /* reserved rom area: all osap can execute and read */
    osrsv2_lower_addr = (ConstMemoryStartAddressType)(ar_reserved_region_table[coreid].start);
    osrsv2_upper_addr = (ConstMemoryStartAddressType)(ar_reserved_region_table[coreid].end_size);
    osrsv2_size = (MemorySizeType)osrsv2_upper_addr - (MemorySizeType)osrsv2_lower_addr;

    return xmcos_ar_spacea_contains_spaceb(
        osrsv2_lower_addr,
        osrsv2_size,
        check_lower_addr,
        check_size);
}

/*---------------------------------------------------------------------------
  xmcos_ar_get_memory_permissions

  Summary   :   Check whether the context(Task or C2ISR) which belongs to
                the specifed osap can access the specifed space or not.
                if accessible, return the access attributes (Read or Write or eXecute)
                else not accessible, return AP_NoAccess

  Input     :   can_fullaccess
            :   osapconfig       configuration of the specified osap
            :   start            the lower address of the space to be checked
            :   size             the size of the space to be checked
            :   stack_lower      the lower address of the stack space used by the osap
            :   stack_size       the size of the stack space used by the osap
  Output    :   none
  Return    :   mask of the access attributes (None or Read or Write or eXecute)
  Note  :   none
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE AccessType
xmcos_ar_get_memory_permissions(
    boolean         can_fullaccess,
    const ar_osap_config_t *p_osapconfig,
    ConstMemoryStartAddressType start, MemorySizeType size,
    ConstMemoryStartAddressType stack_lower, MemorySizeType stack_size)
{
    AccessType access;
    boolean is_contained_in_stack;

    is_contained_in_stack =
        xmcos_is_contained_in_stack_space(stack_lower, stack_size, start, size);

    if (can_fullaccess != (boolean)FALSE)
    {
        if (is_contained_in_stack != (boolean)FALSE)
        {
            /* in the stack with AP_Executable */
            access = (AccessType)(AP_Readable | AP_Writable | AP_Executable | AP_StackSpace);
        }
        else
        {
            access = (AccessType)(AP_Readable | AP_Writable | AP_Executable);
        }
    }
    else
    {
        boolean is_contained_in_osrsv1;
        boolean is_contained_in_osrsv2;

        is_contained_in_osrsv1 = xmcos_is_contained_in_os_rgn1(start, size);
        is_contained_in_osrsv2 =
            xmcos_is_contained_in_os_rgn2(start, size, (CoreIdType)LCID2CPUNO(p_osapconfig->lcid));

        if (is_contained_in_stack != (boolean)FALSE)
        {
            /* in the stack without AP_Executable */
            access = (AccessType)(AP_Readable | AP_Writable | AP_StackSpace);
        }
        else if (is_contained_in_osrsv1 != (boolean)FALSE)
        {
            /* in the os reserved region 1 */
            access = (AccessType)(AP_Readable | AP_Executable);
        }
        else if (is_contained_in_osrsv2 != (boolean)FALSE)
        {
            /* in the os reserved region 2 */
            access = (AccessType)(AP_Readable);
        }
        else
        {
            /* in any OsMemoryRegions to which the osap refers */
            const v850_memory_region_cfg_t * p_table;
            uint32 idx;

            p_table = ar_osap_regions_table[p_osapconfig->osap_id];

            access = (AccessType)(AP_NoAccess);

            for (idx = 0U; idx < (uint32)HAL_V850_NUMBERS_OF_MPU_REGION_USER_AVAILABLE; idx++)
            {
                ConstMemoryStartAddressType  lower_addr;
                ConstMemoryStartAddressType  upper_addr;
                MemorySizeType          region_size;
                boolean                 is_contained;

                lower_addr = (ConstMemoryStartAddressType)(p_table[idx].lower_addr);
                upper_addr = (ConstMemoryStartAddressType)(p_table[idx].upper_addr);
                region_size = (MemorySizeType)upper_addr - (MemorySizeType)lower_addr;
                
                is_contained = 
                    xmcos_ar_spacea_contains_spaceb(lower_addr, region_size, start, size);
                if (is_contained != (boolean)FALSE)
                {
                    access |=
                        xmcos_convert_permissions(p_table[idx].mpat, (boolean)p_osapconfig->osap_trusted);
                }
                else
                {
                    /* Nothing to do */
                }
            }
        }
    }

    return access;
}

#endif /* #if (AR_ENABLE_CHECK_TASK_MEMORY_ACCESS != 0U) || (AR_ENABLE_CHECK_ISR_MEMORY_ACCESS != 0U) */


/*---------------------------------------------------------------------------
  xmcos_ar_can_call_fnc_service

  Input     :   none
  Output    :   none
  Return    :   Whether a sysem service should be executed with call-function
                directly or SVC exception
  Note  :  -
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE boolean
xmcos_ar_can_call_fnc_service(void)
{
    return FALSE;
}

#endif /* (AR_OS_USE_SCALABILITYCLASS_3_OR_4 == STD_ON) */

#if (AR_OS_USE_ERRORHOOK == STD_ON)
/*---------------------------------------------------------------------------
  xmcos_ar_can_call_errorhook

  Input     :   none
  Output    :   none
  Return    :   Whether or not ErrorHook can be called
  Note  :   This function can only be called from a specific context
 ---------------------------------------------------------------------------*/
AR_LOCAL_FORCE_INLINE boolean
xmcos_ar_can_call_errorhook(void)
{
    return FALSE;
}
#endif  /* (AR_OS_USE_ERRORHOOK == STD_ON) */

#ifdef __cplusplus
}
#endif


#endif /* #ifndef XMCOS_AR_V850_H */
