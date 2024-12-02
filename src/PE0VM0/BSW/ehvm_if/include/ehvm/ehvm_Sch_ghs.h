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
 [ ehvm_Sch_ghs.h ] - Memory Protection module's configuration data file
****************************************************************************/
#ifndef EHVM_SCH_GHS_H
#define EHVM_SCH_GHS_H

#include "ehvm_types.h"

extern ehvm_std_return_t ehvm_sch_Set_SchTbl_hvc( EhvmConstR ehvm_core_id_t coreid, EhvmConstR ehvm_sch_scheduling_id_t schedulingid );
extern ehvm_std_return_t ehvm_sch_Get_SchTbl_hvc( EhvmConstR ehvm_core_id_t coreid, ehvm_sch_scheduling_id_t* EhvmConstR schedulingid );
extern ehvm_std_return_t ehvm_sch_Disable_Vm_Switch_hvc( void );
extern ehvm_std_return_t ehvm_sch_Enable_Vm_Switch_hvc( void );


#endif /* #define EHVM_SCH_GHS_H */
