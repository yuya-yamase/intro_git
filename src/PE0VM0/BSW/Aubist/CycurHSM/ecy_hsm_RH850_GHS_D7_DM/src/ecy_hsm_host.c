/* Int Hint : File from cycurHSM at : hsm_host\hsm_proxy\tc27x\hsm_proxy_mcal.c*/
/* $Id$ */
/**
 * @file ecy_hsm_host.c
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
#include "test_support_host.h"
#else
#include "ecy_hsm_general_pubcfg.h"
#endif
#include "ecy_hsm_service.h"
#include "ecy_hsm_host_proxy.h"
#include "ecy_hsm_ipcdrv.h"

#define HSM2HTS_SWITCH_TO_BOOT_MASK     (HSM2HTS_CORE_APP | HSM2HTS_BOOTLOADER | HSM2HTS_BOOTED | HSM2HTS_STOPPED_MASK | HSM2HTS_ERROR_MASK)
#define HSM2HTS_BOOTING_MASK            (HSM2HTS_CORE_APP | HSM2HTS_BOOTLOADER | HSM2HTS_SUSPEND)
#define HSM2HTS_SUSPEND_MASK            (HSM2HTS_CORE_APP | HSM2HTS_BOOTLOADER)
#define HSM2HTS_TRANSIT_TO_BOOT_MASK    (HSM2HTS_BOOTLOADER | HSM2HTS_STOPPED_MASK | HSM2HTS_ERROR_MASK)
#define HSM2HTS_CORE_APP_VALID_MASK     (HSM2HTS_BOOTLOADER | HSM2HTS_STOPPED_MASK)

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

HSM_ModeT ecy_hsm_HsmMCAL_GetMode( void )
{
    HSM_ModeT mode;

    /* Get the register value into a local variable so it can't change while we are running through this function   */
    register uint32 hsm2hts = ecy_hsm_IpcDrv_GetHsmStatus();

    /* HSM is in transition from core to bootloader */
    if(HSM2HTS_BOOTLOADER == (hsm2hts & HSM2HTS_SWITCH_TO_BOOT_MASK))
    {
        mode = HSM_MODE_SWITCHING_FROM_CORE_TO_BOOT;
    }
    /* HSM is not yet started */
    else if(0UL == (hsm2hts & HSM2HTS_BOOTED))
    {
        mode = HSM_MODE_NOT_STARTED;
    }
    /* HSM is booting, have not reached core yet and is still doing checks*/
    else if(0UL == (hsm2hts & HSM2HTS_BOOTING_MASK))
    {
        mode = HSM_MODE_BOOTING;
    }
    /* HSM is in suspend mode */
    else if(0UL == (hsm2hts & HSM2HTS_SUSPEND_MASK))
    {
        mode = HSM_MODE_SUSPENDED;
    }
    /* HSM runs in bootloader */
    else if(0UL == (hsm2hts & HSM2HTS_CORE_APP))
    {
        mode = HSM_MODE_BOOTLOADER;
    }
    /* HSM is in transition to bootloader */
    else if(HSM2HTS_BOOTLOADER == (hsm2hts & HSM2HTS_TRANSIT_TO_BOOT_MASK))
    {
        mode = HSM_MODE_SWITCHING_FROM_CORE_TO_BOOT;
    }
    /* Core application is valid and running */
    else if(0UL == (hsm2hts & HSM2HTS_CORE_APP_VALID_MASK))
    {
        mode = HSM_MODE_CORE_APP;
    }
    else if(HSM2HTS_BOOTLOADER == (hsm2hts & HSM2HTS_CORE_APP_VALID_MASK))
    {
        mode = HSM_MODE_INVALID;
    }
    else
    {
        mode = HSM_MODE_CORE_APP_STOPPED;
    }

    return (mode);
    /* PRQA S 6009 1 */  /* <Justification: Refactoring due to HIS level makes this code less readable */
}

/* PRQA S 1503 1 *//* Deviation: rule_2.1_1503_Proxy */
boolean ecy_hsm_HsmMCAL_IsBooted( void )
{
    /* PRQA S 4404 1 *//*< Deviation: Conversion from essential type _Bool to boolean is intended */
    return ((0UL != (ecy_hsm_IpcDrv_GetHsmStatus() & HSM2HTS_BOOTED)) ? TRUE : FALSE);
}

