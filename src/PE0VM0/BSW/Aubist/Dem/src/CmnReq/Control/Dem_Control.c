/* Dem_Control_c(v5-5-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_CmnLib_TSFFD.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Control_WWHOBD.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Pm_StoredData.h"
#include "../../../inc/Dem_Pm_Ind.h"
#include "../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../inc/Dem_Pm_PID.h"
#include "../../../inc/Dem_Pm_DTR.h"
#include "../../../inc/Dem_Pm_IUMPR.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_Pm_PreFFD.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_Pm_OccrDTC.h"
#include "../../../inc/Dem_Pm_AltIUMPR.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Udm_Control.h"

#include "Dem_Control_cmn_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
typedef uint8        Dem_u08_CtlInitProcessType;                /*  Control Initialize status                  */

#define DEM_CTL_INIT_PROCESS_NONE       ((Dem_u08_CtlInitProcessType)0x00U)
#define DEM_CTL_INIT_PROCESS_MONSTS     ((Dem_u08_CtlInitProcessType)0x11U)
#define DEM_CTL_INIT_PROCESS_COMPLETE   ((Dem_u08_CtlInitProcessType)0x22U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static  VAR( Dem_u08_CtlInitProcessType, DEM_VAR_NO_INIT ) Dem_CtlInitProcess;
static  VAR( volatile Dem_u08_InitStatusType, DEM_VAR_NO_INIT ) Dem_CtlInitStatus;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST          /*  PreInit section                     */
#include <Dem_MemMap.h>
/****************************************************************************/
/* Function Name | Dem_Control_PreInit                                      */
/* Description   | Pre-initializes Dem_Control.                             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_Control_PreInit          /*  PreInit section     */
( void )
{
    Dem_CtlInitStatus = DEM_CTL_STS_INIT_UNINITIALIZED;


    /* Pre-Initialization of each unit */
    Dem_Control_PreInitDTCSettingStatus();

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_DataAvl_PreInitForAvl();
#endif  /* ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON ) */
    Dem_Event_PreInitEventFailureCycleCounterThreshold();
    Dem_Ind_PreInit_WIRStatus();
    Dem_AsyncReq_PreInit();

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_DTC_PreInitPFCRecordStatus();
#endif  /*  ( DEM_PFC_SUPPORT == STD_ON )   */

#if ( DEM_TRIGGER_DCM_REPORTS == STD_ON )   /*  [FuncSw]    */
    Dem_OccrDTC_PreInitNotifyDTCStatusChanged();
#endif  /*   ( DEM_TRIGGER_DCM_REPORTS == STD_ON )          */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_PreInit();
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    Dem_CtlInitStatus = DEM_CTL_STS_INIT_PREINIT_COMPLETE;

    return;
}

#define DEM_STOP_SEC_CODE_TRUST           /*  PreInit section                     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
/****************************************************************************/
/* Function Name | Dem_Control_Init                                         */
/* Description   | Full-initializes Dem_Control.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_Init
( void )
{
    VAR( Dem_u08_InitStatusType, AUTOMATIC ) initStatus;

    initStatus = Dem_CtlInitStatus;
    if( initStatus == DEM_CTL_STS_INIT_PREINIT_COMPLETE )
    {
        /* Internal variable initialization */
        Dem_Control_InitAsyncReq();
        Dem_Control_Clear_ClearDTCInfo();
        Dem_Control_InitDTCSettingStatus();
        Dem_Control_InitDTCRecordUpdateInfo();
        Dem_Control_InitDTCStoredDataStatus();
        Dem_Control_InitInfoForOpCycleStart();

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    /*  [FuncSw]    */
        Dem_Control_InitPIDInfo();
#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON ) */

#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_Control_InitIUMPRInfo();
#endif  /*   ( DEM_IUMPR_SUPPORT == STD_ON )    */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )    /*  [FuncSw]    */
        Dem_Control_InitIndMI();
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

        /* Initialization of each unit */
        Dem_Event_InitQualification();
        Dem_DataCtl_Init();

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
        Dem_DTC_InitForPFC();
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )            */

#if ( DEM_PID_SUPPORT == STD_ON )   /*  [FuncSw]    */
        Dem_PID_Init();
#endif  /*   ( DEM_PID_SUPPORT == STD_ON )          */

#if ( DEM_TSFF_SUPPORT == STD_ON )  /*  [FuncSw]    */
        Dem_TSFFD_Init();
#endif  /*   ( DEM_TSFF_SUPPORT == STD_ON )         */

        Dem_StoredData_Init();

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )   /*  [FuncSw]    */
        Dem_OccrDTC_Init();
#endif  /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )            */

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
        Dem_MonSts_Init();
#endif  /*   ( DEM_TRIGGER_FIM_REPORTS == STD_ON )  */

#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_IUMPR_Init();
#endif  /*   ( DEM_IUMPR_SUPPORT == STD_ON )    */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_Misfire_Init();
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_UdmControl_Init();
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */

#if ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_OpCycle_ClearProgressEngine1000RPM();
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )                          */

        Dem_CtlInitProcess  =   DEM_CTL_INIT_PROCESS_NONE;
        Dem_CtlInitStatus   =   DEM_CTL_STS_INIT_INITIALIZING;
    }
    else
    {
        /* For processing execution in an incorrect initialization state */
        /* No process */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_Shutdown                                     */
/* Description   | Shuts down Dem_Control.                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_Shutdown
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    checkStatus = Dem_Control_ChkAfterPreInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Shutdown of each unit */
        Dem_AsyncReq_Shutdown();

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
        Dem_MonSts_Shutdown();
#endif  /*   ( DEM_TRIGGER_FIM_REPORTS == STD_ON )          */

        Dem_CtlInitStatus   =   DEM_CTL_STS_INIT_PREINIT_COMPLETE;
    }
    else
    {
        /* For processing execution in an incorrect initialization state */
        /* No process */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_InitProcess                                  */
/* Description   | Initializes Dem_Control.                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : init complete                        */
/*               |        DEM_IRT_PENDING : init continue                   */
/*               |        DEM_IRT_NG : init failed                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_InitProcess
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InitStatusType, AUTOMATIC ) initStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retMonStsInitProc;
    VAR( Dem_u08_CtlInitProcessType, AUTOMATIC ) ctlInitProcess;

    VAR( boolean, AUTOMATIC ) igCycleUpdated;
    VAR( boolean, AUTOMATIC ) drivingCycleQualified;
    VAR( boolean, AUTOMATIC ) warmupCycleQualified;

    retVal = DEM_IRT_NG;

    ctlInitProcess = Dem_CtlInitProcess;
    initStatus = Dem_CtlInitStatus;
    if( initStatus == DEM_CTL_STS_INIT_INITIALIZING )
    {
        if( ctlInitProcess == DEM_CTL_INIT_PROCESS_NONE )
        {
            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - start.   */
            Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
            /*--------------------------------------*/

            Dem_Data_SetNumOfFaultAndFFD();

            /* Call Init of DataCtl after consistency check is finished */
            Dem_DataCtl_Init_AfterRecordCheckComplete();

#if ( DEM_TSFF_SUPPORT == STD_ON )    /* [FuncSw] */
            /* Initializes time-series freeze frame related  memory. */
            Dem_Data_InitTSFFD_AfterRecordCheckComplete();
#endif  /*  ( DEM_TSFF_SUPPORT == STD_ON )  */

#if ( DEM_DTR_SUPPORT == STD_ON )   /*  [FuncSw]    */
            Dem_DTR_Init_AfterRecordCheckComplete();
#endif  /* ( DEM_DTR_SUPPORT == STD_ON )    */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
            Dem_UdmControl_Init_AfterRecordCheckComplete();
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

            /*----------------------------------------------*/
            /*  OperationCycle auto restart     */
            igCycleUpdated              =   (boolean)FALSE;
            drivingCycleQualified       =   (boolean)FALSE;
            warmupCycleQualified        =   (boolean)FALSE;
            Dem_Control_RestartOpCycleInitProcess( &igCycleUpdated, &drivingCycleQualified, &warmupCycleQualified );

            /*  generate order list.              */
            Dem_Data_GenerateFaultOrderList();

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /* [FuncSw] */
            Dem_Data_GenerateConfirmedFaultOrderList();
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )      */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) /*  [FuncSw]    */
            Dem_Data_GenerateMILFaultOrderList();
#endif  /*   ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )        */

            Dem_Data_ClearSearchFFDIndex();

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
            Dem_UdmControl_GenerateRecordInfo();
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
            /* In  [OperationCycle auto restart : exec end job], exec B1Record Update. */
            /* follow the order, Generate IndMIIndexList -> B1Record Update. */
            Dem_IndMI_Init_AfterOrderListGenerateComplete();
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

            /*  OperationCycle auto restart : exec end job.    */
            Dem_Control_RestartOpCycleInitEndProcess( igCycleUpdated, drivingCycleQualified, warmupCycleQualified );

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    /*  [FuncSw]    */
            Dem_PID_ConfirmedDTCClear();
#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )             */

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )    /*  [FuncSw]    */
            Dem_OccrDTC_Init_AfterOrderListGenerateComplete();
#endif  /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )             */

            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - end.     */
            Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
            /*--------------------------------------*/

            ctlInitProcess = DEM_CTL_INIT_PROCESS_MONSTS;
        }

        if( ctlInitProcess == DEM_CTL_INIT_PROCESS_MONSTS )
        {
            retMonStsInitProc = Dem_MonSts_ReCalcProc( DEM_MONSTS_RECALC_TYPE_INIT );
            if( retMonStsInitProc != DEM_IRT_PENDING )
            {
                ctlInitProcess = DEM_CTL_INIT_PROCESS_COMPLETE;
            }
        }

        if( ctlInitProcess == DEM_CTL_INIT_PROCESS_COMPLETE )
        {
            Dem_CtlInitStatus   =   DEM_CTL_STS_INIT_COMPLETE;
            ctlInitProcess = DEM_CTL_INIT_PROCESS_NONE;
            retVal = DEM_IRT_OK;
        }
        else
        {
            retVal = DEM_IRT_PENDING;
        }

    }
    else
    {
        /* For processing execution in an incorrect initialization state */
        /* No process */
    }
    Dem_CtlInitProcess = ctlInitProcess;

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_Process                                      */
/* Description   | Main function of the periodicity processing.             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_Process
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Async processing */
        Dem_Control_SetEventProcess();
        Dem_Control_ClearDTCProcess();
        Dem_Control_DTCSettingProcess();

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    /*  [FuncSw]    */
        Dem_Control_UpdatePIDProcess();
