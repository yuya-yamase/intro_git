/* Dem_Control_Clear_c(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_Clear/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_Md_ModeMng.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_Pm_OccrDTC.h"
#include "../../../inc/Dem_Udm_Control.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../usr/Dem_Clear_Callout.h"
#include "../../../usr/Dem_SavedZone_Callout.h"

#include "Dem_Control_cmn_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
typedef uint8        Dem_u08_CtlClearStatusType;     /*  ClearStatus type                       */

/* Clear state */
#define DEM_CTL_STS_CLEAR_NONE                       ((Dem_u08_CtlClearStatusType)0x00U)
#define DEM_CTL_STS_CLEAR_PREPARE_CLEAR              ((Dem_u08_CtlClearStatusType)0x11U)
#define DEM_CTL_STS_CLEAR_NV_CLEAR                   ((Dem_u08_CtlClearStatusType)0x33U)
#define DEM_CTL_STS_CLEAR_RAM_CLEAR                  ((Dem_u08_CtlClearStatusType)0x44U)
#define DEM_CTL_STS_CLEAR_RECALC_MONSTS              ((Dem_u08_CtlClearStatusType)0x55U)
#define DEM_CTL_STS_CLEAR_CHECK_COMPLETED            ((Dem_u08_CtlClearStatusType)0x66U)
#define DEM_CTL_STS_CLEAR_COMPLETE                   ((Dem_u08_CtlClearStatusType)0x77U)

/* Check result of the clear target */
typedef uint8        Dem_u08_CtlClearTargetType;     /*  ClearStatus type                       */

