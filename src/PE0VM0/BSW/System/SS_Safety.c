/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Safety.c
 * [Module] 		Safety
 * [Function]		SS_Safety
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_MemmapProtect_Env.h>

#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_Safety.h>
#include <SS_CpuCore.h>
#include <SS_RamTest.h>
#include <SS_RomTest.h>
#include <SS_StackCheck.h>
#include <SS_ISeq.h>

#include <SS_MemmapSdaSelectE_Env.h>
/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------
 * [Format] 	void SS_SafetyM_mainFunction(void)
 * [Function]	SSが提供する安全機能を実行する
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_SafetyM_mainFunction(void)
{
    

    

#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
    SS_StackCheck_exec();
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */

    
    

#if (SS_USE_ADDRBUSCHECK == STD_ON)
    SS_RamTest_execAddrBusChk();
#endif /* (SS_USE_ADDRBUSCHECK == STD_ON) */

    

#if (SS_USE_ROMBUFFCHECK == STD_ON)
    SS_RomTest_execBuffChk();
#endif /* (SS_USE_ROMBUFFCHECK == STD_ON) */

    SS_CpuCore_refresh();

    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	void SS_SafetyM_init(void)
 * [Function]	SSが提供する安全機能を初期化する
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_SafetyM_init(void)
{
#if (SS_USE_STACK_BOUNDARYCHECK == STD_ON)
    SS_StackCheck_init();
    
#endif /* (SS_USE_STACK_BOUNDARYCHECK == STD_ON) */

#if (SS_USE_ADDRBUSCHECK == STD_ON)
    SS_RamTest_initAddrBusChk();
    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_POSTOS_C);
#endif /* (SS_USE_ADDRBUSCHECK == STD_ON) */

#if (SS_USE_ADDRBUSCHECK == STD_ON)
    
    SS_RamTest_execAddrBusChk();
    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_POSTOS_D);
#endif /* (SS_USE_ADDRBUSCHECK == STD_ON) */

#if (SS_USE_ROMBUFFCHECK == STD_ON)
    SS_RomTest_execBuffChk();
    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_POSTOS_E);
#endif /* (SS_USE_ROMBUFFCHECK == STD_ON) */

    return;
}
