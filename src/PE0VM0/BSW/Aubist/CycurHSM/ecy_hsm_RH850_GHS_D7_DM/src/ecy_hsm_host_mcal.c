/* Int Hint : File from cycurHSM at : hsm_host\hsm_proxy\rh850\hsm_proxy_mcal.c*/
/* $Id$ */
/**
 * @file
 ***********************************************************************************************
 * @brief Functions and data structures for the host communication with the HSM Bridge Registers
 *

 ***********************************************************************************************
 * @copyright                     Copyright (c) 2014 ESCRYPT GmbH, Bochum. All rights reserved.
 **********************************************************************************************/

#include "ecy_hsm_host_mcal.h"
/* To avoid the Guam specific file includes*/
#if defined(GUAM)
#include "ecy_hsm_general.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_ipcdrv.h"

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* The RH850 does not have this functionality */
ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_ClockConfigure( uint32 divider )
{
    ecy_hsm_Csai_ErrorT errorCode = ecy_hsm_CSAI_SUCCESS;
    ecy_hsm_IpcDrv_SetStatus( ALL_FLAGS_ON, divider );

    /* Request the HSM to update its divider, flags bits can only be set, not cleared    */
    ecy_hsm_IpcDrv_SendEvents( HT2HSMF_CLOCK_CONFIG );

    return (errorCode);
}
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