#define DEM_CTL_CLEAR_TARGET_NONE                    ((Dem_u08_CtlClearTargetType)0x00U)
#define DEM_CTL_CLEAR_TARGET_SAME                    ((Dem_u08_CtlClearTargetType)0x01U)
#define DEM_CTL_CLEAR_TARGET_OTHER                   ((Dem_u08_CtlClearTargetType)0x02U)
#define DEM_CTL_CLEAR_TARGET_CANCEL                  ((Dem_u08_CtlClearTargetType)0x03U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    Dem_u32_DTCGroupType                DTCGroup;
    Dem_DTCFormatType                   DTCFormat;
    Dem_DTCOriginType                   DTCOrigin;
    Dem_u08_RequestCallerType          Caller;
} Dem_CtlClearTargetType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_CtlClearTargetType, DEM_CODE ) Dem_Control_CheckClearTarget
(
    VAR( Dem_u08_RequestCallerType, AUTOMATIC ) Caller,
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ClearDTCTargetSame
( void );

static FUNC( void, DEM_CODE ) Dem_Control_ClearDTCTargetCancel
( void );

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ClearDTCFirstRequest
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

static FUNC( void, DEM_CODE ) Dem_Control_PrepareClear
( void );

static FUNC( void, DEM_CODE ) Dem_Control_CheckClearNvStatus
( void );

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckStatusOtherThanClear
( void );

static FUNC( void, DEM_CODE ) Dem_Control_ClearRAMData
( void );

static FUNC( void, DEM_CODE ) Dem_Control_ReCalcMonSts
( void );

static FUNC( void, DEM_CODE ) Dem_Control_ClearCheckCompleted
( void );

static FUNC( void, DEM_CODE ) Dem_Control_SetClearStatusComplete
(
    VAR( Dem_u08_ClearCompleteType, AUTOMATIC ) ClearResult
);

static FUNC( void, DEM_CODE ) Dem_Control_SetClearTarget
(
    VAR( Dem_u08_RequestCallerType, AUTOMATIC ) Caller,
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_CtlClearTargetType, DEM_VAR_NO_INIT )       Dem_CtlClearTargetInfo;
static VAR( Dem_u08_InternalReturnType, DEM_VAR_NO_INIT )   Dem_CtlClearResult;
static VAR( boolean, DEM_VAR_NO_INIT )                      Dem_CtlCancelClearRequest;

static VAR( volatile Dem_u08_CtlClearStatusType, DEM_VAR_NO_INIT )               Dem_CtlClearStatus;
static VAR( volatile boolean, DEM_VAR_NO_INIT )             Dem_CtlExecClearDTCFlag;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Unit External functions                                                  */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_CheckClearParameter                          */
/* Description   | Performs a parameter check and gives the result which w- */
/*               | ould also be returned by calling clear with same parame- */
/*               | ters.                                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        Defines the DTC in respective format, that shall  */
/*               |         be cleared from the event memory. Either a sing- */
/*               |        le DTC or a DTC group may be passed.              */
/*               | [in] DTCFormat :                                         */
/*               |        Defines the input-format of the provided DTC val- */
/*               |        ue.                                               */
/*               | [in] DTCOrigin :                                         */
/*               |        This parameter is used to select the source memo- */
/*               |        rythe DTCs shall be cleared from.                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : DTC successfully cleared             */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing (in t- */
/*               |        his format)                                       */
/*               |        DEM_IRT_WRONG_DTCORIGIN : Wrong DTC origin        */
/*               |        DEM_IRT_NG : DTC clear failed( condition error.)  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckClearParameter
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retVal = Dem_CfgInfo_CheckClearParameter( DTCGroup, DTCFormat, DTCOrigin );
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_ClearDTC                                     */
/* Description   | Clears the fault information by DTC (the actual process- */
/*               | ing is performed in the periodicity processing).         */
/* Preconditions | none                                                     */
/* Parameters    | [in] Caller :                                            */
/*               |        For detect caller instance.                       */
/*               | [in] DTCGroup :                                          */
/*               |        Defines the DTC in respective format, that shall  */
/*               |         becleared from the event memory. If the DTC fit- */
/*               |        s to aDTC group number, all DTCs of the group sh- */
/*               |        all becleared.                                    */
/*               | [in] DTCFormat :                                         */
/*               |        Defines the input-format of the provided DTC val- */
/*               |        ue                                                */
/*               | [in] DTCOrigin :                                         */
/*               |        If the Dem supports more than one event memoryth- */
/*               |        is parameter is used to select the source memory- */
/*               |        the DTCs shall be read from                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : DTC successfully cleared             */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing (in t- */
/*               |        his format)                                       */
/*               |        DEM_IRT_WRONG_DTCORIGIN : Wrong DTC origin        */
/*               |        DEM_IRT_NG : DTC clear failed( condition error.)  */
/*               |        DEM_IRT_PENDING : The DTC clearing is performed - */
/*               |        asynchronously and still pending. The caller can  */
/*               |         retry later.                                     */
/*               |        DEM_IRT_BUSY : DTC not cleared, as another clear- */
/*               |        ing process is in progress. The caller can retry  */
/*               |         later.                                           */
/*               |        DEM_IRT_MEMORY_ERROR : An error occurred during - */
/*               |        erasing a memory location                         */
/* Notes         | This function is in SW-C or DCM main process.            */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ClearDTC
(
    VAR( Dem_u08_RequestCallerType, AUTOMATIC ) Caller,
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_CtlClearTargetType, AUTOMATIC ) retCheckClearTarget;
    VAR( boolean, AUTOMATIC ) firstClear = (boolean)FALSE;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatusOtherThanClear;

    checkStatus = Dem_Control_ChkAfterInit();
    if( checkStatus == DEM_IRT_OK )
    {
        SchM_Enter_Dem_CheckClearDTCStatus();

        checkStatusOtherThanClear = Dem_Control_CheckStatusOtherThanClear();
        if( checkStatusOtherThanClear == DEM_IRT_OK )
        {
            /* When obtain processing does not start */
            /* Check clear target */
            retCheckClearTarget = Dem_Control_CheckClearTarget( Caller, DTCGroup, DTCFormat, DTCOrigin );
            switch( retCheckClearTarget )
            {
                case DEM_CTL_CLEAR_TARGET_NONE:
                    /* For not in clear processing excuation, when clear target is held */
                    Dem_Control_SetClearTarget( Caller, DTCGroup, DTCFormat, DTCOrigin );
                    firstClear = (boolean)TRUE;
                    break;
                case DEM_CTL_CLEAR_TARGET_SAME:
                    /* When the same clear request as in the clear processing is requested */
                    retVal = Dem_Control_ClearDTCTargetSame();
                    break;
                case DEM_CTL_CLEAR_TARGET_OTHER:
                    /* When the other clear processing is executing */
                    retVal = DEM_IRT_PENDING;
                    break;
                case DEM_CTL_CLEAR_TARGET_CANCEL:
                default:
                    /* When cancel is requested */
                    Dem_Control_ClearDTCTargetCancel();
                    retVal = DEM_IRT_OK;
                    break;
            }
        }
        else if( checkStatusOtherThanClear == DEM_IRT_PENDING )
        {
            /* When clear is waited by the condition except clear state */
            retVal = DEM_IRT_PENDING;
        }
        else
        {
            /* When clear cannot be executed under the condition except clear state */
            retVal = DEM_IRT_BUSY;
        }

        SchM_Exit_Dem_CheckClearDTCStatus();

        if( firstClear == (boolean)TRUE )
        {
            /* When it is the first clear request */
            /* For shortening the exclusive time of the above processing, divide this processing */
            retVal = Dem_Control_ClearDTCFirstRequest( DTCGroup, DTCFormat, DTCOrigin );
        }
        else
        {
            /* When it is not the first clear request */
            /* For the necessary processing was done by Check clear target in the above */
            /* No process */
        }
    }
    else
    {
        /* For processing execution in an incorrect initialization state */
        retVal = DEM_IRT_NG;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_CheckStatusOtherThanClear                    */
/* Description   | Checks ClearDTC execution other than state Clear state.  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : ClearDTC can be executed.            */
/*               |        DEM_IRT_NG : ClearDTC cannot be executed.         */
/*               |        DEM_IRT_PENDING :                                 */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckStatusOtherThanClear
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal = DEM_IRT_OK;
    VAR( Dem_u08_DTCRecordUpdateStatusType, AUTOMATIC ) dtcUpdateStatus;
    VAR( Dem_u08_DTCStoredDataStatusType, AUTOMATIC ) dtcStoredDataStatus;
    VAR( boolean, AUTOMATIC ) execAsyncProcess;

    /* Check DTC update status */
    dtcUpdateStatus = Dem_ControlIFCmn_GetDTCRecordUpdateStatus();
    if( dtcUpdateStatus == DEM_CTL_STS_DTC_UPDATE_DISABLE )
    {
        /* When update is disabled */
        /* For SID0x19-sub04 is executed, cannot execute clear processing */
        retVal = DEM_IRT_NG;
    }
    else
    {
        /* No process */
    }

    if( retVal == DEM_IRT_OK )
    {
        /* Check DTCStoredData acquisition processing state */
        dtcStoredDataStatus = Dem_Control_GetDTCStoredDataStatus();
        if( dtcStoredDataStatus == DEM_CTL_STS_DTC_STORED_DATA_START )
        {
            /* When acquisition processing starts */
            /* For SID0x19-sub05 is executed, cannot execute clear processing */
            retVal = DEM_IRT_NG;
        }
        else
        {
            /* No process */
        }
    }

    if( retVal == DEM_IRT_OK )
    {
        /* Check operation cycle bit initialization state of DTC status caused by starting operation cycle */
        execAsyncProcess = Dem_Control_CheckExecAsyncProcess();
        if( execAsyncProcess == (boolean)FALSE )
        {
            /* No process */
        }
        else
        {
            /* In processing */
            /* For doing operation cycle bit initialization of DTC status, cannot execute clear processing */
            retVal = DEM_IRT_PENDING;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_CheckClearTarget                             */
/* Description   | Checks clear target.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] Caller :                                            */
/*               |                                                          */
/*               | [in] DTCGroup :                                          */
/*               |                                                          */
/*               | [in] DTCFormat :                                         */
/*               |                                                          */
/*               | [in] DTCOrigin :                                         */
/*               |                                                          */
/* Return Value  | Dem_u08_CtlClearTargetType                               */
/*               |        DEM_CTL_CLEAR_TARGET_NONE : no clear data         */
/*               |        DEM_CTL_CLEAR_TARGET_SAME : Equals data for clea- */
/*               |        r                                                 */
/*               |        DEM_CTL_CLEAR_TARGET_OTHER : Not equals data for  */
/*               |         clear                                            */
/*               |        DEM_CTL_CLEAR_TARGET_CANCEL :                     */
/* Notes         | This Function is in CheckClearDTCStatus exclusive sec..  */
/****************************************************************************/
static FUNC( Dem_u08_CtlClearTargetType , DEM_CODE ) Dem_Control_CheckClearTarget
(
    VAR( Dem_u08_RequestCallerType, AUTOMATIC ) Caller,
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_CtlClearTargetType, AUTOMATIC ) retVal = DEM_CTL_CLEAR_TARGET_OTHER;
    VAR( boolean, AUTOMATIC )   execClearDTCFlag;

    execClearDTCFlag    =   Dem_CtlExecClearDTCFlag;
    if ( execClearDTCFlag == (boolean)TRUE )
    {
        /*  ClearDTC process is executing.          */
        if( Caller == Dem_CtlClearTargetInfo.Caller )
        {
            if( DTCGroup == Dem_CtlClearTargetInfo.DTCGroup )
            {
                if( DTCFormat == Dem_CtlClearTargetInfo.DTCFormat )
                {
                    if( DTCOrigin == Dem_CtlClearTargetInfo.DTCOrigin )
                    {
                        /* When holding clear target information matched with accepted argument */
                        retVal = DEM_CTL_CLEAR_TARGET_SAME;
                    }
                }
            }
            else if( DTCGroup == DEM_DTC_CANCEL_CLEAR_DTC )
            {
                /* Because Caller is the same, cancel request */
                retVal = DEM_CTL_CLEAR_TARGET_CANCEL;
            }
            else
            {
                /* No process */
            }
        }
    }
    else
    {
        /*  ClearDTC is not execute.                */
        if( DTCGroup == DEM_DTC_CANCEL_CLEAR_DTC )
        {
            /* Cancel request when clear target is not held */
            retVal = DEM_CTL_CLEAR_TARGET_CANCEL;
        }
        else
        {
            /* When clear target is not held */
            retVal = DEM_CTL_CLEAR_TARGET_NONE;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_SetClearTarget                               */
/* Description   | Sets clear target.                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] Caller :                                            */
/*               |                                                          */
/*               | [in] DTCGroup :                                          */
/*               |                                                          */
/*               | [in] DTCFormat :                                         */
/*               |                                                          */
/*               | [in] DTCOrigin :                                         */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | This Function is in CheckClearDTCStatus exclusive sec..  */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_SetClearTarget
(
    VAR( Dem_u08_RequestCallerType, AUTOMATIC ) Caller,
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{

    Dem_CtlClearTargetInfo.DTCGroup = DTCGroup;
    Dem_CtlClearTargetInfo.DTCFormat = DTCFormat;
    Dem_CtlClearTargetInfo.DTCOrigin = DTCOrigin;

    /* Setting of Caller must be done at last */
    Dem_CtlClearTargetInfo.Caller = Caller;

    Dem_CtlExecClearDTCFlag =   (boolean)TRUE;
    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_ClearDTCTargetSame                           */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |         DEM_IRT_PENDING:                                 */
/*               |         DEM_IRT_MEMORY_ERROR:                            */
/*               |         DEM_IRT_OK:                                      */
/* Notes         | This function is in DCM main process.                    */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ClearDTCTargetSame
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_CtlClearStatusType, AUTOMATIC ) clearStatus;

    retVal = DEM_IRT_PENDING;

    if( Dem_CtlCancelClearRequest == (boolean)TRUE )
    {
        /* When cancel request has been responded, clear the flag and cancel the cancel */
        Dem_CtlCancelClearRequest = (boolean)FALSE;
    }
    else
    {
        /* No process */
    }
    clearStatus =   Dem_CtlClearStatus;
    if( clearStatus == DEM_CTL_STS_CLEAR_COMPLETE )
    {
        /* When clear processing was not finished */
        /* Store clear result to return value */
        retVal = Dem_CtlClearResult;
        Dem_Control_Clear_ClearDTCInfo();
    }
    else
    {
        /* During clear processing */
        /* When canceling the cancel, status must be one except completion */
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_ClearDTCTargetCancel                         */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | This function is in DCM main process.                    */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_ClearDTCTargetCancel
( void )
{
    VAR( Dem_u08_CtlClearStatusType, AUTOMATIC ) clearStatus;

    clearStatus =   Dem_CtlClearStatus;
    switch( clearStatus )
    {
        case DEM_CTL_STS_CLEAR_PREPARE_CLEAR:
            /* The same processing as DEM_CTL_STS_CLEAR_CHECK_COMPLETED */
        case DEM_CTL_STS_CLEAR_NV_CLEAR:
            /* The same processing as DEM_CTL_STS_CLEAR_CHECK_COMPLETED */
        case DEM_CTL_STS_CLEAR_RAM_CLEAR:
            /* The same processing as DEM_CTL_STS_CLEAR_CHECK_COMPLETED */
        case DEM_CTL_STS_CLEAR_RECALC_MONSTS:
            /* The same processing as DEM_CTL_STS_CLEAR_CHECK_COMPLETED */
        case DEM_CTL_STS_CLEAR_CHECK_COMPLETED:
            /* Because clear processing is in execution, remain cancel request */
            Dem_CtlCancelClearRequest = (boolean)TRUE;
            break;

        case DEM_CTL_STS_CLEAR_COMPLETE:
            /* Because clear processing has been finished, initialize clear-related information */
            Dem_Control_Clear_ClearDTCInfo();
            break;

        default:    /*  DEM_CTL_STS_CLEAR_NONE  */
            /* Because clear processing is not executed, do nothing and end */
            break;
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_ClearDTCFirstRequest                         */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in]  DTCGroup:                                          */
/*               |                                                          */
/*               | [in]  DTCFormat:                                         */
/*               |                                                          */
/*               | [in]  DTCOrigin:                                         */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |         DEM_IRT_PENDING:                                 */
/*               |         DEM_IRT_WRONG_DTC:                               */
/*               |         DEM_IRT_WRONG_DTCORIGIN:                         */
/* Notes         | This function is in DCM main process.                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ClearDTCFirstRequest
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckClearParameter;

    /* For the first clear request, check the requested argument */
    retCheckClearParameter = Dem_CfgInfo_CheckClearParameter( DTCGroup, DTCFormat, DTCOrigin );
    if( retCheckClearParameter == DEM_IRT_OK )
    {
        /* Set clear state to event queue */
        Dem_AsyncReq_SetClearStatus();

        if( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
        {
            Dem_Control_StartClearDTC_PrimaryMemory();
        }
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
        else
        {
            Dem_UdmControl_StartClearDTC( DTCOrigin );
        }
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

        Dem_ModeMng_SetMode( DEM_MODE_PROCESSING_CLEAR_DTC );

        Dem_CtlClearStatus = DEM_CTL_STS_CLEAR_PREPARE_CLEAR;

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
        if ( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
        {
            Dem_MonSts_UpdateAllMonitorStatus();
        }
#endif  /*   ( DEM_TRIGGER_FIM_REPORTS == STD_ON )          */

        retVal = DEM_IRT_PENDING;
    }
    else
    {
        /* DEM_IRT_WRONG_DTC or DEM_IRT_WRONG_DTCORIGIN */
        /* When it is the first request, for the clear state is moved to clearing beforehand, return clear unprocessed state */
        SchM_Enter_Dem_CheckClearDTCStatus();           /*  enter exclusion : Prevent conflicts with Dem_Control_RefreshRAM(Dem_MainFunction)   */

        /*  Dem_CtlClearTargetInfo is set from other contexts, so exclusion should be monitored.    */
        Dem_Control_Clear_ClearDTCInfo();

        SchM_Exit_Dem_CheckClearDTCStatus();            /*  exit exclusion      */
        retVal = retCheckClearParameter;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetClearType                                 */
/* Description   | get DTCGroup and DTCOrigin.                              */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
/*               | [out] DTCGroupPtr :                                      */
/*               |        Address to Set DTCGroup                           */
/*               | [out] DTCOriginPtr :                                     */
/*               |        Address to Set DTCOrigin                          */
/* Return Value  | void                                                     */
/* Notes         | This function is in Dem_MainFunction process.            */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_GetClearType
(
    P2VAR( Dem_u32_DTCGroupType, AUTOMATIC, AUTOMATIC ) DTCGroupPtr,
    P2VAR( Dem_DTCOriginType, AUTOMATIC, AUTOMATIC ) DTCOriginPtr
)
{
    *DTCGroupPtr = Dem_CtlClearTargetInfo.DTCGroup;
    *DTCOriginPtr = Dem_CtlClearTargetInfo.DTCOrigin;

    return;
}


/*--------------------------------------------------------------------------*/
/* Unit Internal functions(process)                                         */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Function Name | Dem_Control_ClearDTCProcess                              */
/* Description   | Processes DTC clear event.                               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_ClearDTCProcess
( void )
{
    VAR( Dem_u08_CtlClearStatusType, AUTOMATIC ) clearStatus;

    clearStatus =   Dem_CtlClearStatus;
    switch( clearStatus )
    {
        case DEM_CTL_STS_CLEAR_NONE:
            /* No process */
            break;
        case DEM_CTL_STS_CLEAR_PREPARE_CLEAR:
            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - start.   */
            Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
            /*--------------------------------------*/

            Dem_Control_PrepareClear();

            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - end.     */
            Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
            /*--------------------------------------*/
            break;
        case DEM_CTL_STS_CLEAR_NV_CLEAR:
            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - start.   */
            Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
            /*--------------------------------------*/

            Dem_Control_CheckClearNvStatus();

            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - end.     */
            Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
            /*--------------------------------------*/

            break;
        case DEM_CTL_STS_CLEAR_RAM_CLEAR:
            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - start.   */
            Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
            /*--------------------------------------*/

            Dem_Control_ClearRAMData();

            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - end.     */
            Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
            /*--------------------------------------*/
            break;
        case DEM_CTL_STS_CLEAR_RECALC_MONSTS:
            Dem_Control_ReCalcMonSts();
            break;
        case DEM_CTL_STS_CLEAR_CHECK_COMPLETED:
            Dem_Control_ClearCheckCompleted();
            break;
        case DEM_CTL_STS_CLEAR_COMPLETE:
            /* No process */
            break;
        default:
            /* When it is undefined clear status */
            /* No process */
            break;
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_PrepareClear                                 */
/* Description   | Prepare clear.                                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | This function is in Dem_Mainfunction process.            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_PrepareClear
( void )
{
    VAR( Dem_u08_ClearDTCBehaviorType, AUTOMATIC ) clearDTCBehavior;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) skipMode;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;

    skipMode    =   (boolean)FALSE;
    if ( Dem_CtlClearTargetInfo.DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY )
    {
        memType =   Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin( Dem_CtlClearTargetInfo.DTCOrigin, &udmInfoTableIndex ); /* [GUD:RET:Not DEM_MEMORYTYPE_INVALID] udmInfoTableIndex */
        if ( memType == DEM_MEMORYTYPE_EXTERNAL )
        {
            /*  mirror memory.  :   skip clear phase.               */
            skipMode    =   (boolean)TRUE;
        }
    }

    if ( skipMode ==  (boolean)TRUE )
    {
        /*  mirror memory.  :   skip clear phase.               */
        Dem_CtlClearStatus = DEM_CTL_STS_CLEAR_CHECK_COMPLETED;
        /* If without clear processing of application side, clear is as completion in the below function */
        Dem_Control_ClearCheckCompleted();
    }
    else
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */
    {
        if ( Dem_CtlClearTargetInfo.DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
        {
            Dem_Control_PrepareClear_PrimaryMemory();
        }


        clearDTCBehavior    =   Dem_ClearDTCBehavior;

        if ( clearDTCBehavior == DEM_CLRRESP_NONVOLATILE_FINISH )
        {
            /*------------------------------*/
            /*  NonVolatile Finish.         */
            /*------------------------------*/
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   /*  [FuncSw]    */
            /*  Update : ClearRecord        */
            Dem_ClrInfoMng_StartClearDTC( Dem_CtlClearTargetInfo.DTCGroup, Dem_CtlClearTargetInfo.DTCOrigin );
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )            */

            /*  wait complete of write ClearRecord NvM.     */
            Dem_CtlClearStatus = DEM_CTL_STS_CLEAR_NV_CLEAR;
        }
        else
        {
            /*------------------------------*/
            /*  Volatile.                   */
            /*------------------------------*/
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   /*  [FuncSw]    */
            /*  Write ClearRecord request.      */
            Dem_ClrInfoMng_StartClearDTC( Dem_CtlClearTargetInfo.DTCGroup, Dem_CtlClearTargetInfo.DTCOrigin );
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )            */

            /* ClearID Update */
            Dem_ClrInfoMng_UpdateClearID( Dem_CtlClearTargetInfo.DTCGroup, Dem_CtlClearTargetInfo.DTCOrigin );

            /* Nonvolatile clear is completed */
            Dem_CtlClearStatus = DEM_CTL_STS_CLEAR_RAM_CLEAR;

            /*  RAM Clear first     */
            Dem_Control_ClearRAMData();
        }
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_CheckClearNvStatus                           */
/* Description   | Checks clear Nv status.                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_CheckClearNvStatus
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;

    /* Obtain nonvolatile clear status */
    retTempVal = Dem_ClrInfoMng_GetNvClearResult();
    if( retTempVal == DEM_IRT_PENDING )
    {
        /* During nonvolatile clear processing */
        /* No process */
    }
    else if( retTempVal == DEM_IRT_OK )
    {
        /* ClearID Update */
        Dem_ClrInfoMng_UpdateClearID( Dem_CtlClearTargetInfo.DTCGroup, Dem_CtlClearTargetInfo.DTCOrigin );
        /* Nonvolatile clear is completed */
        Dem_CtlClearStatus = DEM_CTL_STS_CLEAR_RAM_CLEAR;

        /*  RAM Clear first     */
        Dem_Control_ClearRAMData();
    }
    else
    {
        /* Nonvolatile clear is failure */
        Dem_Control_SetClearStatusComplete( DEM_CLEARCOMPLETE_NVMERROR );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Control_ClearRAMData                                 */
/* Description   | Clears RAM data.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_ClearRAMData
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    if ( Dem_CtlClearTargetInfo.DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY )
    {
        retVal =    Dem_UdmControl_ClearRAM();
        if( retVal != DEM_IRT_PENDING )
        {
            /* All clear of event queue */
            Dem_AsyncReq_SetClearEvent( Dem_CtlClearTargetInfo.DTCGroup, Dem_CtlClearTargetInfo.DTCOrigin );

            Dem_CtlClearStatus = DEM_CTL_STS_CLEAR_CHECK_COMPLETED;
            /* If without clear processing of application side, clear is as completion in the below function */
            Dem_Control_ClearCheckCompleted();
        }
    }
    else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
    {
        retVal  =   Dem_Control_ClearRAM_PrimaryMemory( Dem_CtlClearTargetInfo.DTCGroup );
        if( retVal != DEM_IRT_PENDING )
        {
            /* All clear of event queue */
            Dem_AsyncReq_SetClearEvent( Dem_CtlClearTargetInfo.DTCGroup, Dem_CtlClearTargetInfo.DTCOrigin );

            Dem_CtlClearStatus = DEM_CTL_STS_CLEAR_RECALC_MONSTS;

            Dem_MonSts_ReCalcStart( (boolean)TRUE );
            Dem_Control_ReCalcMonSts();
        }
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_ReCalcMonSts                                 */
/* Description   | recalculation of MonSts.                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | This function is in Dem_MainFunction process.            */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_ReCalcMonSts
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retValFim;

    retValFim = Dem_MonSts_ReCalcProc( DEM_MONSTS_RECALC_TYPE_DTC_CLEAR );
    if( retValFim != DEM_IRT_PENDING )
    {
        Dem_CtlClearStatus = DEM_CTL_STS_CLEAR_CHECK_COMPLETED;
        /* If without clear processing of application side, clear is as completion in the below function */
        Dem_Control_ClearCheckCompleted();
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Control_ClearCheckCompleted                          */
/* Description   | Check clear status of application.                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | This function is in Dem_MainFunction process.            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_ClearCheckCompleted
( void )
{
    VAR( Dem_ClearDTCCallerType, AUTOMATIC ) calloutCaller;
    VAR( Dem_CalloutReturnType, AUTOMATIC ) retClearComp;

    if( Dem_CtlClearTargetInfo.Caller == DEM_CALLER_DCM )
    {
        calloutCaller = DEM_CALLER_TYPE_DCM;
    }
    else
    {
        /* Currently just use DCM or CDD value, so if it is not DCM */
        calloutCaller = DEM_CALLER_TYPE_SWC;
    }

    retClearComp = Dem_CheckClearCompleted( calloutCaller, Dem_CtlClearTargetInfo.DTCGroup, Dem_CtlClearTargetInfo.DTCFormat, Dem_CtlClearTargetInfo.DTCOrigin );
    if( retClearComp == DEM_CALLOUT_PENDING )
    {
        /* During clear of applicaiton side */
        /* No process */
    }
    else if( retClearComp == DEM_CALLOUT_OK )
    {
        /* Clear of applicaiton side is finished or no clear processing of application side */
        Dem_Control_SetClearStatusComplete( DEM_CLEARCOMPLETE_OK );
    }
    else
    {
        /* Clear of applicaiton side is failure */
        /* By returning memory error, tool side returns NRC0x72 */
        Dem_Control_SetClearStatusComplete( DEM_CLEARCOMPLETE_SWCERROR );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetClearStatusComplete                       */
/* Description   | Sets clear status complete.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] ClearResult :                                       */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | This function is in Dem_MainFunction process.            */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_SetClearStatusComplete
(
    VAR( Dem_u08_ClearCompleteType, AUTOMATIC ) ClearResult
)
{
    SchM_Enter_Dem_CheckClearDTCStatus();

    if( Dem_CtlCancelClearRequest == (boolean)TRUE )
    {
        Dem_Control_Clear_ClearDTCInfo();
    }
    else
    {
        if ( ClearResult == DEM_CLEARCOMPLETE_OK )
        {
            Dem_CtlClearResult  =   DEM_IRT_OK;
        }
        else
        {
            Dem_CtlClearResult  =   DEM_IRT_MEMORY_ERROR;
        }
        Dem_CtlClearStatus = DEM_CTL_STS_CLEAR_COMPLETE;
    }

    SchM_Exit_Dem_CheckClearDTCStatus();

    if ( Dem_CtlClearTargetInfo.DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
    {
        Dem_Control_EndClearDTC_PrimaryMemory( Dem_CtlClearTargetInfo.DTCGroup, ClearResult );
    }
    else
    {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
        /*  UserDefinedMemory clear.        */
        Dem_UdmControl_EndClearDTC( Dem_CtlClearTargetInfo.DTCOrigin );
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */
    }

    Dem_ModeMng_ClearMode( DEM_MODE_PROCESSING_CLEAR_DTC );

    return;
}

/*--------------------------------------------------------------------------*/
/* Unit Internal functions(data)                                            */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_Clear_ClearDTCInfo                           */
/* Description   | Initializes clear info.                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | This Function is in CheckClearDTCStatus exclusive sec..  */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_Clear_ClearDTCInfo
( void )
{
    Dem_CtlClearResult = DEM_IRT_NG;
    Dem_CtlClearStatus = DEM_CTL_STS_CLEAR_NONE;
    Dem_CtlCancelClearRequest = (boolean)FALSE;

    Dem_CtlClearTargetInfo.DTCGroup = (Dem_u32_DTCGroupType)0U;
    Dem_CtlClearTargetInfo.DTCFormat = DEM_DTC_FORMAT_UDS;
    Dem_CtlClearTargetInfo.DTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
    Dem_CtlClearTargetInfo.Caller = DEM_CALLER_NONE;
    Dem_CtlExecClearDTCFlag = (boolean)FALSE;

    Dem_Control_StartClearDTC_PrimaryMemory();

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_UdmControl_Clear_ClearDTCInfo();
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_CheckExecClearDTCProcess                     */
/* Description   | Check execute clearDTC process.                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  :   Active ClearDTC process.                */
/*               |        FALSE :   Not Active ClearDTC process.            */
/* Notes         | This function is in SW-C  main process.                  */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Control_CheckExecClearDTCProcess
( void )
{
    return Dem_CtlExecClearDTCFlag;
}


/****************************************************************************/
/* Function Name | Dem_Control_Clear_RefreshRAM                             */
/* Description   | Refresh RAM  - Control                                   */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_Clear_RefreshRAM
( void )
{
    VAR( volatile boolean, AUTOMATIC )                      b_dummyExec;      /*  for store GlobalVariable data    */
    P2VAR( volatile boolean, AUTOMATIC, DEM_VAR_NO_INIT )   b_dummyExecPtr;   /*  for GlobalVariable address       */

    VAR( volatile Dem_u08_CtlClearStatusType, AUTOMATIC )                      u8_dummyStatus;      /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u08_CtlClearStatusType, AUTOMATIC, DEM_VAR_NO_INIT )   u8_dummyStatusPtr;   /*  for GlobalVariable address       */

    /* Exclusion is necessary       */
    SchM_Enter_Dem_CheckClearDTCStatus();                   /*  enter exclusion     */
        b_dummyExecPtr     = &Dem_CtlExecClearDTCFlag;         /*  set GlobalVariable pointer  */
        b_dummyExec        = *b_dummyExecPtr;                 /*  read GlobalVariable data    */
        *b_dummyExecPtr    = b_dummyExec;                         /*  rewrite GlobalVariable data */

        u8_dummyStatusPtr   = &Dem_CtlClearStatus;
        u8_dummyStatus      = *u8_dummyStatusPtr;               /*  read GlobalVariable data    */
        *u8_dummyStatusPtr  = u8_dummyStatus;                         /*  rewrite GlobalVariable data */

    SchM_Exit_Dem_CheckClearDTCStatus();                    /*  exit exclusion      */
    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
