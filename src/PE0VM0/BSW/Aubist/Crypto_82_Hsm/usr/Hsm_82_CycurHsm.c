/**
 * \file  Hsm_82_CycurHsm.c
 * \copyright  DENSO Corporation 2022
*/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_service_basic.h"
#include "Crypto_82_Hsm.h"
#include "Crypto_82_Hsm_Internal.h"
#include "SchM_Crypto_82_Hsm.h"
#include "Hsm_82_CycurHsm.h"
#include "Hsm_82_CycurHsm_Cfg.h"
#if (USR_HSM_SETTINR_RAM == STD_ON)
#include "ecy_Hsm_RAM.h"
#endif
#if (USR_HSM_VERSION == USR_HSM_VERSION_V3x)
#include "ecy_hsm_ipcmcal.h"
#include "ecy_hsm_mgmt.h"
#else
#include "ecy_hsm_host_proxy.h"
#include "ecy_hsm_ipcdrv.h"
#endif

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if (USR_HSM_RESETTING_HSMCONF == STD_ON)
#define Hsm_82_CycurHsm_GetCounterValue           (Hsm_82_CycurHsm_GetCounterValue1)
#define Hsm_82_CycurHsm_GetElapsedCounterValue    (Hsm_82_CycurHsm_GetElapsedCounterValue1)
#else
#define Hsm_82_CycurHsm_GetCounterValue           (Hsm_82_CycurHsm_GetCounterValue0)
#define Hsm_82_CycurHsm_GetElapsedCounterValue    (Hsm_82_CycurHsm_GetElapsedCounterValue0)
#endif

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Internal Functions                                                       */
/*--------------------------------------------------------------------------*/
#if (USR_HSM_SETTINR_RAM == STD_ON)
#pragma ghs section text = ".P_RAM_RPGEVTHK"

/******************************************************************/
/* uint32 Hsm_82_CycurHsm_CopyRomToRam */
/******************************************************************/
static void Hsm_82_CycurHsm_CopyRomToRam
(
    VAR(uint32, AUTOMATIC) DstAddr[],
    CONST(uint32, AUTOMATIC) SrcAddr[],
    CONST(uint32, AUTOMATIC) SrcEndAddr[]
)
{
    VAR(uint32, AUTOMATIC) Index;

    Index = 0UL;

    while( &SrcAddr[Index] < SrcEndAddr )
    {
        DstAddr[Index] = SrcAddr[Index];
        Index++;            /* no wrap around */
    }

    return;
}

/******************************************************************/
/* Usr_CycurHSM_RAM_Init */
/******************************************************************/
__farcall static void Hsm_82_CycurHsm_RAM_Init(void)
{
    ecy_hsm_Csai_ErrorT    errorCode;

    Hsm_82_CycurHsm_CopyRomToRam(SECTION_RAMCOPY_HSM_DST_ADDR, SECTION_RAMCOPY_HSM_SRC_ADDR, SECTION_RAMCOPY_HSM_SRC_END_ADDR);
    
    errorCode = ECY_HSM_RAM_CONFIGCALLOUTS(Hsm_82_CycurHsm_GetResourceRAM,
                                           Hsm_82_CycurHsm_ReleaseResourceRAM,
                                           Hsm_82_CycurHsm_GetCounterValueRAM,
                                           Hsm_82_CycurHsm_GetElapsedCounterValueRAM);
    if( ecy_hsm_CSAI_SUCCESS != errorCode )
    {
        Hsm_82_CycurHsm_Callout_ErrorRAM();
    }
}

#pragma ghs section text = default
#endif

