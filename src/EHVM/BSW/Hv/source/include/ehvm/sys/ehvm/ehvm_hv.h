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
 [ ehvm_hv.h ] - EHVM API for Hv internal use header
****************************************************************************/

#ifndef EHVM_HV_H
#define EHVM_HV_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "ehvm_types_stdint.h"
#define EHVM_TYPES_HV_C
#include "ehvm_types_hv.h"
#include "ehvm_types_cfg.h"
#include "ehvm_types_api.h"
#include "ehvm_hvcb.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/* HV Init */
extern void ehvm_hvm_get_lock( ehvm_uint8_t* lock );
extern ehvm_uint8_t ehvm_hvm_try_to_lock( ehvm_uint8_t* lock );
extern void ehvm_hvm_release_lock( ehvm_uint8_t* lock );
extern ehvm_uint32_t ehvm_hvm_get_EIPSWH( void );
extern ehvm_spid_t ehvm_hvm_get_vm_SPID( void );
extern void ehvm_hvm_start_timer( void );
extern ehvm_uint32_t ehvm_hvm_get_timer_upper_4byte( void );
extern ehvm_uint32_t ehvm_hvm_get_timer_lower_4byte( void );
extern void ehvm_hvm_accept_FE_level_interrupt( void );
extern void ehvm_hvm_deny_FE_level_interrupt( void );
extern ehvm_uint32_t ehvm_hvm_get_PSW_EP( void );
extern void ehvm_hvm_stack_init( void );
extern ehvm_context_id_t ehvm_hvm_get_contextid( EhvmConstR ehvm_peid_t peid, EhvmConstR ehvm_gpid_t gpid );
extern EhvmConst ehvm_hvcb_t* ehvm_hvm_get_hvcb( void );
extern ehvm_uint8_t ehvm_hvm_clear_Bit( EhvmConstR ehvm_uint8_t* EhvmConstR baseAddr,  EhvmConstR ehvm_uint8_t bitNum );
extern ehvm_uint8_t ehvm_hvm_set_Bit( EhvmConstR ehvm_uint8_t* EhvmConstR baseAddr,  EhvmConstR ehvm_uint8_t bitNum );
extern ehvm_uint8_t ehvm_hvm_test_Bit( EhvmConstR ehvm_uint8_t* EhvmConstR baseAddr, EhvmConstR ehvm_uint8_t bitNum );
extern void ehvm_hvm_exc_Fetrap( void );

/* for MPU interface */
extern void ehvm_mp_mpu_init(void);
extern void ehvm_mp_mpu_load_memory( EhvmConstR ehvm_gpid_t gpid );
extern void ehvm_mp_mpu_store_memory( EhvmConstR ehvm_gpid_t gpid );
extern void ehvm_mp_mpu_load_mpid( EhvmConstR ehvm_gpid_t gpid );
extern ehvm_std_return_t ehvm_mp_mpu_check_memory_protection( EhvmConstR ehvm_uint8_t* data, EhvmConstR ehvm_uint32_t lenbytes, EhvmConstR ehvm_spid_t spid );
extern void ehvm_bios_v850_mp_mpu_init_mpu_table( void );
extern void ehvm_bios_v850_mp_mpu_set_MPIDX( EhvmConstR ehvm_uint32_t mpidx );
extern void ehvm_bios_v850_mp_mpu_set_MPLA( EhvmConstR ehvm_uint32_t mpla );
extern void ehvm_bios_v850_mp_mpu_set_MPUA( EhvmConstR ehvm_uint32_t mpua );
extern void ehvm_bios_v850_mp_mpu_set_MPAT( EhvmConstR ehvm_uint32_t mpat );
extern void ehvm_bios_v850_mp_mpu_set_MCA( EhvmConstR ehvm_uint8_t* addr );
extern void ehvm_bios_v850_mp_mpu_set_MCS( EhvmConstR ehvm_uint32_t size );
extern void ehvm_bios_v850_mp_mpu_set_MCC( EhvmConstR ehvm_uint32_t val );
extern void ehvm_bios_v850_mp_mpu_set_MCI( EhvmConstR ehvm_uint32_t spid );
extern ehvm_uint32_t ehvm_bios_v850_mp_mpu_get_MCR( void );
extern void ehvm_bios_v850_mp_mpu_set_MPID( EhvmConstR ehvm_uint32_t index, EhvmConstR ehvm_uint32_t mpid );
extern void ehvm_bios_v850_mp_mpu_exec_STM_MP( EhvmConstR ehvm_gpid_t gpid );
extern void ehvm_bios_v850_mp_mpu_exec_LDM_MP( EhvmConstR ehvm_gpid_t gpid );
extern void ehvm_bios_v850_mp_mpu_set_MPCFG( void );
extern void ehvm_bios_v850_mp_mpu_set_HMMPM( void );
extern void ehvm_mp_mpu_clear_guest_entry(void);


