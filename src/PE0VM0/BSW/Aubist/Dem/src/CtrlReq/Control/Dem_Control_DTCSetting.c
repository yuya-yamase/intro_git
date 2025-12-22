/* Dem_Control_DTCSetting_c(v5-8-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_DTCSetting/CODE                               */
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
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_Control.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_Control_NotifyDisabledProcess
( void );

static FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Control_NotifyDisabled
( void );

static FUNC( void, DEM_CODE ) Dem_Control_NotifyReenabledProcess
( void );

static FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Control_NotifyReenabled
( void );

static FUNC( void, DEM_CODE ) Dem_Control_SetDTCSettingStatus
(
    VAR( Dem_u08_DTCSettingStatusType, AUTOMATIC ) DTCSettingStatus
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextEventPosByDTCsForDTCSetting
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) BaseEventPos,
    P2VAR( Dem_u16_EventPosType, AUTOMATIC, AUTOMATIC ) NextEventPosPtr
);


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( volatile Dem_u08_DTCSettingStatusType, DEM_VAR_NO_INIT )               Dem_CtlDTCSettingStatus;
static VAR( Dem_u16_EventPosType, DEM_VAR_NO_INIT )                       Dem_CtlDisableDTCSettingEventPos;
static VAR( Dem_u16_EventPosType, DEM_VAR_NO_INIT )                       Dem_CtlEnableDTCSettingEventPos;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST          /*  PreInit section                     */
#include <Dem_MemMap.h>
/****************************************************************************/
/* Function Name | Dem_Control_PreInitDTCSettingStatus                      */
/* Description   | PreInitialize DTC setting status.(RAM init for read.)    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_TRUST ) Dem_Control_PreInitDTCSettingStatus     /*  PreInit section                     */
( void )
{
    Dem_CtlDTCSettingStatus = DEM_CTL_STS_DTC_SETTING_ENABLE;
    return ;
}

#define DEM_STOP_SEC_CODE_TRUST           /*  PreInit section                     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Control_InitDTCSettingStatus                         */
/* Description   | Initialize DTC setting status.(functional init)          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_InitDTCSettingStatus
( void )
{
    /*  initialize DTC setting.     */
    /*  this is functional initializing. (for term of shutdown->init, always DTCSetting starts enable.) */
    Dem_CtlDTCSettingStatus = DEM_CTL_STS_DTC_SETTING_ENABLE;
    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_DisableDTCSetting                            */
