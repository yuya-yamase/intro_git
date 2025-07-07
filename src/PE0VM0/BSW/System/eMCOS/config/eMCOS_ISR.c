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
#include "can_rscf4_cfg.h"

#include "scheduler.h"

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

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
#define OS_START_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
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
#if (CAN_CFG_RX_PROCESSING_3 == CAN_INTERRUPT)
    Can_RxFinish_3();
#endif
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
#if (CAN_CFG_TX_PROCESSING_3 == CAN_INTERRUPT)
    Can_TxFinish_3();
#endif
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
#if (CAN_CFG_RX_PROCESSING_5 == CAN_INTERRUPT)
    Can_RxFinish_5();
#endif
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
#if (CAN_CFG_TX_PROCESSING_5 == CAN_INTERRUPT)
    Can_TxFinish_5();
#endif
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
#if (CAN_CFG_RX_PROCESSING_7 == CAN_INTERRUPT)
    Can_RxFinish_7();
#endif
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
#if (CAN_CFG_TX_PROCESSING_7 == CAN_INTERRUPT)
    Can_TxFinish_7();
#endif
}

#define OS_STOP_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