extern void ehvm_mp_guard_init(void);
extern void ehvm_mp_intc2g_set_protection_setting( EhvmConstR ehvm_gpid_t next_vm_id );
extern void ehvm_mp_intc2g_clear_protection_setting( EhvmConstR ehvm_gpid_t curr_vm_id );

/* for VCC interface */
extern void ehvm_vcc_init(void);
extern ehvm_std_return_t ehvm_vcc_transmit(EhvmConstR ehvm_vcc_id_t vccid,EhvmConstR ehvm_uint32_t* EhvmConstR databuffer, EhvmConstR ehvm_uint32_t lenbytes);
extern ehvm_std_return_t ehvm_vcc_receive(EhvmConstR ehvm_vcc_id_t vccid, ehvm_uint32_t* EhvmConstR buf, EhvmConstR ehvm_uint32_t lenbytes, ehvm_uint32_t *EhvmConstR databytes);
extern ehvm_std_return_t ehvm_vcc_clear( void );
extern ehvm_std_return_t ehvm_vcc_clear_channel( EhvmConstR ehvm_vcc_id_t vccid );
extern ehvm_std_return_t ehvm_vcc_get_overwrite_status( EhvmConstR ehvm_vcc_id_t vccid );

/* for VWDT interface */
extern ehvm_std_return_t ehvm_vwdt_wdg_setmode( EhvmConstR ehvm_uint8_t DeviceIndex, EhvmConstR ehvm_vwdt_mode_t VWdtMode );
extern ehvm_std_return_t ehvm_vwdt_wdg_settriggercondition( EhvmConstR ehvm_uint8_t DeviceIndex, EhvmConstR ehvm_uint16_t Timeout );

/* for VMSch interface */
extern ehvm_std_return_t ehvm_sch_set_schedule_table( EhvmConstR ehvm_core_id_t coreid, EhvmConstR ehvm_sch_scheduling_id_t schedulingid );
extern ehvm_std_return_t ehvm_sch_get_schedule_table( EhvmConstR ehvm_core_id_t coreid, ehvm_sch_scheduling_id_t* EhvmConstR schedulingid );
extern ehvm_std_return_t ehvm_sch_disable_vm_switch( void );
extern ehvm_std_return_t ehvm_sch_enable_vm_switch( void );

/* for HVCM interface */
extern ehvm_std_return_t  ehvm_hvcm_set_access_deny_list( EhvmConstR ehvm_context_id_t contextId, EhvmConstR ehvm_uint32_t * EhvmConstR denylist );
extern ehvm_std_return_t  ehvm_hvcm_get_access_deny_list( EhvmConstR ehvm_context_id_t contextId, ehvm_uint32_t * EhvmConstR denylist );
extern void ehvm_hvcm_clr_access_deny_list( EhvmConstR ehvm_context_id_t contextId );
extern ehvm_std_return_t ehvm_hvcm_chk_access_deny_list( EhvmConstR ehvm_uint32_t functionID );
extern void ehvm_hvcm_shared_init( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* EHVM_HV_H */
