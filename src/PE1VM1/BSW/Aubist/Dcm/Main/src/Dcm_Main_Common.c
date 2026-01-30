/* Dcm_Main_Common_c(v5-8-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Main_Common/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Main/cfg/Dcm_Main_Common_Cfg.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include "../../Main/inc/Dcm_Version.h"
#include "../../Dsd/inc/Dcm_Dsd_Main.h"
#include "../../Dsd/inc/Dcm_Dsd_ServiceMng.h"
#include "../../Dsl/inc/Dcm_Dsl_Main.h"

#include <Dcm.h>
#include <SchM_Dcm.h>

#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_Common_Connector.h>
#include <Dcm/Dcm_Main_TmrSrv.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include <Dcm/Dcm_Dsp_DidMng.h>
#include <Dcm/Dcm_Dsl_Ctrl.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Dcm Init Status */
#define DCM_MAIN_ACTIVE         ((uint8)0xA5U)      /* Dcm Init             */
#define DCM_MAIN_MIRROR_ACTIVE  ((uint8)0x5AU)      /* Dcm Init(Mirror)     */

/* Dcm_Main_Memset */
#define DCM_MAIN_REMAINED_BUFSIZE_8                             ((uint16)8U)
#define DCM_MAIN_REMAINED_BUFSIZE_7                             ((uint16)7U)
#define DCM_MAIN_REMAINED_BUFSIZE_6                             ((uint16)6U)
#define DCM_MAIN_REMAINED_BUFSIZE_5                             ((uint16)5U)
#define DCM_MAIN_REMAINED_BUFSIZE_4                             ((uint16)4U)
#define DCM_MAIN_REMAINED_BUFSIZE_3                             ((uint16)3U)
#define DCM_MAIN_REMAINED_BUFSIZE_2                             ((uint16)2U)
#define DCM_MAIN_REMAINED_BUFSIZE_1                             ((uint16)1U)
#define DCM_MAIN_BUFFER_INDEX_7                                 ((uint8)7U)
#define DCM_MAIN_BUFFER_INDEX_6                                 ((uint8)6U)
#define DCM_MAIN_BUFFER_INDEX_5                                 ((uint8)5U)
#define DCM_MAIN_BUFFER_INDEX_4                                 ((uint8)4U)
#define DCM_MAIN_BUFFER_INDEX_3                                 ((uint8)3U)
#define DCM_MAIN_BUFFER_INDEX_2                                 ((uint8)2U)
#define DCM_MAIN_BUFFER_INDEX_1                                 ((uint8)1U)
#define DCM_MAIN_BUFFER_INDEX_0                                 ((uint8)0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( void, DCM_CODE ) Dcm_Main_InternalInit
( void );

#if ( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Main_RespReqAfterEcuReset
( void );
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Main_ReadVinFromSWC
(
    Dcm_OpStatusType u1OpStatus,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData
);
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Main_ReadVinFromRAM
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData
);

#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Main_ReadMasterVin
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData
);
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */

#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Main_ClearMasterVin
( void );
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( volatile uint8, DCM_VAR_NO_INIT ) Dcm_Main_u1InitStatus;  /* Dcm Init Status  */
static VAR( volatile uint8, DCM_VAR_NO_INIT ) Dcm_Main_u1InitStatusMirror;  /* Dcm Init Status Mirror */