#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/******************************************************************/
/* uint32 Hsm_82_CycurHsm_GetFatalErrorFlags */
/******************************************************************/
static uint32 Hsm_82_CycurHsm_GetFatalErrorFlags(void)
{
    uint32 HSMStatus;
#if (USR_HSM_VERSION == USR_HSM_VERSION_V3x)
    ecy_hsm_IpcMcal_StatusStructT tempStat;

    tempStat = ecy_hsm_IpcMcal_GetStatus(ECY_HSM_IPCMCAL_IF_ID_0);
    HSMStatus = tempStat.status;
#else
    HSMStatus = ecy_hsm_IpcDrv_GetHsmStatus();
#endif
    return HSMStatus & HSM2HTS_STOPPED_MASK;
}

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/*--------------------------------------------------------------------------*/
/* External Functions                                                       */
/*--------------------------------------------------------------------------*/
#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/******************************************************************/
/* Hsm_82_CycurHsm_InitZero */
/******************************************************************/
void Hsm_82_CycurHsm_InitZero(void)
{
    ecy_hsm_Csai_ErrorT    errorCode;
    HSM_ModeT              actMode;
#if (USR_HSM_MICRO == USR_HSM_MICRO_TC3X)
    uint32 df_timeout;
    uint32 hf_status;
#endif
#if (USR_HSM_VERSION == USR_HSM_VERSION_V3x)
    errorCode = ecy_hsm_Mgmt_ConfigureCallouts(Hsm_82_CycurHsm_GetResource0,
                                               Hsm_82_CycurHsm_ReleaseResource0,
                                               Hsm_82_CycurHsm_GetCounterValue0,
                                               Hsm_82_CycurHsm_GetElapsedCounterValue0);
#else
    errorCode = ecy_HSM_ConfigureCallouts(Hsm_82_CycurHsm_GetResource0,
                                          Hsm_82_CycurHsm_ReleaseResource0,
                                          Hsm_82_CycurHsm_GetCounterValue0,
                                          Hsm_82_CycurHsm_GetElapsedCounterValue0);
#endif
    if(  ecy_hsm_CSAI_SUCCESS != errorCode )
    {
        Hsm_82_CycurHsm_Callout_Error();
    }
#if (USR_HSM_VERSION == USR_HSM_VERSION_V3x)
    actMode = ecy_hsm_Mgmt_GetMode();
#else
    actMode = ecy_HSM_GetMode();
#endif
    if( HSM_MODE_CORE_APP != actMode )
    {
#if (USR_HSM_VERSION == USR_HSM_VERSION_V3x)
        errorCode = ecy_hsm_Mgmt_WaitForBooted(USR_HSM_WAITFORBOOTED_TIMEOUT);
#else
        errorCode = ecy_HSM_WaitForBooted(USR_HSM_WAITFORBOOTED_TIMEOUT);
#endif
        if( ecy_hsm_CSAI_SUCCESS != errorCode )
        {
            Hsm_82_CycurHsm_Callout_Error();
        }
        
        Hsm_82_CycurHsm_Callout_ClockConfig();

        /* D0BUSY and D1BUSY should be checked before ecy_HSM_Release() executed. */
#if (USR_HSM_MICRO == USR_HSM_MICRO_TC3X)
        df_timeout=0;
        hf_status=(uint32)(USR_HSM_REG_HF_STATUS);
        while (((uint32)USR_HSM_REG_HF_STATUS_BITPOS_D0BUSY == (uint32)(hf_status & USR_HSM_REG_HF_STATUS_BITPOS_D0BUSY))
            || ((uint32)USR_HSM_REG_HF_STATUS_BITPOS_D1BUSY == (uint32)(hf_status & USR_HSM_REG_HF_STATUS_BITPOS_D1BUSY)))
        {
            if (df_timeout > USR_HSM_DFBUSY_TIMEOUT)
            {
                Hsm_82_CycurHsm_Callout_Error();
            }
            df_timeout++;
            hf_status=(uint32)(USR_HSM_REG_HF_STATUS);
        }
#endif

#if (USR_HSM_VERSION == USR_HSM_VERSION_V3x)
        (void)ecy_hsm_Mgmt_Release();
#else
        (void)ecy_HSM_Release();
#endif
    }
}

