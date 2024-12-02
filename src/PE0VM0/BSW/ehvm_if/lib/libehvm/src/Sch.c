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
[Sch.c] -  VM Scheduler
****************************************************************************/

#include "Sch.h"
#include "ehvm_Sch_ghs.h"

/*---------------------------------------------------------------------------
  ehvm_sch_set_schedule_table

  Input     :   coreid
                schedulingid
  Output    :   none
  Return    :   ehvm_std_return_t
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t ehvm_sch_set_schedule_table( EhvmConstR ehvm_core_id_t coreid, EhvmConstR ehvm_sch_scheduling_id_t schedulingid )
{
    ehvm_std_return_t setSchTblResult;

    setSchTblResult = ehvm_sch_Set_SchTbl_hvc( coreid, schedulingid );

    return setSchTblResult;
}

/*---------------------------------------------------------------------------
  ehvm_sch_get_schedule_table

  Input     :   coreid
  Output    :   schedulingid
  Return    :   ehvm_std_return_t
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t ehvm_sch_get_schedule_table( EhvmConstR ehvm_core_id_t coreid, ehvm_sch_scheduling_id_t* EhvmConstR schedulingid )
{
    ehvm_std_return_t getSchTblResult;

    getSchTblResult = ehvm_sch_Get_SchTbl_hvc( coreid, schedulingid );

    return getSchTblResult;
}

/*---------------------------------------------------------------------------
  ehvm_sch_disable_vm_switch

  Input     :   none
  Output    :   none
  Return    :   ehvm_std_return_t
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t ehvm_sch_disable_vm_switch( void )
{
    ehvm_std_return_t disableResult;
    
    disableResult = ehvm_sch_Disable_Vm_Switch_hvc();
    
    return disableResult;
}

/*---------------------------------------------------------------------------
  ehvm_sch_enable_vm_switch

  Input     :   none
  Output    :   none
  Return    :   ehvm_std_return_t
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_std_return_t ehvm_sch_enable_vm_switch( void )
{
    ehvm_std_return_t enableResult;
    
    enableResult = ehvm_sch_Enable_Vm_Switch_hvc();
    
    return enableResult;
}