#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Main_u1VinMasterStatus;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Main_u1VinMasterInfo[DCM_MAIN_VIN_DATA_SIZE];
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Main_u1GetVinCntAfterInit;
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE_SHARE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Init                                                 */
/* Description   | Dcm init                                                 */
/* Preconditions | None                                                     */
/* Parameters    | [in] ConfigPtr : post-build ConfigParam                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_M_SATELLITE_USED == STD_ON )
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Init
(
    P2CONST( Dcm_ConfigType, AUTOMATIC, DCM_APPL_CONST ) ConfigPtr  /* MISRA DEVIATION */
)
{
    Dcm_ApplicationType u1_DcmApplType;

    if( Dcm_M_ptPartition == NULL_PTR )
    {
        /* No process */
    }
    else
    {
        u1_DcmApplType = Dcm_Main_Cnct_GetCurrentApplicationID();
        if( u1_DcmApplType == (Dcm_ApplicationType)DCM_INVALID_OSAPPLICATION )
        {
            /* No process */
        }
        else if( u1_DcmApplType == Dcm_M_ptPartition->ptMaster->u1MasterEcucPartition )
        {
            Dcm_Main_ClearMasterVin();

#if ( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
            Dcm_Main_RespReqAfterEcuReset();
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */
        }
        else
        {
            Dcm_Main_ClearSatelliteVin();
        }
    }

    return;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */
#endif /* DCM_M_SATELLITE_USED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Init                                                 */
/* Description   | Dcm init                                                 */
/* Preconditions | None                                                     */
/* Parameters    | [in] ConfigPtr : post-build ConfigParam                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_M_SATELLITE_USED == STD_OFF )
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Init
(
    P2CONST( Dcm_ConfigType, AUTOMATIC, DCM_APPL_CONST ) ConfigPtr  /* MISRA DEVIATION */
)
{
    Dcm_ApplicationType u1_DcmApplType;
    boolean             b_InitFlag;

    b_InitFlag = (boolean)FALSE;

    if( Dcm_M_ptPartition == NULL_PTR )
    {
        b_InitFlag = (boolean)TRUE;
    }
    else
    {
        u1_DcmApplType = Dcm_Main_Cnct_GetCurrentApplicationID();
        if( u1_DcmApplType == Dcm_M_ptPartition->ptMaster->u1MasterEcucPartition )
        {
            b_InitFlag = (boolean)TRUE;
        }
        else
        {
            /* No process */
        }
    }

    if( b_InitFlag == (boolean)TRUE )
    {
        Dcm_Main_ClearMasterVin();

#if ( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
        Dcm_Main_RespReqAfterEcuReset();
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */
    }

    return;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */
#endif /* DCM_M_SATELLITE_USED == STD_OFF */


/****************************************************************************/
/* Function Name | Dcm_Init                                                 */
/* Description   | Dcm init                                                 */
/* Preconditions | None                                                     */
/* Parameters    | [in] ConfigPtr : post-build ConfigParam                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_OFF )
FUNC( void, DCM_CODE ) Dcm_Init
(
    P2CONST( Dcm_ConfigType, AUTOMATIC, DCM_APPL_CONST ) ConfigPtr  /* MISRA DEVIATION */
)
{
    Dcm_ApplicationType u1_DcmApplType;
    boolean             b_InitFlag;

    b_InitFlag = (boolean)FALSE;

    if( Dcm_M_ptPartition == NULL_PTR )
    {
        b_InitFlag = (boolean)TRUE;
    }
    else
    {
        u1_DcmApplType = Dcm_Main_Cnct_GetCurrentApplicationID();
        if( u1_DcmApplType == Dcm_M_ptPartition->ptMaster->u1MasterEcucPartition )
        {
            b_InitFlag = (boolean)TRUE;
        }
        else
        {
            /* No process */
        }
    }

    if( b_InitFlag == (boolean)TRUE )
    {
        Dcm_Main_InternalInit();
        Dcm_Main_u1InitStatus = DCM_MAIN_ACTIVE;
        Dcm_Main_u1InitStatusMirror = DCM_MAIN_MIRROR_ACTIVE;
#if ( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
        Dcm_Main_RespReqAfterEcuReset();
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */
    }

    return;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_OFF */

#define DCM_STOP_SEC_CODE_SHARE
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_MainFunction                                         */
/* Description   | Dcm periodic function                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PERIODIC_SEND_USE == STD_OFF )
FUNC( void, DCM_CODE ) Dcm_MainFunction
( void )
{
    P2VAR(volatile uint8, AUTOMATIC, DCM_APPL_DATA) pt_InitStatus;
    P2VAR(volatile uint8, AUTOMATIC, DCM_APPL_DATA) pt_InitStatusMirror;
    uint8 u1_InitStatus;
    uint8 u1_InitStatusMirror;

    /* ECC (Error Correction Code) */
    pt_InitStatus  = &Dcm_Main_u1InitStatus;
    u1_InitStatus  = *pt_InitStatus;
    *pt_InitStatus = u1_InitStatus;
    pt_InitStatusMirror  = &Dcm_Main_u1InitStatusMirror;
    u1_InitStatusMirror  = *pt_InitStatusMirror;
    *pt_InitStatusMirror = u1_InitStatusMirror;

    if( u1_InitStatus == DCM_MAIN_ACTIVE )
    {
        Dcm_Dsl_IdleRefresh();
        Dcm_Dsp_IdleRefresh();
        Dcm_Main_TmrSrv_Main();
        Dcm_Main_EvtDistr_Main();
        Dcm_Main_u1InitStatusMirror = DCM_MAIN_MIRROR_ACTIVE;
    }
    else
    {
        if( u1_InitStatusMirror == DCM_MAIN_MIRROR_ACTIVE )
        {
            Dcm_Dsl_IdleRefresh();
            Dcm_Dsp_IdleRefresh();
            Dcm_Main_TmrSrv_Main();
            Dcm_Main_EvtDistr_Main();
            Dcm_Main_u1InitStatus = DCM_MAIN_ACTIVE;
        }
    }

    return;
}
#endif  /* DCM_PERIODIC_SEND_USE == STD_OFF */
#if ( DCM_PERIODIC_SEND_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_MainFunction
( void )
{
    P2VAR(volatile uint8, AUTOMATIC, DCM_APPL_DATA) pt_InitStatus;
    P2VAR(volatile uint8, AUTOMATIC, DCM_APPL_DATA) pt_InitStatusMirror;
    uint8 u1_InitStatus;
    uint8 u1_InitStatusMirror;

    /* ECC (Error Correction Code) */
    pt_InitStatus  = &Dcm_Main_u1InitStatus;
    u1_InitStatus  = *pt_InitStatus;
    *pt_InitStatus = u1_InitStatus;
    pt_InitStatusMirror  = &Dcm_Main_u1InitStatusMirror;
    u1_InitStatusMirror  = *pt_InitStatusMirror;
    *pt_InitStatusMirror = u1_InitStatusMirror;

    if( u1_InitStatus == DCM_MAIN_ACTIVE )
    {
        Dcm_Dsl_IdleRefresh();
        Dcm_Dsp_IdleRefresh();
        Dcm_Main_TmrSrv_Main();
        Dcm_Main_EvtDistr_Main();
        Dcm_Dsp_Main();
        Dcm_Main_u1InitStatusMirror = DCM_MAIN_MIRROR_ACTIVE;
    }
    else
    {
        if( u1_InitStatusMirror == DCM_MAIN_MIRROR_ACTIVE )
        {
            Dcm_Dsl_IdleRefresh();
            Dcm_Dsp_IdleRefresh();
            Dcm_Main_TmrSrv_Main();
            Dcm_Main_EvtDistr_Main();
            Dcm_Dsp_Main();
            Dcm_Main_u1InitStatus = DCM_MAIN_ACTIVE;
        }
    }

    return;
}
#endif  /* DCM_PERIODIC_SEND_USE == STD_ON */

