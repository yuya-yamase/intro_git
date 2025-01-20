/* Dem_Main_c(v5-3-0)                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Main/CODE                                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Mm_MM.h"
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_Md_ModeMng.h"
#include "../../../inc/Dem_CmnLib_TSFFD.h"
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Mm_MemSync.h"
#include "../../../usr/Dem_DataVerify_Callout.h"
#include "../../../inc/Dem_Udm_Control.h"


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8        Dem_u08_InitProcessType;                /*  Initialize status                  */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Dem init status */
#define DEM_MAIN_STS_INIT_UNINITIALIZED        ((Dem_u08_InitProcessType)0x00U) /* Uninitialized                        */
#define DEM_MAIN_STS_INIT_PREINIT_COMPLETE     ((Dem_u08_InitProcessType)0x11U) /* PreInit completed                    */
#define DEM_MAIN_STS_INIT_CHECK_READNVM        ((Dem_u08_InitProcessType)0x22U) /* check execute Read NvM               */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#define DEM_MAIN_STS_INIT_READ_NVM             ((Dem_u08_InitProcessType)0x33U) /* Read NvM                             */
#define DEM_MAIN_STS_INIT_CHECK_DATAVERIFY     ((Dem_u08_InitProcessType)0x44U) /* check VerifyStart or not.            */
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )  */

#define DEM_MAIN_STS_INIT_START_DATAVERIFY     ((Dem_u08_InitProcessType)0x55U) /* Start verify record                  */
#define DEM_MAIN_STS_INIT_DATAVERIFY           ((Dem_u08_InitProcessType)0x66U) /* Verify Record                        */
#define DEM_MAIN_STS_INIT_CONTROL_INIT_PROCESS ((Dem_u08_InitProcessType)0x77U) /* Init Process after record checked.   */
#define DEM_MAIN_STS_INIT_COMPLETE             ((Dem_u08_InitProcessType)0x88U) /* Init process completed.              */


/* Definition value of counter for divide cycle to call each processes of Dem. */
#define DEM_MAIN_CTL_PROC_CYC_COUNTER_INITIAL       ((Dem_u08_ControlProcCycleCounterType)0x00U)
#define DEM_MAIN_CTL_PROC_CYC_COUNTER_RESET         ((Dem_u08_ControlProcCycleCounterType)0x00U)
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#define DEM_MAIN_NVM_SYNC_IDLE_CYC_COUNTER_INITIAL  ((Dem_u32_NvMProcIdleCycleCounterType)0x00U)
#define DEM_MAIN_NVM_SYNC_IDLE_CYC_COUNTER_RESET    ((Dem_u32_NvMProcIdleCycleCounterType)0x00U)
#define DEM_MAIN_NVM_SYNC_CYC_COUNTER_INITIAL       ((Dem_u08_NvMProcCycleCounterType)0x00U)
#define DEM_MAIN_NVM_SYNC_CYC_COUNTER_RESET         ((Dem_u08_NvMProcCycleCounterType)0x01U)
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )            */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_InitProcess
( void );
static FUNC( void, DEM_CODE ) Dem_RefreshRAM
( void );
static FUNC( void, DEM_CODE ) Dem_Main_RefreshRAM
( void );

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/* Counter for divide cycle to call  Dem_Control_Process */
static VAR( Dem_u08_ControlProcCycleCounterType, DEM_VAR_NO_INIT ) Dem_ControlProcessCycleCounter;

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/* Counter for divide Idle cycle to call  Dem_MM_Process */
static VAR( Dem_u32_NvMProcIdleCycleCounterType, DEM_VAR_NO_INIT ) Dem_NvMSyncIdleCycleCounter;

/* Counter for divide cycle to call  Dem_MM_Process */
static VAR( Dem_u08_NvMProcCycleCounterType, DEM_VAR_NO_INIT ) Dem_NvMSyncCycleCounter;
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )            */


/* Dem init status */
static VAR( volatile Dem_u08_InitProcessType, DEM_VAR_NO_INIT ) Dem_InitStatus;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST          /*  PreInit section                     */
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_PreInit                                              */
/* Description   | Pre-Initializes Dem.                                     */
/* Preconditions | Usable only once when not initialize Dem.                */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_PreInit                  /*  PreInit section     */
( void )
{
    Dem_InitStatus = DEM_MAIN_STS_INIT_UNINITIALIZED;

    /* PreInits Dem units */
    Dem_Control_PreInit();
    Dem_ModeMng_PreInit();

    /* Changes init status */
    Dem_InitStatus = DEM_MAIN_STS_INIT_PREINIT_COMPLETE;

    return ;
}

