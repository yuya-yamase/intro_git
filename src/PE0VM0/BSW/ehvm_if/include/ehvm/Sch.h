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
[Sch.h] -  VM Scheduler module's header
****************************************************************************/

#ifndef SCH_H
#define SCH_H

#include "ehvm_types.h"

typedef ehvm_uint8_t  ehvm_core_id_t;
typedef ehvm_uint8_t  ehvm_sch_scheduling_id_t;

extern ehvm_std_return_t ehvm_sch_set_schedule_table( EhvmConstR ehvm_core_id_t coreid, EhvmConstR ehvm_sch_scheduling_id_t schedulingid );
extern ehvm_std_return_t ehvm_sch_get_schedule_table( EhvmConstR ehvm_core_id_t coreid, ehvm_sch_scheduling_id_t* EhvmConstR schedulingid );
extern ehvm_std_return_t ehvm_sch_disable_vm_switch( void );
extern ehvm_std_return_t ehvm_sch_enable_vm_switch( void );


#endif /* SCH_H */