/* Description   | Disables the DTC setting for a DTC group.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        Defineds thed group of DTC that shall be disable- */
/*               |        d to store in event memory.                       */
/*               | [in] DTCKind :                                           */
/*               |        This parameter defineds the requested DTC kind, - */
/*               |        either only OBD-relevant DTCs or all DTCs         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : DTC setting control successful       */
/*               |        DEM_IRT_NG : DTC setting control not successful   */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : DTC setting control  */
/*               |         not successful becouse group of DTC was wrong    */
/* Notes         | This function is in SW-C or DCM main process.            */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_DisableDTCSetting
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSettingParameterVal;
    VAR( Dem_u08_DTCSettingStatusType, AUTOMATIC ) settingStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retNotifyVal;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retSettingParameterVal = Dem_CfgInfo_CheckDTCSettingParameter( DTCGroup, DTCKind );
        if( retSettingParameterVal == DEM_IRT_OK )
        {

            settingStatus = Dem_Control_GetDTCSettingStatus();
            switch( settingStatus )
            {
                case DEM_CTL_STS_DTC_SETTING_ENABLE:
                    Dem_CtlDisableDTCSettingEventPos = DEM_EVENTPOS_INVALID;
                    SchM_Enter_Dem_CheckControlDTCSetting();    /*  enter exclusion : Prevent conflicts with Dem_Control_RefreshRAM(Dem_MainFunction)   */
                    Dem_Control_SetDTCSettingStatus( DEM_CTL_STS_DTC_SETTING_DISABLE );
                    SchM_Exit_Dem_CheckControlDTCSetting();     /*  exit exclusion      */
                    retNotifyVal = Dem_Control_NotifyDisabled();
                    if( retNotifyVal == DEM_IRT_PENDING )
                    {
                        SchM_Enter_Dem_CheckControlDTCSetting();    /*  enter exclusion : Prevent conflicts with Dem_Control_RefreshRAM(Dem_MainFunction)   */
                        Dem_Control_SetDTCSettingStatus( DEM_CTL_STS_DTC_SETTING_TO_DISABLE );
                        SchM_Exit_Dem_CheckControlDTCSetting();     /*  exit exclusion      */
                    }
                    else
                    {
                        /* If notification processing result is not PENDING (both successful/failure), set state as DISABLE */
                        /* But not update here because the sate has been DISABLE */
                        /* No process */
                    }
                    retVal = DEM_IRT_OK;
                    break;
                case DEM_CTL_STS_DTC_SETTING_TO_DISABLE:
                    /* The same processing as DEM_CTL_STS_DTC_SETTING_DISABLE */
                case DEM_CTL_STS_DTC_SETTING_DISABLE:
                    retVal = DEM_IRT_OK;
                    break;
                case DEM_CTL_STS_DTC_SETTING_TO_ENABLE:
                    /* No process */
                    break;
                default:
                    /* No process */
                    break;
            }
        }
        else
        {
            retVal = retSettingParameterVal;
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_EnableDTCSetting                             */
/* Description   | Enables the DTC setting for a DTC group.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        Defineds thed group of DTC that shall be disable- */
/*               |        d to store in event memory.                       */
/*               | [in] DTCKind :                                           */
/*               |        This parameter defineds the requested DTC kind, - */
/*               |        either only OBD-relevant DTCs or all DTCs         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : DTC setting control successful       */
/*               |        DEM_IRT_NG : DTC setting control not successful   */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : DTC setting control  */
/*               |         not successful becouse group of DTC was wrong    */
/* Notes         | This function is in SW-C or DCM main process.            */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_EnableDTCSetting
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSettingParameterVal;
    VAR( Dem_u08_DTCSettingStatusType, AUTOMATIC ) settingStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retNotifyVal;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retSettingParameterVal = Dem_CfgInfo_CheckDTCSettingParameter( DTCGroup, DTCKind );
        if (retSettingParameterVal == DEM_IRT_OK)
        {
            settingStatus = Dem_Control_GetDTCSettingStatus();
            switch( settingStatus )
            {
                case DEM_CTL_STS_DTC_SETTING_DISABLE:
                    /* The same processing as DEM_CTL_STS_DTC_SETTING_TO_DISABLE */
                case DEM_CTL_STS_DTC_SETTING_TO_DISABLE:
                    Dem_CtlEnableDTCSettingEventPos = DEM_EVENTPOS_INVALID;
                    retNotifyVal = Dem_Control_NotifyReenabled();
                    SchM_Enter_Dem_CheckControlDTCSetting();
                    if( retNotifyVal == DEM_IRT_PENDING )
                    {
                        Dem_Control_SetDTCSettingStatus( DEM_CTL_STS_DTC_SETTING_TO_ENABLE );
                    }
                    else
                    {
                        /* If notification processing result is not PENDING (both successful/failure), set state as ENABLE */
                        Dem_Control_SetDTCSettingStatus( DEM_CTL_STS_DTC_SETTING_ENABLE );
                    }
                    SchM_Exit_Dem_CheckControlDTCSetting();
                    retVal = DEM_IRT_OK;
                    break;
                case DEM_CTL_STS_DTC_SETTING_ENABLE:
                    /* The same processing as DEM_CTL_STS_DTC_SETTING_TO_ENABLE */
                case DEM_CTL_STS_DTC_SETTING_TO_ENABLE:
                    retVal = DEM_IRT_OK;
                    break;
                default:
                    /* No process */
                    break;
            }

        }
        else
        {
            retVal = retSettingParameterVal;
        }
    }
    else
    {
        /* No process */
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetDTCSettingStatusForIF                     */
/* Description   | Get the DTC setting status.                              */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCSettingStatusPtr :                              */
/*               |        DTC setting status.                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetDTCSettingStatusForIF
(
    P2VAR( Dem_DTCSettingStatusType, AUTOMATIC, AUTOMATIC ) DTCSettingStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_DTCSettingStatusType, AUTOMATIC ) settingStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterInit();
    if( checkStatus == DEM_IRT_OK )
    {
        SchM_Enter_Dem_CheckControlDTCSetting();
        settingStatus = Dem_Control_GetDTCSettingStatus();
        SchM_Exit_Dem_CheckControlDTCSetting();

        if( settingStatus == DEM_CTL_STS_DTC_SETTING_ENABLE )
        {
            /*  DTC setting status is enable    */
            *DTCSettingStatusPtr = DEM_DTCSETTING_STATUS_ENABLE;
        }
        else
        {
            /*  DTC setting status is disable   */
            *DTCSettingStatusPtr = DEM_DTCSETTING_STATUS_DISABLE;
        }
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/*--------------------------------------------------------------------------*/
/* Unit Internal functions(process)                                         */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_DTCSettingProcess                            */
/* Description   | Processes DTC setting.                                   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | This function is in Dem_MainFunction process.            */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_DTCSettingProcess
( void )
{
    VAR( Dem_u08_DTCSettingStatusType, AUTOMATIC ) settingStatus;

    settingStatus = Dem_Control_GetDTCSettingStatus();
    switch( settingStatus )
    {
        case DEM_CTL_STS_DTC_SETTING_TO_DISABLE:
            Dem_Control_NotifyDisabledProcess();
            break;
        case DEM_CTL_STS_DTC_SETTING_TO_ENABLE:
            Dem_Control_NotifyReenabledProcess();
            break;
        case DEM_CTL_STS_DTC_SETTING_DISABLE:
            /* The same processing as DEM_CTL_STS_DTC_SETTING_ENABLE */
        case DEM_CTL_STS_DTC_SETTING_ENABLE:
            /* No process */
            break;
        default:
            /* No process */
            break;
    }
}