#define DEM_STOP_SEC_CODE_TRUST           /*  PreInit section                     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Init                                                 */
/* Description   | Full-initializes Dem.                                    */
/* Preconditions | Usable after pre-initialize Dem.                         */
/* Parameters    | [in] ConfigPtr :                                         */
/*               |        Pointer to the configuration set in VARIANT-POST- */
/*               |        BUILD.                                            */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Init
(
    P2CONST( Dem_ConfigType, AUTOMATIC, DEM_APPL_CONST ) ConfigPtr      /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InitProcessType, AUTOMATIC ) initStatus;

    initStatus  =   Dem_InitStatus;
    if ( initStatus == DEM_MAIN_STS_INIT_PREINIT_COMPLETE )
    {
        /* Inits Dem units */
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   /*  [FuncSw]    */
        Dem_MM_Init();
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )            */
        Dem_RecMngCmn_Init();
        Dem_Control_Init();
        Dem_ModeMng_Init();

        /* Inits unit local variable */
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   /*  [FuncSw]    */
        Dem_NvMSyncIdleCycleCounter = DEM_MAIN_NVM_SYNC_IDLE_CYC_COUNTER_INITIAL;
        Dem_NvMSyncCycleCounter = DEM_MAIN_NVM_SYNC_CYC_COUNTER_INITIAL;
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )            */
        Dem_ControlProcessCycleCounter = DEM_MAIN_CTL_PROC_CYC_COUNTER_INITIAL;

        /*  next status : check ReadAll executed.     */
        Dem_InitStatus = DEM_MAIN_STS_INIT_CHECK_READNVM;

        /*  initialize process.      */
        Dem_InitProcess();
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_Shutdown                                             */
/* Description   | Shuts down Dem.                                          */
/* Preconditions | Usable after full-initialize Dem.                        */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Shutdown
( void )
{
    VAR( Dem_u08_InitProcessType, AUTOMATIC ) initStatus;

    initStatus  =   Dem_InitStatus;
    if ( initStatus != DEM_MAIN_STS_INIT_UNINITIALIZED )
    {
        /* Shuts down Dem units */
        Dem_Control_Shutdown();
        Dem_RecMngCmn_Shutdown();
        Dem_ModeMng_Shutdown();

        /* Changes init status */
        Dem_InitStatus = DEM_MAIN_STS_INIT_PREINIT_COMPLETE;
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_GetMode                                              */
/* Description   | Get mode of Dem.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_ModeType                                             */
/*               |        0x0000-0xFFFF : Current Dem-mode.                 */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_ModeType, DEM_CODE ) Dem_GetMode
( void )
{
    VAR( Dem_ModeType, AUTOMATIC ) retVal;

    retVal = Dem_ModeMng_GetMode();

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_MainFunction                                         */
/* Description   | Processes all not event based Dem internal functions.    */
/* Preconditions | Usable after full-initialize Dem.                        */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MainFunction
( void )
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u32_NvMProcIdleCycleCounterType, AUTOMATIC ) syncNvmDivideIdleCycleCount;
    VAR( Dem_ModeType, AUTOMATIC ) demMode;
    VAR( Dem_u08_NvMProcCycleCounterType, AUTOMATIC ) syncNvmDivideCycleCount;
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )            */
    VAR( Dem_u08_ControlProcCycleCounterType, AUTOMATIC ) controlDivideCycleCount;
    VAR( Dem_u08_InitProcessType, AUTOMATIC ) initStatus;

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   /*  [FuncSw]    */
    syncNvmDivideIdleCycleCount = Dem_MainSyncNvmDivideIdleCycleCount;
    syncNvmDivideCycleCount = Dem_MainSyncNvmDivideCycleCount;
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )            */
    controlDivideCycleCount = Dem_MainControlDivideCycleCount;

    initStatus = Dem_InitStatus;

    if( initStatus == DEM_MAIN_STS_INIT_COMPLETE )
    {
        Dem_RefreshRAM();   /*  Refresh RAM( All Dem RAM ).         */

#if ( DEM_TSFF_SUPPORT == STD_ON )  /*  [FuncSw]    */
        Dem_TSFFD_SampleFreezeFrame();
#endif  /*   ( DEM_TSFF_SUPPORT == STD_ON )         */

        /* Calls Dem_Control_Process by Dem control divide cycle count */
        /*  ex.) 0,1,2,...      */
        Dem_ControlProcessCycleCounter = Dem_ControlProcessCycleCounter + (Dem_u08_ControlProcCycleCounterType)1U;
        if( Dem_ControlProcessCycleCounter >= controlDivideCycleCount )
        {
            Dem_ControlProcessCycleCounter = DEM_MAIN_CTL_PROC_CYC_COUNTER_RESET;
            Dem_Control_Process();
        }

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   /*  [FuncSw]    */
        /* Calls Dem_MM_Process by NvM divide cycle count */
        /*  ex.) 1,2,3,...      */
        Dem_NvMSyncCycleCounter = Dem_NvMSyncCycleCounter + (Dem_u08_NvMProcCycleCounterType)1U;
        if( Dem_NvMSyncCycleCounter > syncNvmDivideCycleCount )
        {
            Dem_NvMSyncCycleCounter = DEM_MAIN_NVM_SYNC_CYC_COUNTER_RESET;

            if( Dem_NvMSyncIdleCycleCounter < syncNvmDivideIdleCycleCount )
            {
                demMode = Dem_ModeMng_GetMode();
                demMode = ( demMode & DEM_MODE_PROCESSING_CLEAR_DTC );
                if( demMode != DEM_MODE_PROCESSING_CLEAR_DTC )
                {
                    Dem_NvMSyncIdleCycleCounter = Dem_NvMSyncIdleCycleCounter + (Dem_u32_NvMProcIdleCycleCounterType)1U;    /* no wrap around */
                }
                else
                {
                    Dem_NvMSyncIdleCycleCounter = syncNvmDivideIdleCycleCount;
                }
            }

            if( Dem_NvMSyncIdleCycleCounter >= syncNvmDivideIdleCycleCount )
            {
                Dem_MM_Process();
                demMode = Dem_ModeMng_GetMode();
                demMode = ( demMode & DEM_MODE_SYNCING_NVRAM );
                if( demMode != DEM_MODE_SYNCING_NVRAM )
                {
                    Dem_NvMSyncIdleCycleCounter = DEM_MAIN_NVM_SYNC_IDLE_CYC_COUNTER_RESET;
                }
            }
        }
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )            */
    }
    else
    {
        /*  init process.       */
        Dem_InitProcess();
    }
    return ;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ExpireNvMSyncIdleTaskTime                            */
