/* Int Hint : New file created in Guam*/
/**
 * @file
 ***********************************************************************************************
 * @brief
 *  Inter processor communication mcal driver implementation for RH850 - HOST side
 *
 * [$Satisfies $COMPONENT IPC_MCAL]
 *
 * @details
 * Hardware specific routines to control communication between HSM and HOST controller,
 * specific to RH850
 *
 **********************************************************************************************/
 /***********************************************************************************************
 * @copyright                     Copyright (c) 2014 ESCRYPT GmbH, Bochum. All rights reserved.
 **********************************************************************************************/

#ifndef ECY_HSM_IPCMCAL_H
#define ECY_HSM_IPCMCAL_H

/*
 *************************************************************************************************
 * Includes
 *************************************************************************************************
 */

/* To avoid the Guam specific file includes*/
#if defined(GUAM)
#include "arch.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif

#if ( (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V3) ||  \
      (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V4) ||  \
      (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V5) )
#include "ecy_hsm_service.h"
#endif

#include "ecy_hsm_ipcmcal_if.h"

/**
 * @addtogroup IPCMCAL
 * @{
 */

/* **********************************************************************************************
 Function implementations
 ************************************************************************************************/
/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/*
 * If NOT stubbed by UTEST ...
 */
#ifndef TEST_IPC_MCAL_STUBBED


/*  [$Satisfies $DD 111] */
LOCAL_INLINE void ecy_hsm_IpcMcal_Initialize( void )
{
    /* Disable HSM bridge interrupts */
    /* PRQA S 0303 1 */ /*Deviation: Implicit conversion is not causing any harm to the intended functionality */
    ICU2PEIE = 0x00000000UL;

    /* HOST status is cleared */
    /* PRQA S 0303 1 */ /*Deviation: Implicit conversion is not causing any harm to the intended functionality */
    PE2ICUS  = 0x00000000UL;

    /* All HSM-to-host events SHALL be acknowledged */
    /* PRQA S 0303 1 */ /*Deviation: Implicit conversion is not causing any harm to the intended functionality */
    ICU2PEFC = 0xFFFFFFFFUL;
}

/* [$Satisfies $DD 112] */
LOCAL_INLINE uint32 ecy_hsm_IpcMcal_GetIrqStates( void )
{
    /* PRQA S 0303 1 */ /*Deviation: Implicit conversion is not causing any harm to the intended functionality */
    return ICU2PEIE;
}

/* [$Satisfies $DD 113] */
LOCAL_INLINE void ecy_hsm_IpcMcal_ConfigureIrqs(uint32 hsmEventMask, uint32 hsmEventValue)
{
    /* PRQA S 0303 1 */ /*Deviation: Implicit conversion is not causing any harm to the intended functionality */
    ICU2PEIE =  (ICU2PEIE & ~hsmEventMask) | (hsmEventValue & hsmEventMask);
}

/* [$Satisfies $DD 114] */
LOCAL_INLINE uint32 ecy_hsm_IpcMcal_GetHostEvents( void )
{
    /* PRQA S 0303 1 */ /*Deviation: Implicit conversion is not causing any harm to the intended functionality */
    return PE2ICUF;
}

/* [$Satisfies $DD 116] */
LOCAL_INLINE uint32 ecy_hsm_IpcMcal_GetHsmEvents( void )
{
    /* PRQA S 0303 1 */ /*Deviation: Implicit conversion is not causing any harm to the intended functionality */
    return ICU2PEF;
}

/* [$Satisfies $DD 118] */
LOCAL_INLINE uint32 ecy_hsm_IpcMcal_GetHostStatus( void )
{
    /* PRQA S 0303 1 */ /*Deviation: Implicit conversion is not causing any harm to the intended functionality */
    return PE2ICUS;
}

/* [$Satisfies $DD 120] */
LOCAL_INLINE uint32 ecy_hsm_IpcMcal_GetHsmStatus( void )
{
    /* PRQA S 0303 1 */ /*Deviation: Implicit conversion is not causing any harm to the intended functionality */
    return ICU2PES;
}

/* [$Satisfies $DD 117] */
LOCAL_INLINE void ecy_hsm_IpcMcal_SendEvents(uint32 hsmEventMask)
{
#if ( (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V3) ||  \
      (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V4) ||  \
      (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V5))
    /** Use the single ICUPES interrupt for Quick CMAC,
     *  triggered by the PE2ICUSFS register. All other host requests are routed over the ICUPE IRQ,
     *  triggered as on the P1x, using the PE2ICUFS register */
    if(HT2HSMF_QUICK_ROUTE == hsmEventMask)
    {
        PE2ICUSFS = 1UL;
    }
    else
    {
        /* PRQA S 0303 1 */ /*Deviation: Implicit conversion is not causing any harm to the intended functionality */
        PE2ICUFS = hsmEventMask;
    }
#else
    /* PRQA S 0303 1 */ /*Deviation: Implicit conversion is not causing any harm to the intended functionality */
    PE2ICUFS = hsmEventMask;
#endif /* #if ( (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V3) || (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V4) ) */
}

/* [$Satisfies $DD 115] */
LOCAL_INLINE void ecy_hsm_IpcMcal_AcknowledgeEvents(uint32 hostEventMask)
{
   /* PRQA S 0303 1 */ /*Deviation: Implicit conversion is not causing any harm to the intended functionality */
    ICU2PEFC = hostEventMask;
}

/* [$Satisfies $DD 119] */
LOCAL_INLINE void ecy_hsm_IpcMcal_SetStatus(uint32 dataMask,uint32 dataValue)
{
    /* PRQA S 0303 1 */ /*Deviation: Implicit conversion is not causing any harm to the intended functionality */
    PE2ICUS = (PE2ICUS & ~dataMask) | (dataValue & dataMask);
}

#endif /* TEST_IPC_MCAL_STUBBED */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */

#endif /* ECY_HSM_IPCMCAL_H */