/****************************************************************************/
/* Function Name | Dem_Control_NotifyDisabledProcess                        */
/* Description   | Processes notify disabled.                               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | This function is in Dem_MainFunction process.            */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_NotifyDisabledProcess
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_DTCSettingStatusType, AUTOMATIC ) settingStatus;

    retVal = Dem_Control_NotifyDisabled();
    if( retVal != DEM_IRT_PENDING )
    {
        /* If notification processing result is not PENDING (both successful/failure), set state as DISABLE */
        /* But not set to DISABLE if the state is changed by receiving Enable request during notification processing */
        SchM_Enter_Dem_CheckControlDTCSetting();
        settingStatus = Dem_Control_GetDTCSettingStatus();
        if( settingStatus == DEM_CTL_STS_DTC_SETTING_TO_DISABLE )
        {
            Dem_Control_SetDTCSettingStatus( DEM_CTL_STS_DTC_SETTING_DISABLE );
        }
        else
        {
            /* No process */
        }
        SchM_Exit_Dem_CheckControlDTCSetting();
    }
    else
    {
        /* No process */
    }
}


/****************************************************************************/
/* Function Name | Dem_Control_NotifyDisabled                               */
/* Description   | Notifies disabled.                                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Notify disabled is completed.        */
/*               |        DEM_IRT_PENDING : Notify disabled is not over.    */
/*               |        DEM_IRT_NG : Notify disabled is failed.           */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_NotifyDisabled
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;
    VAR( Dem_u16_AdjustCntByEventNumType, AUTOMATIC ) loopCount;
    VAR( Dem_u16_EventPosType, AUTOMATIC ) nextEventPos;
    VAR( Dem_u16_AdjustCntByEventNumType, AUTOMATIC ) notifyControlDTCSettingAtOnce;

    retVal = DEM_IRT_NG;
    retTempVal = DEM_IRT_NG;
    resultOfCallback = E_NOT_OK;
    nextEventPos = DEM_EVENTPOS_INVALID;
    notifyControlDTCSettingAtOnce = Dem_CtlNotifyControlDTCSettingAtOnce;

    for( loopCount = (Dem_u16_AdjustCntByEventNumType)0U; loopCount < notifyControlDTCSettingAtOnce; loopCount++ )
    {
        retTempVal = Dem_Control_GetNextEventPosByDTCsForDTCSetting( Dem_CtlDisableDTCSettingEventPos, &nextEventPos );
        if( retTempVal == DEM_IRT_OK )
        {
            Dem_CfgInfoPm_TriggerInitMForEFnc( nextEventPos, DEM_INIT_MONITOR_DISABLED, &resultOfCallback );

            Dem_CtlDisableDTCSettingEventPos = nextEventPos;
        }
        else
        {
            break;
        }
    }

    switch( retTempVal )
    {
        case DEM_IRT_OK:
            retVal = DEM_IRT_PENDING;
            break;
        case DEM_IRT_NO_MATCHING_ELEMENT:
            retVal = DEM_IRT_OK;
            break;
        default:
            /* No process */
            break;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_NotifyReenabledProcess                       */
/* Description   | Processes notify reenabled.                              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | This function is in Dem_MainFunction process.            */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_NotifyReenabledProcess
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_Control_NotifyReenabled();
    if( retVal != DEM_IRT_PENDING )
    {
        /* If notification processing result is not PENDING (both successful/failure), set state as ENABLE */
        Dem_Control_SetDTCSettingStatus( DEM_CTL_STS_DTC_SETTING_ENABLE );
    }
    else
    {
        /* No Process */
    }
}