boolean ecy_hsm_HsmMCAL_IsConfigured( void )
{
    /* PRQA S 4404 1 *//*< Deviation: Conversion from essential type _Bool to boolean is intended */
    return ((0UL != (ecy_hsm_IpcDrv_GetHsmStatus() & HSM2HTS_CONFIGURED)) ? TRUE : FALSE);
}

boolean ecy_hsm_HsmMCAL_IsClockConfigured( void )
{
    /* PRQA S 4404 1 *//*< Deviation: Conversion from essential type _Bool to boolean is intended */
    return ((0UL != (ecy_hsm_IpcDrv_GetHsmStatus() & HSM2HTS_CLOCK_CONFIGURED)) ? TRUE : FALSE);
}

boolean ecy_hsm_HsmMCAL_IsSuspendedSharedRamWrite(void)
{
    boolean retval = FALSE;

    if( HSM2HTF_SUSPEND_SHARED_RAM_WRITE == (ecy_hsm_IpcDrv_GetHsmEvents() & HSM2HTF_SUSPEND_SHARED_RAM_WRITE) )
    {
        retval = TRUE;
    }
    return (retval);
}
boolean ecy_hsm_HsmMCAL_IsSessionOpen( void )
{
    // request flag got confirmed
    return ((0UL == (ecy_hsm_IpcDrv_GetHostEvents() & HT2HSMF_SESSION_OPEN)) ? TRUE : FALSE);
}

boolean ecy_hsm_HsmMCAL_IsOperationCancelled( void )
{
    /* PRQA S 4404 1 *//*< Deviation: Conversion from essential type _Bool to boolean is intended */
    return ((0UL != (ecy_hsm_IpcDrv_GetHsmEvents() & HSM2HTF_CANCELLED)) ? TRUE : FALSE);
}

uint32 ecy_hsm_HsmMCAL_GetCoreErrorFlags( void )
{
    return (ecy_hsm_IpcDrv_GetHsmStatus() & HSM2HTS_ERROR_MASK);
}

boolean ecy_hsm_IsClockConfigure_Acknowledged(void)
{
    return (0u == (ecy_hsm_IpcDrv_GetHostEvents() & HT2HSMF_CLOCK_CONFIG)) ? TRUE : FALSE;
}

boolean ecy_hsm_IsSuspendSharedRamWrite_Acknowledged(void)
{
    return (0u == (ecy_hsm_IpcDrv_GetHostEvents() & HT2HSMF_SUSPEND_SHARED_RAM_WRITE)) ? TRUE : FALSE;
}
#if (ecy_hsm_HOST_STORAGE == ENABLED)

/* [$Satisfies $DD 1216] */
boolean ecy_hsm_IsHostStorageConfigure_Acknowledged(void)
{
    return ((0u == (ecy_hsm_IpcDrv_GetHostEvents() & HT2HSMF_HOST_STORAGE_CONFIG)) ? TRUE : FALSE);
}

#endif /* #if (ecy_hsm_HOST_STORAGE == ENABLED) */

void ecy_hsm_HsmMCAL_Configure( const volatile HSM_BridgeConfigurationT* pBridgeConfiguration )
{
    /* Write the address of the configuration structure to the Host-to-HSM status register */
    /* PRQA S 0303 1*//* <Deviation: conversion of pointer to uint32 does not affect functionality */
    ecy_hsm_IpcDrv_SetStatus( ALL_FLAGS_ON, (uint32) pBridgeConfiguration );

    /* Fire interrupt */
    ecy_hsm_IpcDrv_SendEvents( HT2HSMF_CONFIGURE );
}

void ecy_hsm_HsmMCAL_SuspendSharedRamWrite(const volatile HSM_HostSideSuspendSharedRamParamsT* pSuspendSharedRamOpParams)
{
    /* Clear the acknowledgement flag */
    ecy_hsm_IpcDrv_AcknowledgeEvents( HSM2HTF_SUSPEND_SHARED_RAM_WRITE );

    /* Send the operation parameters structure address */
    /* PRQA S 0303 1*//* <Deviation: conversion of pointer to uint32 does not affect functionality */
    ecy_hsm_IpcDrv_SetStatus(ALL_FLAGS_ON, (uint32)pSuspendSharedRamOpParams);

    /* Fire interrupt */
    ecy_hsm_IpcDrv_SendEvents( HT2HSMF_SUSPEND_SHARED_RAM_WRITE );
}