#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON ) */

#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_Control_UpdateIUMPRProcess();
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )  */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )    /*  [FuncSw]    */
        Dem_Control_UpdateB1CounterProcess();
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    }
    else
    {
        /* For processing execution in an incorrect initialization state */
        /* No process */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_RefreshRAM                                   */
/* Description   | Refresh RAM  - Control                                   */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_RefreshRAM
( void )
{
    VAR( volatile Dem_u08_InitStatusType, AUTOMATIC )                    u8_dummy;               /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u08_InitStatusType, AUTOMATIC, DEM_VAR_NO_INIT ) u8_dummyPtr;     /*  for GlobalVariable address       */

    /* Exclusion is not necessary   */
    u8_dummyPtr    = &Dem_CtlInitStatus;     /*  set GlobalVariable pointer  */
    u8_dummy       = *u8_dummyPtr;    /*  read GlobalVariable data    */
    *u8_dummyPtr   = u8_dummy;               /*  rewrite GlobalVariable data */

    Dem_Control_DTCSettingStatus_RefreshRAM();
    Dem_Control_Clear_RefreshRAM();
    Dem_Control_OpCycle_RefreshRAM();

#if ( DEM_ASYNCDATAQUE_USE == STD_ON )  /* [FuncSw] */
    Dem_AsyncReq_RefreshRAM();
#endif  /* ( DEM_ASYNCDATAQUE_USE == STD_ON )   */

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_PFC_RefreshRAM();
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )          */

    return ;
}

/*--------------------------------------------------------------------------*/
/* Unit Internal functions -data-                                           */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Function Name | Dem_Control_ChkAfterCompleteInit                         */
/* Description   | Check if the status is initialization complete.          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Status initialization complete.      */
/*               |        DEM_IRT_NG : Status initialization not completed. */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ChkAfterCompleteInit
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InitStatusType, AUTOMATIC ) initStatus;

    retVal = DEM_IRT_NG;

    initStatus = Dem_CtlInitStatus;
    if( initStatus == DEM_CTL_STS_INIT_COMPLETE )
    {
        retVal = DEM_IRT_OK;
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_ChkAfterInit                                 */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ChkAfterInit
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InitStatusType, AUTOMATIC ) initStatus;

    retVal = DEM_IRT_NG;

    initStatus = Dem_CtlInitStatus;
    switch( initStatus )
    {
        case DEM_CTL_STS_INIT_UNINITIALIZED:
            /* The same processing as DEM_CTL_STS_INIT_PREINIT_COMPLETE */
        case DEM_CTL_STS_INIT_PREINIT_COMPLETE:
            /* No process */
            break;
        case DEM_CTL_STS_INIT_INITIALIZING:
            /* The same processing as DEM_CTL_STS_INIT_COMPLETE */
        case DEM_CTL_STS_INIT_COMPLETE:
            retVal = DEM_IRT_OK;
            break;
        default:
            /* No process */
            break;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_ChkAfterPreInit                              */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ChkAfterPreInit
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InitStatusType, AUTOMATIC ) initStatus;

    retVal = DEM_IRT_NG;

    initStatus = Dem_CtlInitStatus;
    switch( initStatus )
    {
        case DEM_CTL_STS_INIT_UNINITIALIZED:
            /* No process */
            break;
        case DEM_CTL_STS_INIT_PREINIT_COMPLETE:
            /* The same processing as DEM_CTL_STS_INIT_COMPLETE */
        case DEM_CTL_STS_INIT_INITIALIZING:
            /* The same processing as DEM_CTL_STS_INIT_COMPLETE */
        case DEM_CTL_STS_INIT_COMPLETE:
            retVal = DEM_IRT_OK;
            break;
        default:
            /* No process */
            break;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_ChkInitStatus                                */
/* Description   | Check Dem_Control initialize status.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] InitStatus :                                        */
/*               |        init status                                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ChkInitStatus
(
    VAR( Dem_u08_InitStatusType, AUTOMATIC ) InitStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InitStatusType, AUTOMATIC ) currentInitStatus;

    retVal = DEM_IRT_NG;

    currentInitStatus = Dem_CtlInitStatus;
    if( InitStatus <= currentInitStatus )
    {
        retVal = DEM_IRT_OK;
    }

    return retVal;
}



/*--------------------------------------------------------------------------*/
/* Empty functions for function switching.                                  */
/*--------------------------------------------------------------------------*/

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