/****************************************************************************/
/* Function Name | Dem_Control_NotifyReenabled                              */
/* Description   | Notifies reenabled.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] retVal :                                            */
/*               | [in] retTempVal :                                        */
/*               | [in] resultOfCallback :                                  */
/*               | [in] loopCount :                                         */
/*               | [in] nextEventPos :                                      */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Notify reenabled is completed.       */
/*               |        DEM_IRT_PENDING : Notify reenabled is not over.   */
/*               |        DEM_IRT_NG : Notify reenabled is failed.          */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Control_NotifyReenabled
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;
    VAR( Dem_u16_AdjustCntByEventNumType, AUTOMATIC ) loopCount;
    VAR( Dem_u16_EventPosType, AUTOMATIC ) nextEventPos;
    VAR( Dem_u16_AdjustCntByEventNumType, AUTOMATIC ) notifyControlDTCSettingAtOnce;

    retVal = DEM_IRT_NG;
    retTempVal = DEM_IRT_NG;
    resultOfCallback = E_NOT_OK;
    nextEventPos = DEM_EVENTPOS_INVALID;
    notifyControlDTCSettingAtOnce = Dem_CtlNotifyControlDTCSettingAtOnce;

    for( loopCount = (Dem_u16_AdjustCntByEventNumType)0U; loopCount < notifyControlDTCSettingAtOnce; loopCount++ )
    {
        retTempVal = Dem_Control_GetNextEventPosByDTCsForDTCSetting( Dem_CtlEnableDTCSettingEventPos, &nextEventPos );
        if( retTempVal == DEM_IRT_OK )
        {
            Dem_CfgInfoPm_TriggerInitMForEFnc( nextEventPos, DEM_INIT_MONITOR_REENABLED, &resultOfCallback );

            Dem_CtlEnableDTCSettingEventPos = nextEventPos;
        }
        else
        {
            break;
        }
    }

    switch( retTempVal )
    {
        case DEM_IRT_OK:
            retVal = DEM_IRT_PENDING;
            break;
        case DEM_IRT_NO_MATCHING_ELEMENT:
            retVal = DEM_IRT_OK;
            break;
        default:
            /* No process */
            break;
    }

    return retVal;
}


