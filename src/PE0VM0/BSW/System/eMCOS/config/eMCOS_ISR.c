/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		eMCOS_ISR.c
 * [Module]			ISR body of eMCOS configuration
 * [Function]		ISR body implementation
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>
#include <Os.h>

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>

/* Communication         */
#include "Can.h"

#include "scheduler.h"

#if ((defined(__AIP_THROUGHPUT__)) && (__AIP_THROUGHPUT__ == 1))
#include "throughput.h"
#endif

#include <Ecu_Memmap_SdaDisableE_env.h>
/*----------------------------------------------------------------------------
 *		Defines
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *      Prototypes
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM5TINT);
ISR(eMCOS_ISR_INTTAUD0I14);
ISR(eMCOS_ISR_INTRCAN3REC);
ISR(eMCOS_ISR_INTRCAN3TRX);
ISR(eMCOS_ISR_INTRCAN5REC);
ISR(eMCOS_ISR_INTRCAN5TRX);
ISR(eMCOS_ISR_INTRCAN7REC);
ISR(eMCOS_ISR_INTRCAN7TRX);
ISR(eMCOS_ISR_INTRCAN11REC);
ISR(eMCOS_ISR_INTRCAN11TRX);

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
#define OS_START_SEC_CODE_GLOBAL
#include "Os_MemMap.h"

#if (__AIP_THROUGHPUT__ != 1)
/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM5TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM5TINT)
{
    vd_g_SchdlrMainTick();
    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTTAUD0I14)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTTAUD0I14)
{
    /*    INTTAUD0CH14;*/
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN3REC)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN3REC)
{
    /*    INTRCAN3REC_ISR;*/
    Can_RxFinish_3();
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN3TRX)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN3TRX)
{
    /*    INTRCAN3TRX_ISR;*/
    Can_TxFinish_3();
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN5REC)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN5REC)
{
    /*    INTRCAN5REC_ISR;*/
    Can_RxFinish_5();
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN5TRX)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN5TRX)
{
    /*    INTRCAN5TRX_ISR;*/
    Can_TxFinish_5();
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN7REC)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN7REC)
{
    /*    INTRCAN7REC_ISR;*/
    Can_RxFinish_7();
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN7TRX)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN7TRX)
{
    /*    INTRCAN7TRX_ISR;*/
    Can_TxFinish_7();
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN11REC)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN11REC)
{
    /*    INTRCAN11REC_ISR;*/
    Can_RxFinish_11();
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN11TRX)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN11TRX)
{
    /*    INTRCAN11TRX_ISR;*/
    Can_TxFinish_11();
}

#else /* #if ((defined(__AIP_THROUGHPUT__)) && (__AIP_THROUGHPUT__ == 1)) */
/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM5TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM5TINT)
{
    vd_g_ThroughputIntrptStart();
    vd_g_SchdlrMainTick();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTOSTM5TINT);
    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTTAUD0I14)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTTAUD0I14)
{
    /*    INTTAUD0CH14;*/
    vd_g_ThroughputIntrptStart();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTTAUD0I14);
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN3REC)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN3REC)
{
    /*    INTRCAN3REC_ISR;*/
    vd_g_ThroughputIntrptStart();
    Can_RxFinish_3();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRCAN3REC);
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN3TRX)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN3TRX)
{
    /*    INTRCAN3TRX_ISR;*/
    vd_g_ThroughputIntrptStart();
    Can_TxFinish_3();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRCAN3TRX);
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN5REC)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN5REC)
{
    /*    INTRCAN5REC_ISR;*/
    vd_g_ThroughputIntrptStart();
    Can_RxFinish_5();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRCAN5REC);
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN5TRX)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN5TRX)
{
    /*    INTRCAN5TRX_ISR;*/
    vd_g_ThroughputIntrptStart();
    Can_TxFinish_5();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRCAN5TRX);
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN7REC)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN7REC)
{
    /*    INTRCAN7REC_ISR;*/
    vd_g_ThroughputIntrptStart();
    Can_RxFinish_7();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRCAN7REC);
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN7TRX)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN7TRX)
{
    /*    INTRCAN7TRX_ISR;*/
    vd_g_ThroughputIntrptStart();
    Can_TxFinish_7();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRCAN7TRX);
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN11REC)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN11REC)
{
    /*    INTRCAN11REC_ISR;*/
    vd_g_ThroughputIntrptStart();
    Can_RxFinish_11();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRCAN11REC);
}

/**---------------------------------------------------------------------------
 * [Format] 	ISR(eMCOS_ISR_INTRCAN11TRX)
 * [Function]	
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRCAN11TRX)
{
    /*    INTRCAN11TRX_ISR;*/
    vd_g_ThroughputIntrptStart();
    Can_TxFinish_11();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRCAN11TRX);
}
#endif /* #if (__AIP_THROUGHPUT__ != 1) */

#define OS_STOP_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
