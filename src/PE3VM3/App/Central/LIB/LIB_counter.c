/* -------------------------------------------------------------------------- */
/* file name  :  LIB_counter.c                                                */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include "gpt_drv_frt.h"
#include <LIB.h>
#include "aip_common.h"
/* -------------------------------------------------------------------------- */
/* #define LIB_START_SEC_CODE */
/* #include <LIB_MemMap.h> */
/* -------------------------------------------------------------------------- */
uint32 LIB_GetFreeRunCount1us (void)
{

	uint32 FreeRunCount1us = 0U;

    /* –ß‚è’l‚ÌLSB‚ª0.0125us‚Ì‚½‚ßLSB‚ð1us‚É•ÏŠ· */
	FreeRunCount1us = (uint32)(u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA) / 80);
	
	return((uint32)FreeRunCount1us);
}
/* -------------------------------------------------------------------------- */
/* #define LIB_STOP_SEC_CODE */
/* #include <LIB_MemMap.h> */
/* -------------------------------------------------------------------------- */