#if ( DCM_VERSION_INFO_API == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_GetVersionInfo                                       */
/* Description   | Get dcm version information                              */
/* Preconditions | None                                                     */
/* Parameters    | [out]versionInfo : Dcm version infomation                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_GetVersionInfo                /* MISRA DEVIATION */
(
    P2VAR( Std_VersionInfoType, AUTOMATIC, DCM_APPL_DATA ) versionInfo
)
{
    versionInfo->vendorID = DCM_VENDOR_ID;
    versionInfo->moduleID = DCM_MODULE_ID;
    versionInfo->sw_major_version = DCM_SW_MAJOR_VERSION;
    versionInfo->sw_minor_version = DCM_SW_MINOR_VERSION;
    versionInfo->sw_patch_version = DCM_SW_PATCH_VERSION;

    return;
}
#endif /* DCM_VERSION_INFO_API == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CODE_SHARE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_GetVin                                               */
/* Description   | Get the VIN Infomation                                   */
/* Preconditions | None                                                     */
/* Parameters    | [out] ptData : VIN Infomation                            */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Successful acquisition of information      */
/*               |        E_NOT_OK : Failure                                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetVin              /* MISRA DEVIATION */
(
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData
)
{
    Std_ReturnType u1_RetVal;

    if( ptData != NULL_PTR )
    {
        u1_RetVal = Dcm_Main_ReadVinFromRAM( ptData );
    }
    else
    {
        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}

#define DCM_STOP_SEC_CODE_SHARE
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_SyncOsapComplete                                     */
/* Description   | This function receives completion of synchronization of  */
/*               | VIN information on the satellite side.                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |     E_OK : this value is always returned.                */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SyncOsapComplete
( void )
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( Dcm_Main_u1GetVinCntAfterInit == (uint8)STD_OFF )
    {
        (void)Dcm_Main_NotifyAct();     /* no return check required */

        Dcm_Main_u1GetVinCntAfterInit = STD_ON;
    }
    else
    {
        /* No process */
    }
    Dcm_Main_u1VinMasterStatus = DCM_MAIN_VIN_STATUS_UPDATED;

    return u1_RetVal;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Main_SetVin                                          */
/* Description   | This function writes the VIN information to the RAM on   */
/*               | the master side and synchronizes to the satellite side.  */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptData : VIN information                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Main_SetVin
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData
)
{
    uint8 u1_VinSetCnt;
    SchM_Enter_Dcm_Main_MasterVin();

    for( u1_VinSetCnt = (uint8)0; u1_VinSetCnt < DCM_MAIN_VIN_DATA_SIZE; u1_VinSetCnt++ )
    {
        Dcm_Main_u1VinMasterInfo[u1_VinSetCnt] = ptData[u1_VinSetCnt];
    }

    SchM_Exit_Dcm_Main_MasterVin();

    (void)SchM_Call_Dcm_IocS_SyncOsapData(ptData, DCM_MAIN_VIN_DATA_SIZE);      /* no return check required */

    return;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Main_SetVin                                          */
/* Description   | This function writes the VIN information to the RAM on   */
/*               | the master side and synchronizes to the satellite side.  */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptData : VIN information                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_OFF )
#if ( DCM_SUPPORT_SID2E == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Main_SetVin
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData    /* MISRA DEVIATION */
)
{
    return;
}
#endif /* DCM_SUPPORT_SID2E == STD_ON */
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_OFF */