boolean ecy_hsm_IsConfigure_Acknowledged(void)
{
    return (0u == (ecy_hsm_IpcDrv_GetHostEvents() & HT2HSMF_CONFIGURE)) ? TRUE : FALSE;
}

void ecy_hsm_HsmMCAL_LoadOp( ecy_hsm_Csai_JobHandleT hJob )
{
    /* Set the port number  */
    ecy_hsm_IpcDrv_SetStatus( ALL_FLAGS_ON, hJob );

    /* Fire interrupt, flags bits can only be set, not cleared */
    ecy_hsm_IpcDrv_SendEvents( HT2HSMF_REQUEST );
}

void ecy_hsm_HsmMCAL_LoadQuickRoute( ecy_hsm_Csai_SessionHandleT hSession )
{
    /* Set the port number  */
    ecy_hsm_IpcDrv_SetStatus( ALL_FLAGS_ON, hSession );

    /* Fire interrupt, flags bits can only be set, not cleared */
    ecy_hsm_IpcDrv_SendEvents( HT2HSMF_QUICK_ROUTE );
}

void ecy_hsm_HsmMCAL_OpenSession( const volatile HSM_SessionOpenT* pSessionOpen )
{
    /* Copy pSessionOpen structure address to the status register */
    /* PRQA S 0303 1 *//* <Deviation: conversion of pointer to uint32 does not affect functionality */
    ecy_hsm_IpcDrv_SetStatus( ALL_FLAGS_ON, (uint32) pSessionOpen );

    /* Fire interrupt, flags bits can only be set, not cleared */
    ecy_hsm_IpcDrv_SendEvents( HT2HSMF_SESSION_OPEN );
}

void ecy_hsm_HsmMCAL_CancelOp( ecy_hsm_Csai_SessionHandleT hSession )
{
    /* Clear the acknowledgement flag - don't use the .B form because that does a read-then-write and clears all the set flags!   */
    ecy_hsm_IpcDrv_AcknowledgeEvents( HSM2HTF_CANCELLED );

    /* Set the port number  */
    ecy_hsm_IpcDrv_SetStatus( ALL_FLAGS_ON, hSession );

    /* Fire interrupt, flags bits can only be set, not cleared */
    ecy_hsm_IpcDrv_SendEvents( HT2HSMF_CANCEL );
}

ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_Release( void )
{
    ecy_hsm_IpcDrv_SendEvents( HT2HSMF_RELEASE );
    return (ecy_hsm_CSAI_SUCCESS);
}

ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_SoftReset( void )
{
#ifdef ECY_HSM_CTC
    TestEvent(TestEvent_HSM_CTC_Printout);
#endif
    ecy_hsm_IpcDrv_SendEvents(HT2HSMF_RESET);
    return (ecy_hsm_CSAI_SUCCESS);
}

boolean ecy_hsm_HsmMCAL_IsResetAcknowledged( void )
{
    boolean retVal = FALSE;

    /* wait until command reception got confirmed and the HT2HSMF_RESET flag is cleared. */
    if (0UL == (ecy_hsm_IpcDrv_GetHostEvents() & HT2HSMF_RESET))
    {
        retVal = TRUE;
    }

    return retVal;
}

ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_DoMaintenance( void )
{
    /* Clear the acknowledgement flag   */
    ecy_hsm_IpcDrv_AcknowledgeEvents( HSM2HTF_MTNC_REQUEST );

    /* Fire interrupt, flags bits can only be set, not cleared */
    ecy_hsm_IpcDrv_SendEvents( HT2HSMF_MTNC_REQUEST );
    return (ecy_hsm_CSAI_SUCCESS);
}

boolean ecy_hsm_HsmMCAL_IsMaintenanceDone( void )
{
    boolean retval = FALSE;

    if( HSM2HTF_MTNC_REQUEST == (ecy_hsm_IpcDrv_GetHsmEvents() & HSM2HTF_MTNC_REQUEST) )
    {
        retval = TRUE;
    }
    return (retval);
}

