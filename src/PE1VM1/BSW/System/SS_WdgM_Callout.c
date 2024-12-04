/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]      SS_WdgM_Callout.c
 * [Module]         WdgM
 * [Function]       SS_WdgM
 * [Revision]       1.10
 * [Notes]          Customize file
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *      Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>
#if 0u /* MCAL製Gpt未対応のため */
#ifdef ECU_SAMPLE_ON
#include <Gpt.h>
#endif /* ECU_SAMPLE_ON */
#endif /* MCAL製Gpt未対応のため */

/* vv include start vv */
#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_MemmapP.h>
#include <SS_WdgM_Callout.h>
/* ^^ include end ^^ */
/* vv extern start vv */
/* ^^ extern end ^^ */
/* vv include start vv */
#include <Ecu_Memmap_SdaDisableE_env.h>
/* ^^ include end ^^ */

/*----------------------------------------------------------------------------
 *      Codes
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]     uint32 SS_WdgM_getCountCallout (void)
 * [Function]   Hook of get Count
 * [Arguments]  None
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
uint32 SS_WdgM_getCountCallout(void)
{
    uint32 u4CurrenTickTime;

    /* vv User Hook start vv */
#if 0u /* MCAL製Gpt未対応のため */

#ifdef ECU_SAMPLE_ON
    u4CurrenTickTime = (uint32)(Gpt_GetTimeElapsed(GptConf_GptChannelConfiguration_GptChannelConfiguration_0));
#else
    u4CurrenTickTime = 0UL;
#endif /* ECU_SAMPLE_ON */

#else  /* MCAL製Gpt未対応のため */
    u4CurrenTickTime = 0UL;
#endif /* MCAL製Gpt未対応のため */
    /* ^^ User Hook end   ^^ */

    return (u4CurrenTickTime);
}