/*--------------------------------------------------------------------------*/
/* Unit Internal functions(data)                                            */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_GetNextEventPosByDTCsForDTCSetting         */
/* Description   | Returns the next event index corresponding to the speci- */
/*               | fied DTC/group DTCs/all DTCs.                            */
/* Preconditions | Now, supports all DTCs only.                             */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        The specified DTC/DTCs group/all DTCs.            */
/*               | [in] BaseEventPos :                                      */
/*               |        The specified based event index.                  */
/*               | [out] NextEventPosPtr :                                  */
/*               |        The next event index which has been retrieved.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The next event index retrieving is - */
/*               |        successful.                                       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No more next event  */
/*               |         index.(retrieving finished)                      */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextEventPosByDTCsForDTCSetting
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) BaseEventPos,
    P2VAR( Dem_u16_EventPosType, AUTOMATIC, AUTOMATIC ) NextEventPosPtr
)
{
    VAR( Dem_u16_EventPosType, AUTOMATIC ) eventPos;
    VAR( Dem_u16_EventPosType, AUTOMATIC ) eventPosBase;
    VAR( Dem_u16_EventPosType, AUTOMATIC ) numOfAllEventConfigured;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Initializes the return value to OK. */
    retVal = DEM_IRT_OK;

    numOfAllEventConfigured = ( Dem_u16_EventPosType )Dem_PrimaryMemEventConfigureNum;    /*  DTCSetting control is PrimaryMemory only.   */

    eventPosBase  =   BaseEventPos;
    eventPos      =   DEM_EVENTPOS_INVALID;

    /*  search loop :   start of eventPos(DEM_EVENTPOS_MIN) to max.    */
    if( numOfAllEventConfigured > (Dem_u16_EventPosType)0U )
    {
        /* Checks whether the specified based event index is initial value. */
        if( eventPosBase == DEM_EVENTPOS_INVALID )
        {
            /* The specified based event index is initial value. */

            /* Sets the next event index to DEM_EVENTPOS_MIN. */
            eventPos  =   DEM_EVENTPOS_MIN;        /*  start of eventPos.             */
        }
        else if( ( eventPosBase + (Dem_u16_EventPosType)1U ) < numOfAllEventConfigured )    /* MISRA DEVIATION */
        {
            /* The specified based event index is less than number of the configured events. */

            /* Sets the next event index to based event index plus one. */
            eventPos  =   eventPosBase + (Dem_u16_EventPosType)1U;                   /* MISRA DEVIATION */
        }
        else
        {
            /* The specified based event index is number of the configured events or more. */

            /* Sets the next event index to initial value. */
            eventPos  =   DEM_EVENTPOS_INVALID;

            /* Sets return value to no matching element. */
            retVal = DEM_IRT_NO_MATCHING_ELEMENT;
        }

    }
    else
    {
        retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    }

    *NextEventPosPtr = eventPos;

    /* Returns with the result. */
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_SetDTCSettingStatus                          */
/* Description   | Sets DTC setting status.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCSettingStatus :                                  */
/*               |        DTC setting status.                               */
/* Return Value  | void                                                     */
/* Notes         | This Function is in CheckControlDTCSetting exclusive sec.*/
/*               | without initial process.                                 */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_SetDTCSettingStatus
(
    VAR( Dem_u08_DTCSettingStatusType, AUTOMATIC ) DTCSettingStatus
)
{
    Dem_CtlDTCSettingStatus = DTCSettingStatus;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetDTCSettingStatus                          */
/* Description   | Gets DTC setting status.                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_DTCSettingStatusType                             */
/*               |        DEM_CTL_STS_DTC_SETTING_ENABLE : DTC setting sta- */
/*               |        tus is enable.                                    */
/*               |        DEM_CTL_STS_DTC_SETTING_TO_ENABLE : DTC setting   */
/*               |        status is transitting enable.                     */
/*               |        DEM_CTL_STS_DTC_SETTING_DISABLE : DTC setting st- */
/*               |        atus is disable                                   */
/*               |        DEM_CTL_STS_DTC_SETTING_TO_DISABLE : DTC setting  */
/*               |        status is transitting disable.                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCSettingStatusType, DEM_CODE) Dem_Control_GetDTCSettingStatus
( void )
{
    return Dem_CtlDTCSettingStatus;
}


/****************************************************************************/
/* Function Name | Dem_Control_DTCSettingStatus_RefreshRAM                  */
/* Description   | Refresh RAM  - Control                                   */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_DTCSettingStatus_RefreshRAM
( void )
{
    VAR( volatile Dem_u08_DTCSettingStatusType, AUTOMATIC )                      u8_dummy;      /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u08_DTCSettingStatusType, AUTOMATIC, DEM_VAR_NO_INIT )   u8_dummyPtrNoInit;   /*  for GlobalVariable address       */

    /* Exclusion is necessary       */
    SchM_Enter_Dem_CheckControlDTCSetting();                /*  enter exclusion     */
        u8_dummyPtrNoInit  = &Dem_CtlDTCSettingStatus;      /*  set GlobalVariable pointer  */
        u8_dummy           = *u8_dummyPtrNoInit;                  /*  read GlobalVariable data    */
        *u8_dummyPtrNoInit = u8_dummy;                      /*  rewrite GlobalVariable data */
    SchM_Exit_Dem_CheckControlDTCSetting();                 /*  exit exclusion      */
    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