boolean ecy_hsm_HsmMCAL_IsMaintenanceStarted( void )
{
    boolean retval = FALSE;
    /* check if the request bit was cleared by the HSM, meaning it has started the maintenance */
    if( (ecy_hsm_IpcDrv_GetHostEvents() & HT2HSMF_MTNC_REQUEST) == 0UL )
    {
        retval = TRUE;
    }
    return (retval);
}

ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_DoSuspendOp( const HSM_HostSideSuspendParamsT *pSuspendParams )
{
    /* Clear the acknowledgement flag   */
    ecy_hsm_IpcDrv_AcknowledgeEvents( HSM2HTF_SUSPEND );

    /* Send the operation parameters structure address */
    /* PRQA S 0306 1 *//* Deviation: conversion of pointer to uint32 does not affect functionality */
    ecy_hsm_IpcDrv_SetStatus( ALL_FLAGS_ON, (uint32) pSuspendParams );

    /* Fire interrupt, flags bits can only be set, not cleared */
    ecy_hsm_IpcDrv_SendEvents( HT2HSMF_SUSPEND );
    return (ecy_hsm_CSAI_SUCCESS);
}

boolean ecy_hsm_HsmMCAL_IsSuspendOpDone( void )
{
    boolean retval = FALSE;

    if( HSM2HTF_SUSPEND == (ecy_hsm_IpcDrv_GetHsmEvents() & HSM2HTF_SUSPEND) )
    {
        retval = TRUE;
    }
    return (retval);
}

boolean ecy_hsm_HsmMCAL_IsSuspendOpStarted( void )
{
    boolean retval = FALSE;

    /* check if the request bit was cleared by the HSM, meaning it has started the suspend operation */
    if( (ecy_hsm_IpcDrv_GetHostEvents() & HT2HSMF_SUSPEND) == 0UL )
    {
        retval = TRUE;
    }
    return (retval);
}

ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_DoDisableSecCritOp( ecy_hsm_Csai_SessionHandleT hSession )
{
    /* Clear the acknowledgement flag   */
    ecy_hsm_IpcDrv_AcknowledgeEvents( HSM2HTF_SECCRIT_FUNC );
    /* send the operation parameters structure address */
    /* PRQA S 0306 1 *//* Deviation: rule_11.6_0306 */
    ecy_hsm_IpcDrv_SetStatus( ALL_FLAGS_ON, (uint32) hSession );

    /* Fire interrupt, flags bits can only be set, not cleared */
    ecy_hsm_IpcDrv_SendEvents( HT2HSMF_SECCRIT_FUNC );
    return (ecy_hsm_CSAI_SUCCESS);
}

/* PRQA S 1503 1 */ /* Justification: Function is called in ecy_hsm_host_proxy.c */
ecy_hsm_Csai_ErrorT ecy_hsm_HsmMCAL_DoSecureDebugConfigureOp(const HSM_SecureDebugConfigureParamsT* pDebugConfigParam)
{
    /* Clear the acknowledgement flag   */
    ecy_hsm_IpcDrv_AcknowledgeEvents(HSM2HTF_SECDEBUG_CONFIGURE);
    /* send the operation parameters structure address */
    /* PRQA S 0306 1 */ /* Deviation: rule_11.6_0306 */
    ecy_hsm_IpcDrv_SetStatus(ALL_FLAGS_ON, (uint32)pDebugConfigParam);

    /* Fire interrupt, flags bits can only be set, not cleared */
    ecy_hsm_IpcDrv_SendEvents(HT2HSMF_SECDEBUG_CONFIGURE);
    return (ecy_hsm_CSAI_SUCCESS);
}

/* PRQA S 1503 1 */ /* Justification: Function is called in ecy_hsm_host_proxy.c */
boolean ecy_hsm_HsmMCAL_IsSecureDebugConfigureDone(void)
{
    boolean retval = FALSE;

    if (HSM2HTF_SECDEBUG_CONFIGURE == (ecy_hsm_IpcDrv_GetHsmEvents() & HSM2HTF_SECDEBUG_CONFIGURE))
    {
        retval = TRUE;
    }
    return (retval);
}

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"