/* Description   | Expire Dem_NvMSyncIdleCycleCounter.                      */
/* Preconditions | Usable after full-initialize Dem.                        */
/* Parameters    | none                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ExpireNvMSyncIdleTaskTime
( void )
{
    VAR( Std_ReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InitProcessType, AUTOMATIC ) initStatus;

    retVal = E_NOT_OK;
    initStatus = Dem_InitStatus;

    if( initStatus == DEM_MAIN_STS_INIT_COMPLETE )
    {
        Dem_NvMSyncIdleCycleCounter = Dem_MainSyncNvmDivideIdleCycleCount;
        retVal = E_OK;
    }

    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )            */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_InitFunction                                         */
/* Description   | Initializes Dem.                                         */
/* Preconditions | None.                                                    */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_InitProcess
( void )
{
    VAR( Dem_u08_InitProcessType, AUTOMATIC ) initStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retFunc;

    VAR( boolean, AUTOMATIC ) exitInitLoop;
    VAR( boolean, AUTOMATIC ) checkReadNvM;
    VAR( boolean, AUTOMATIC ) checkExecDataVerify;

    /*  set status      */
    initStatus  =   Dem_InitStatus;
    exitInitLoop  =   (boolean)FALSE;

    /*  exit InitProcess loop : PENDING or initialize complete.       */
    while( exitInitLoop == (boolean)FALSE )
    {
        switch( initStatus )
        {
            case DEM_MAIN_STS_INIT_CHECK_READNVM:       /*  Check Read NvM              */
                /*  check execute ReadAll.              */
                checkReadNvM    =   Dem_MM_CheckExecReadAll();
                if ( checkReadNvM == (boolean)TRUE )
                {
                    /*  read all executed.      */
                    /*  wait NvM read completer and check NvM read status.              */
                    initStatus  =   DEM_MAIN_STS_INIT_READ_NVM;
                }
                else
                {
                    /*  read all not execute.           */

                    /*  initialize data after NvBlockRead complete. */
                    Dem_RecMngCmn_AfterNvBlockReadComplete();

                    /*  next status : check DataVerify necessary.   */
                    initStatus  =   DEM_MAIN_STS_INIT_CHECK_DATAVERIFY;
                }
                break;

            case DEM_MAIN_STS_INIT_READ_NVM:            /*  Read NvM                    */
                retFunc         =   Dem_MM_InitProcess();
                if ( retFunc != DEM_IRT_PENDING )
                {
                    /*  initialize data after NvBlockRead complete. */
                    Dem_RecMngCmn_AfterNvBlockReadComplete();

                    /*  next status : start DataVerify.     */
                    initStatus  =   DEM_MAIN_STS_INIT_START_DATAVERIFY;
                }
                else
                {
                    /*  continue job to next cycle. exit loop.    */
                    exitInitLoop = (boolean)TRUE;
                }
                break;

            case DEM_MAIN_STS_INIT_CHECK_DATAVERIFY:    /*  Start Verify Record.        */
                checkExecDataVerify =   Dem_CheckDataVerifyNecessary();
                if ( checkExecDataVerify == (boolean)TRUE )
                {
                    /*  next status : start DataVerify.     */
                    initStatus  =   DEM_MAIN_STS_INIT_START_DATAVERIFY;
                }
                else
                {
                    /*  skip DataVerify.       */
                    /*  next status : control initialize process.                       */
                    initStatus  =   DEM_MAIN_STS_INIT_CONTROL_INIT_PROCESS;
                }
                break;

            case DEM_MAIN_STS_INIT_START_DATAVERIFY:    /*  Start Verify Record.        */

                Dem_RecMngCmn_InitSavedZone();

                Dem_RecMngCmn_InitDataVerify();
                initStatus  =   DEM_MAIN_STS_INIT_DATAVERIFY;
                break;

            case DEM_MAIN_STS_INIT_DATAVERIFY:          /*  Verify Record.              */
                retFunc         =   Dem_RecMngCmn_DataVerify();
                if ( retFunc != DEM_IRT_PENDING )
                {
                    /*  next status : control initialize process.                       */
                    initStatus  =   DEM_MAIN_STS_INIT_CONTROL_INIT_PROCESS;
                }
                else
                {
                    /*  continue job to next cycle. exit loop.    */
                    exitInitLoop = (boolean)TRUE;
                }
                break;

            case DEM_MAIN_STS_INIT_CONTROL_INIT_PROCESS:    /*  Init Process after record checked.      */
                retFunc         =   Dem_Control_InitProcess();
                if ( retFunc != DEM_IRT_PENDING )
                {
                    /*  next status : complete. */
                    initStatus  =   DEM_MAIN_STS_INIT_COMPLETE;
                }
                else
                {
                    /*  continue job to next cycle. exit loop.    */
                    exitInitLoop = (boolean)TRUE;
                }
                break;

            case DEM_MAIN_STS_INIT_COMPLETE:                /*  Init process complete.      */
                /* Init complete Dem_ModeMng */
                Dem_ModeMng_InitComplete();
                exitInitLoop  =   (boolean)TRUE;      /*  init process loop complete.     */
                break;

            default:
                exitInitLoop  =   (boolean)TRUE;      /*  init process loop complete.     */
                break;
        }
    }

    /*  update status       */
    Dem_InitStatus  =   initStatus;

    return ;
}
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )  */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_InitFunction                                         */
/* Description   | Initializes Dem.                                         */
/* Preconditions | None.                                                    */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_InitProcess
( void )
{
    VAR( Dem_u08_InitProcessType, AUTOMATIC ) initStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retFunc;

    VAR( boolean, AUTOMATIC ) exitInitLoop;
    VAR( boolean, AUTOMATIC ) checkExecDataVerify;

    /*  set status      */
    initStatus  =   Dem_InitStatus;
    exitInitLoop  =   (boolean)FALSE;

    /*  exit InitProcess loop : PENDING or initialize complete.       */
    while( exitInitLoop == (boolean)FALSE )
    {
        switch( initStatus )
        {
            case DEM_MAIN_STS_INIT_CHECK_READNVM:       /*  Check Read NvM              */
                /*  no read all.                                */

                /*  initialize data after NvBlockRead complete. */
                Dem_RecMngCmn_AfterNvBlockReadComplete();

                /*  check DataVerify necessary.   */
                checkExecDataVerify =   Dem_CheckDataVerifyNecessary();
                if ( checkExecDataVerify == (boolean)TRUE )
                {
                    /*  next status : start DataVerify.     */
                    initStatus  =   DEM_MAIN_STS_INIT_START_DATAVERIFY;
                }
                else
                {
                    /*  skip DataVerify.       */
                    /*  next status : control initialize process.                       */
                    initStatus  =   DEM_MAIN_STS_INIT_CONTROL_INIT_PROCESS;
                }
                break;

            case DEM_MAIN_STS_INIT_START_DATAVERIFY:    /*  Start Verify Record.        */

                Dem_RecMngCmn_InitSavedZone();

                Dem_RecMngCmn_InitDataVerify();
                initStatus  =   DEM_MAIN_STS_INIT_DATAVERIFY;
                break;

            case DEM_MAIN_STS_INIT_DATAVERIFY:          /*  Verify Record.              */
                retFunc         =   Dem_RecMngCmn_DataVerify();
                if ( retFunc != DEM_IRT_PENDING )
                {
                    /*  next status : control initialize process.                       */
                    initStatus  =   DEM_MAIN_STS_INIT_CONTROL_INIT_PROCESS;
                }
                else
                {
                    /*  continue job to next cycle. exit loop.    */
                    exitInitLoop = (boolean)TRUE;
                }
                break;

            case DEM_MAIN_STS_INIT_CONTROL_INIT_PROCESS:    /*  Init Process after record checked.      */
                retFunc         =   Dem_Control_InitProcess();
                if ( retFunc != DEM_IRT_PENDING )
                {
                    /*  next status : complete. */
                    initStatus  =   DEM_MAIN_STS_INIT_COMPLETE;
                }
                else
                {
                    /*  continue job to next cycle. exit loop.    */
                    exitInitLoop = (boolean)TRUE;
                }
                break;

            case DEM_MAIN_STS_INIT_COMPLETE:                /*  Init process complete.      */
                /* Init complete Dem_ModeMng */
                Dem_ModeMng_InitComplete();
                exitInitLoop  =   (boolean)TRUE;      /*  init process loop complete.     */
                break;

            default:
                exitInitLoop  =   (boolean)TRUE;      /*  init process loop complete.     */
                break;
        }
    }

    /*  update status       */
    Dem_InitStatus  =   initStatus;

    return ;
}
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_OFF ) */