/******************************************************************/
/* Hsm_82_CycurHsm_InitOne */
/******************************************************************/
void Hsm_82_CycurHsm_InitOne(void)
{
    ecy_hsm_Csai_ErrorT    errorCode;
    uint32                 HSMStatus;
    HSM_ModeT              actMode;
#if (USR_HSM_WAITFORMODEAPPL_DOWHILE == STD_ON)
    uint32                 loopCount = 0UL;
#endif

#if USR_HSM_RESETTING_HSMCONF == STD_ON
#if (USR_HSM_VERSION == USR_HSM_VERSION_V3x)
    errorCode = ecy_hsm_Mgmt_ConfigureCallouts(Hsm_82_CycurHsm_GetResource1,
                                               Hsm_82_CycurHsm_ReleaseResource1,
                                               Hsm_82_CycurHsm_GetCounterValue1,
                                               Hsm_82_CycurHsm_GetElapsedCounterValue1);
#else
    errorCode = ecy_HSM_ConfigureCallouts(Hsm_82_CycurHsm_GetResource1,
                                          Hsm_82_CycurHsm_ReleaseResource1,
                                          Hsm_82_CycurHsm_GetCounterValue1,
                                          Hsm_82_CycurHsm_GetElapsedCounterValue1);
#endif
    if( ecy_hsm_CSAI_SUCCESS != errorCode )
    {
        Hsm_82_CycurHsm_Callout_Error();
    }
#endif

#if (USR_HSM_VERSION == USR_HSM_VERSION_V3x)
    actMode = ecy_hsm_Mgmt_GetMode();
#else
    actMode = ecy_HSM_GetMode();
#endif
    if( HSM_MODE_CORE_APP != actMode )
    {
#if (USR_HSM_WAITFORMODEAPPL_DOWHILE == STD_ON)
        do
        {
            Hsm_82_CycurHsm_Callout_WaitForMode();
#if (USR_HSM_VERSION == USR_HSM_VERSION_V3x)
            errorCode = ecy_hsm_Mgmt_WaitForMode(HSM_MODE_CORE_APP, USR_HSM_WAITFORMODEAPPL_TIMEOUT);
            HSMStatus = ecy_hsm_Mgmt_GetCoreErrorFlags();
#else
            errorCode = ecy_HSM_WaitForMode(HSM_MODE_CORE_APP, USR_HSM_WAITFORMODEAPPL_TIMEOUT);
            HSMStatus = ecy_HSM_GetCoreErrorFlags();
#endif
            loopCount++;
        } while((errorCode != ecy_hsm_CSAI_SUCCESS) && (loopCount < USR_HSM_WAITFORMODEAPPL_COUNT) && (0UL == HSMStatus));
#else
        errorCode = ecy_HSM_WaitForMode(HSM_MODE_CORE_APP, USR_HSM_WAITFORMODEAPPL_TIMEOUT);
        HSMStatus = ecy_HSM_GetCoreErrorFlags();
#endif
        if( 0UL != HSMStatus )
        {
            Hsm_82_CycurHsm_Callout_Error();
        }

        if( ecy_hsm_CSAI_SUCCESS != errorCode )
        {
            Hsm_82_CycurHsm_Callout_Error();
        }

#if (USR_HSM_VERSION == USR_HSM_VERSION_V3x)
        actMode = ecy_hsm_Mgmt_GetMode();
#else
        actMode = ecy_HSM_GetMode();
#endif
        if( HSM_MODE_CORE_APP != actMode )
        {
            Hsm_82_CycurHsm_Callout_Error();
        }
    }
#if (USR_HSM_VERSION == USR_HSM_VERSION_V3x)
    errorCode = ecy_hsm_Mgmt_Configure(NULL_PTR, 0UL);
#else
    errorCode = ecy_HSM_Configure(NULL_PTR, 0UL);
#endif
    if( ecy_hsm_CSAI_SUCCESS != errorCode )
    {
        Hsm_82_CycurHsm_Callout_Error();
    }
#if (USR_HSM_SETTINR_RAM == STD_ON)
    Hsm_82_CycurHsm_RAM_Init();
#endif


}

/******************************************************************/
/* Hsm_82_CycurHsm_InitTwo */
/******************************************************************/
void Hsm_82_CycurHsm_InitTwo(void)
{

#if (USR_CRYPTO_DRIVER == USE_CRYPTO_82_HSM)
    uint32                 loopCount = 0UL;
    uint32                 startTime = 0UL;
    uint32                 elapsedTime = 0UL;
#endif

#if (USR_CRYPTO_DRIVER == USE_CRYPTO_82_HSM)
    Crypto_82_Hsm_Init(NULL_PTR);
    Hsm_82_CycurHsm_GetCounterValue(&startTime);
    /* Wait until Crypto_82_hsm finishes to read some keys from HSM. The target keys are defined in Crypto_82_Hsm configucation */
    do 
    {
        Crypto_82_Hsm_MainFunction();
        Hsm_82_CycurHsm_GetElapsedCounterValue(startTime, &elapsedTime);
        /* Time out will happen when "USR_INITIALKEYREAD_INETEVALTIME" * "USR_INITIALKEYREAD_MAXCOUNT" has passed */
        if (elapsedTime > USR_INITIALKEYREAD_INETEVALTIME)
        {
            loopCount++;
            Hsm_82_CycurHsm_Callout_WaitForInitialKeyRead();
            if (loopCount > USR_INITIALKEYREAD_MAXCOUNT)
            {
                /* If the time out happens in start up phase, some error might have happend in HSM side. */ 
                Hsm_82_CycurHsm_Callout_Error();
                break;
            }
            /* Reset start time */
            Hsm_82_CycurHsm_GetCounterValue(&startTime);
        }
    } while (E_OK != Crypto_82_Hsm_GetDriverStatus());
    
#endif

}

/******************************************************************/
/* Hsm_82_CycurHsm_MainFunction */
/******************************************************************/
void Hsm_82_CycurHsm_MainFunction(void)
{
    uint32 HSMErrorFlags;
    HSMErrorFlags = Hsm_82_CycurHsm_GetFatalErrorFlags();

    if (0UL != HSMErrorFlags)
    {
        /* Error Callout */
        Hsm_82_CycurHsm_Callout_Error();
    }

}

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/*--------------------------------------------------------------------------*/
/* History                                                                  */
/*  Version    :Date       :Description                                     */
/*  1.0.0      :yyyy/mm/dd :Create new                xxx                   */
/*--------------------------------------------------------------------------*/
/**** End of File ***********************************************************/