/****************************************************************************/
/* Function Name | Dcm_Main_SyncOsapDataCbk                                 */
/* Description   | This function is a callback for updating the master side */
/*               | VIN information.                                         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1TimerId : Timer ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Main_SyncOsapDataCbk
(
    const uint8 u1TimerId       /* MISRA DEVIATION */
)
{
    Std_ReturnType u1_RetVal;
    uint8 u1_VinInfo[DCM_MAIN_VIN_DATA_SIZE];

    if( Dcm_Main_u1VinMasterStatus == DCM_MAIN_VIN_STATUS_INIT )
    {
        u1_RetVal = Dcm_Main_ReadVinFromSWC(DCM_INITIAL, u1_VinInfo);
    }
    else
    {
        u1_RetVal = Dcm_Main_ReadVinFromSWC(DCM_PENDING, u1_VinInfo);
    }

    if( u1_RetVal == (uint8)E_OK )
    {
        Dcm_Main_SetVin(u1_VinInfo);
    }
    else if( u1_RetVal == (uint8)DCM_E_PENDING )
    {
        Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_SYNC_OSAP_DATA, (uint8)0);

        Dcm_Main_u1VinMasterStatus = DCM_MAIN_VIN_STATUS_PENDING;
    }
    else
    {
        if( Dcm_Main_u1GetVinCntAfterInit == (uint8)STD_OFF )
        {
            (void)Dcm_Main_NotifyAct();     /* no return check required */

            Dcm_Main_u1GetVinCntAfterInit = STD_ON;
        }
        else
        {
            /* No process */
        }
        Dcm_Main_u1VinMasterStatus = DCM_MAIN_VIN_STATUS_INIT;
    }

    return;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_GetSleepPermission                                   */