/****************************************************************************/
/* Function Name | Dem_RefreshRAM                                           */
/* Description   | Refresh RAM                                              */
/* Preconditions | None.                                                    */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_RefreshRAM
( void )
{
    /*  call RAM refresh function.      */
    Dem_Main_RefreshRAM();
    Dem_Control_RefreshRAM();

    Dem_DataMng_RefreshRAM();
    Dem_ModeMng_RefreshRAM();

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   /*  [FuncSw]    */
    Dem_MM_RefreshRAM();
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )          */

    Dem_ClrInfoMng_RefreshRAM();

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_UdmControl_SyncEventEntry_RefreshRAM();
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Main_RefreshRAM                                      */
/* Description   | Refresh RAM  - Main                                      */
/* Preconditions | None.                                                    */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Main_RefreshRAM
( void )
{
    VAR( volatile Dem_u08_InitProcessType, AUTOMATIC )                      u8_dummy;      /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u08_InitProcessType, AUTOMATIC, DEM_VAR_NO_INIT )   u8_dummyPtr;   /*  for GlobalVariable address       */

    /*  set GlobalVariable pointer  */
    u8_dummyPtr     = &Dem_InitStatus;

    /* Exclusion is not necessary   */
    u8_dummy        = *u8_dummyPtr; /*  read GlobalVariable data    */
    *u8_dummyPtr    = u8_dummy;     /*  rewrite GlobalVariable data */

    return ;
}

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
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
