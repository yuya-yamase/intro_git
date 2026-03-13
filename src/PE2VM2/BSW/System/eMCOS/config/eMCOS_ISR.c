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

#include "scheduler.h"
#include "gpi2c_ma.h"

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

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
#define OS_START_SEC_CODE_GLOBAL
#include "Os_MemMap.h"

#if (__AIP_THROUGHPUT__ != 1)
/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM8TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM8TINT)
{
    vd_g_SchdlrMainTick();
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC0EE)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC0EE)
{
	/*    INTRIIC0EE_ISR;*/
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_0);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC0RI)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC0RI)
{
    /*    INTRIIC0RI_ISR;*/
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_0);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC0TI)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC0TI)
{
    /*    INTRIIC0TI_ISR;*/
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_0);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC0TEI)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC0TEI)
{
    /*    INTRIIC0TEI_ISR;*/
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_0);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC1EE)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC1EE)
{
    /*    INTRIIC1EE_ISR;*/
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_1);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC1RI)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC1RI)
{
    /*    INTRIIC1RI_ISR;*/
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_1);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC1TI)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC1TI)
{
    /*    INTRIIC1TI_ISR;*/
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_1);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC1TEI)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC1TEI)
{
    /*    INTRIIC1TEI_ISR;*/
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_1);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM1TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM1TINT)
{
    /*    INTOSTM1_ISR;*/
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTP38)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTP38)
{
    /*    INTP38_ISR;*/
}

#else /* #if ((defined(__AIP_THROUGHPUT__)) && (__AIP_THROUGHPUT__ == 1)) */
/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM8TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM8TINT)
{
    vd_g_ThroughputIntrptStart();
    vd_g_SchdlrMainTick();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTOSTM8TINT);
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC0EE)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC0EE)
{
	/*    INTRIIC0EE_ISR;*/
    vd_g_ThroughputIntrptStart();
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_0);
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRIIC0EE);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC0RI)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC0RI)
{
    /*    INTRIIC0RI_ISR;*/
    vd_g_ThroughputIntrptStart();
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_0);
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRIIC0RI);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC0TI)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC0TI)
{
    /*    INTRIIC0TI_ISR;*/
    vd_g_ThroughputIntrptStart();
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_0);
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRIIC0TI);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC0TEI)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC0TEI)
{
    /*    INTRIIC0TEI_ISR;*/
    vd_g_ThroughputIntrptStart();
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_0);
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRIIC0TEI);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC1EE)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC1EE)
{
    /*    INTRIIC1EE_ISR;*/
    vd_g_ThroughputIntrptStart();
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_1);
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRIIC1EE);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC1RI)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC1RI)
{
    /*    INTRIIC1RI_ISR;*/
    vd_g_ThroughputIntrptStart();
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_1);
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRIIC1RI);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC1TI)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC1TI)
{
    /*    INTRIIC1TI_ISR;*/
    vd_g_ThroughputIntrptStart();
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_1);
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRIIC1TI);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTRIIC1TEI)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTRIIC1TEI)
{
    /*    INTRIIC1TEI_ISR;*/
    vd_g_ThroughputIntrptStart();
    vd_g_GpI2cMaIRQTRx(GP_I2C_MA_CH_1);
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTRIIC1TEI);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTOSTM1TINT)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTOSTM1TINT)
{
    /*    INTOSTM1_ISR;*/
    vd_g_ThroughputIntrptStart();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTOSTM1TINT);
}

/**---------------------------------------------------------------------------
 * [Format]		ISR(eMCOS_ISR_INTP38)
 * [Function]	
 * [Arguments]	None
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/
ISR(eMCOS_ISR_INTP38)
{
    /*    INTP38_ISR;*/
    vd_g_ThroughputIntrptStart();
    vd_g_ThroughputIntrptFinish((U2)THRPTM_TASK_ISR_INTP38);
}
#endif /* #if (__AIP_THROUGHPUT__ != 1) */

#define OS_STOP_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