/* Description   | Notify of sleep availability information of DCM.         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Sleep possible                            */
/*               |        FALSE : Sleep impossible                          */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_GetSleepPermission         /* MISRA DEVIATION */
( void )
{
    boolean b_RetVal;

    b_RetVal = Dcm_Dsl_GetSleepPermission();
    if( b_RetVal == (boolean)TRUE )
    {
        b_RetVal = Dcm_Dsp_GetSleepPermission();
    }

    return b_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_GetBusSleepPermission                                */
/* Description   | Notify of Bus Sleep availability information of DCM.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] bRecptionPeriodEnable : Reception Period Enable     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : BusSleep possible                         */
/*               |        FALSE : BusSleep impossible                       */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_GetBusSleepPermission
(
    const boolean bRecptionPeriodEnable
)
{
    boolean b_RetVal;

    if( bRecptionPeriodEnable == (boolean)TRUE )
    {
        b_RetVal = Dcm_Dsl_GetSleepPermission();
    }
    else
    {
        b_RetVal = Dcm_Dsl_GetBusSleepPermission();
    }

    return b_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_PreWriteAll                                          */
/* Description   | Dcm_PreWriteAll                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_PreWriteAll
( void )
{
    uint8           u1_InitStatus;
    uint8           u1_InitStatusMirror;

    u1_InitStatus       = Dcm_Main_u1InitStatus;
    u1_InitStatusMirror = Dcm_Main_u1InitStatusMirror;

    if( u1_InitStatus == DCM_MAIN_ACTIVE )
    {
        Dcm_Dsp_Main_PreWriteAll();
    }
    else
    {
        if( u1_InitStatusMirror == DCM_MAIN_MIRROR_ACTIVE )
        {
            Dcm_Dsp_Main_PreWriteAll();
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Main_SetMemory                                       */
/* Description   | Set the specified data in memory.                        */
/* Preconditions |                                                          */
/* Parameters    | [out] ptBufferPtr :                                      */
/*               |        Address to set the data.                          */
/*               | [in] u1CharData :                                        */
/*               |        Data to set.                                      */
/*               | [in] u2BufferSize :                                      */
/*               |        Memory size for setting data.                     */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Main_SetMemory
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    ptBufferPtr,
    const uint8                                 u1CharData,
    const uint16                                u2BufferSize
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_DstPtr;
    uint16                                      u2_RemainSize;

    pt_DstPtr       = ptBufferPtr;
    u2_RemainSize   = u2BufferSize;

    while( u2_RemainSize >= DCM_MAIN_REMAINED_BUFSIZE_8 )
    {
        pt_DstPtr[DCM_MAIN_BUFFER_INDEX_7] = u1CharData;
        pt_DstPtr[DCM_MAIN_BUFFER_INDEX_6] = u1CharData;
        pt_DstPtr[DCM_MAIN_BUFFER_INDEX_5] = u1CharData;
        pt_DstPtr[DCM_MAIN_BUFFER_INDEX_4] = u1CharData;
        pt_DstPtr[DCM_MAIN_BUFFER_INDEX_3] = u1CharData;
        pt_DstPtr[DCM_MAIN_BUFFER_INDEX_2] = u1CharData;
        pt_DstPtr[DCM_MAIN_BUFFER_INDEX_1] = u1CharData;
        pt_DstPtr[DCM_MAIN_BUFFER_INDEX_0] = u1CharData;
        pt_DstPtr = &pt_DstPtr[DCM_MAIN_REMAINED_BUFSIZE_8];
        u2_RemainSize -= DCM_MAIN_REMAINED_BUFSIZE_8;
    }

    switch( u2_RemainSize )
    {
        case DCM_MAIN_REMAINED_BUFSIZE_7:
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_6] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_5] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_4] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_3] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_2] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_1] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_0] = u1CharData;
            break;
        case DCM_MAIN_REMAINED_BUFSIZE_6:
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_5] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_4] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_3] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_2] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_1] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_0] = u1CharData;
            break;
        case DCM_MAIN_REMAINED_BUFSIZE_5:
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_4] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_3] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_2] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_1] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_0] = u1CharData;
            break;
        case DCM_MAIN_REMAINED_BUFSIZE_4:
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_3] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_2] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_1] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_0] = u1CharData;
            break;
        case DCM_MAIN_REMAINED_BUFSIZE_3:
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_2] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_1] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_0] = u1CharData;
            break;
        case DCM_MAIN_REMAINED_BUFSIZE_2:
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_1] = u1CharData;
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_0] = u1CharData;
            break;
        case DCM_MAIN_REMAINED_BUFSIZE_1:
            pt_DstPtr[DCM_MAIN_BUFFER_INDEX_0] = u1CharData;
            break;
        default:
            /* No process */
            break;
    }

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dcm_Main_InternalInit                                    */
/* Description   | Dcm_Main_InternalInit                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Main_InternalInit
( void )
{
    Dcm_Main_TmrSrv_Init();
    Dcm_Main_EvtDistr_Init();

    Dcm_Dsp_Init();
    Dcm_Dsd_Init();
    Dcm_Dsl_Init();

    return;
}

#if ( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Main_RespReqAfterEcuReset                            */
/* Description   | Response request after Ecu reset.                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Main_RespReqAfterEcuReset
( void )
{
    Dcm_ProgConditionsType      st_ProgConditions;

    st_ProgConditions.ConnectionId = (uint16)0U;
    st_ProgConditions.TesterAddress = (uint16)0U;
    st_ProgConditions.Sid = (uint8)0U;
    st_ProgConditions.SubFncId = (uint8)0U;
    st_ProgConditions.ReprogramingRequest = (boolean)FALSE;
    st_ProgConditions.ApplUpdated = (boolean)FALSE;
    st_ProgConditions.ResponseRequired = (boolean)FALSE;

    (void)Dcm_GetProgConditions( &st_ProgConditions );      /* no return check required */

    Dcm_Dsl_SetupProgConditions( &st_ProgConditions );

    return;
}
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Main_ReadVinFromSWC                                  */
/* Description   | Read the VIN Infomation from SW-C                        */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1OpStatus : Operation state                        */
/*               | [out] ptData : VIN Infomation                            */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Failure                                */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Main_ReadVinFromSWC
(
    Dcm_OpStatusType u1OpStatus,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData
)
{
    Std_ReturnType u1_RetVal;
    Dcm_Main_ReturnCheckType u1_DidMngRetval;
    uint16 u2_did;
    uint16 u2_didIndex;
    uint8 u1_ControlReadWriteSupport;
    uint32 u4_Length;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    uint32 u4_DataBufLen;

    u1_RetVal       = E_NOT_OK;
    u2_didIndex     = (uint16)0x0000U;
    u1_ControlReadWriteSupport = (uint8)0x00U;
    u4_Length       = (uint32)0U;
    u1_ErrorCode    = (uint8)0x00U;
    u4_DataBufLen   = (uint32)DCM_MAIN_VIN_DATA_SIZE;

    if( Dcm_M_General.bVinRefNum == (uint8)0x01U )
    {
        u2_did = Dcm_M_General.u2VinRef;
        u1_DidMngRetval = Dcm_Dsp_DidMng_ChkDid( u2_did, DCM_DSP_DIDMNG_DID_RANGE, &u2_didIndex, &u1_ControlReadWriteSupport );
        if( u1_DidMngRetval == DCM_MAIN_E_CHECK_OK )
        {
            if( ( u1_ControlReadWriteSupport & DCM_DSP_DIDMNG_READ_ONLY ) != (uint8)0x00U )
            {
                u1_RetVal = Dcm_Dsp_DidMng_CallReadDidFnc( u2_didIndex, u2_did, ptData, u1OpStatus, u4_DataBufLen, &u4_Length, &u1_ErrorCode );
            }
        }
    }
    return u1_RetVal;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Main_ReadVinFromRAM                                  */
/* Description   | This function reads VIN information from RAM.            */
/* Preconditions | None                                                     */
/* Parameters    | [out] ptData : VIN information                           */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Successful acquisition of VIN information  */
/*               |        E_NOT_OK : Failure                                */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_M_SATELLITE_USED == STD_ON )
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Main_ReadVinFromRAM
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData
)
{
    uint8 u1_RetVal;
    uint8 u1_RetReadMasterVin;
    uint8 u1_RetReadSatelliteVin;
    Dcm_ApplicationType u1_DcmApplType;

    u1_RetVal = E_NOT_OK;
    u1_RetReadMasterVin = E_NOT_OK;
    u1_RetReadSatelliteVin = E_NOT_OK;

    if( Dcm_M_ptPartition == NULL_PTR )
    {
        /* No process */
    }
    else
    {
        u1_DcmApplType = Dcm_Main_Cnct_GetCurrentApplicationID();
        if( u1_DcmApplType == (Dcm_ApplicationType)DCM_INVALID_OSAPPLICATION )
        {
            /* No process */
        }
        else if( u1_DcmApplType == Dcm_M_ptPartition->ptMaster->u1MasterEcucPartition )
        {
            u1_RetReadMasterVin = Dcm_Main_ReadMasterVin(ptData);
            u1_RetVal = u1_RetReadMasterVin;
        }
        else
        {
            u1_RetReadSatelliteVin = Dcm_Main_ReadSatelliteVin(ptData);
            u1_RetVal = u1_RetReadSatelliteVin;
        }
    }

    return u1_RetVal;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */
#endif /* DCM_M_SATELLITE_USED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Main_ReadVinFromRAM                                  */
/* Description   | This function reads VIN information from RAM.            */
/* Preconditions | None                                                     */
/* Parameters    | [out] ptData : VIN information                           */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Successful acquisition of VIN information  */
/*               |        E_NOT_OK : Failure                                */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_M_SATELLITE_USED == STD_OFF )
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Main_ReadVinFromRAM
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData
)
{
    uint8 u1_RetVal;
    uint8 u1_RetReadMasterVin;
    Dcm_ApplicationType u1_DcmApplType;

    u1_RetVal = E_NOT_OK;

    if( Dcm_M_ptPartition == NULL_PTR )
    {
        u1_RetReadMasterVin = Dcm_Main_ReadMasterVin(ptData);
        u1_RetVal = u1_RetReadMasterVin;
    }
    else
    {
        u1_DcmApplType = Dcm_Main_Cnct_GetCurrentApplicationID();
        if( u1_DcmApplType == Dcm_M_ptPartition->ptMaster->u1MasterEcucPartition )
        {
            u1_RetReadMasterVin = Dcm_Main_ReadMasterVin(ptData);
            u1_RetVal = u1_RetReadMasterVin;
        }
        else
        {
            /* No process */
        }
    }

    return u1_RetVal;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */
#endif /* DCM_M_SATELLITE_USED == STD_OFF */

/****************************************************************************/
/* Function Name | Dcm_Main_ReadVinFromRAM                                  */
/* Description   | This function reads VIN information from RAM.            */
/* Preconditions | None                                                     */
/* Parameters    | [out] ptData : VIN information                           */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_NOT_OK : Failure                                */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Main_ReadVinFromRAM
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData     /* MISRA DEVIATION */
)
{
    uint8 u1_RetVal;

    u1_RetVal = E_NOT_OK;

    return u1_RetVal;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_OFF */

/****************************************************************************/
/* Function Name | Dcm_Main_ReadMasterVin                                   */
/* Description   | This function reads master side VIN information.         */
/* Preconditions | None                                                     */
/* Parameters    | [out] ptData : VIN information                           */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Successful acquisition of VIN information  */
/*               |        E_NOT_OK : Failure                                */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Main_ReadMasterVin
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData
)
{
    uint8 u1_RetVal;
    uint8 u1_VinReadCnt;

    u1_RetVal = E_NOT_OK;

    if( Dcm_Main_u1VinMasterStatus == DCM_MAIN_VIN_STATUS_UPDATED )
    {
        SchM_Enter_Dcm_Main_MasterVin();

        for( u1_VinReadCnt = (uint8)0; u1_VinReadCnt < DCM_MAIN_VIN_DATA_SIZE; u1_VinReadCnt++ )
        {
            ptData[u1_VinReadCnt] = Dcm_Main_u1VinMasterInfo[u1_VinReadCnt];
        }

        SchM_Exit_Dcm_Main_MasterVin();

        u1_RetVal = E_OK;
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Main_ClearMasterVin                                  */
/* Description   | Initialize master side VIN information.                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Main_ClearMasterVin
( void )
{
    uint8 u1_VinClearCnt;

    Dcm_Main_InternalInit();

    Dcm_Main_u1GetVinCntAfterInit = STD_OFF;

    for( u1_VinClearCnt = (uint8)0; u1_VinClearCnt < DCM_MAIN_VIN_DATA_SIZE; u1_VinClearCnt++ )
    {
        Dcm_Main_u1VinMasterInfo[u1_VinClearCnt] = (uint8)0;
    }

    Dcm_Main_u1VinMasterStatus = DCM_MAIN_VIN_STATUS_INIT;

    Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_SYNC_OSAP_DATA, (uint8)0);

    Dcm_Main_u1InitStatus = DCM_MAIN_ACTIVE;
    Dcm_Main_u1InitStatusMirror = DCM_MAIN_MIRROR_ACTIVE;

    return;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-07-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
