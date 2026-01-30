/* Dem_Control_DisableDTCInfo_c(v5-8-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_DisableDTCInfo/CODE                           */
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
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "Dem_Control_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    Dem_u32_DTCValueType            DTCValue;
    Dem_DTCOriginType               DTCOrigin;
    Dem_u16_EventStrgIndexType      EventStrgIndex;
} Dem_CtlDisableDTCInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_DisableDTCRecUpdateFirstRequest
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

static FUNC( void, DEM_CODE ) Dem_Control_SetDisableDTCInfo
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Control_CheckDTCUpdateAlreadyDisabled
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_CtlDisableDTCInfoType, DEM_VAR_NO_INIT )    Dem_CtlDisableDTCInfo;
static VAR( Dem_u08_DTCRecordUpdateStatusType, DEM_VAR_NO_INIT )    Dem_CtlDTCRecordUpdateStatus;

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
/* Function Name | Dem_Control_DisableDTCRecordUpdate                       */
/* Description   | Disables the specific-DTC's record update                */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Selects the DTC in UDS format for which DTC reco- */
/*               |        rd update shall be disabled                       */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory for which DTC record up- */
/*               |        date shall be disabled                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Event memory update of DTC successf- */
/*               |        ully disabled                                     */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing (in U- */
/*               |        DS format)                                        */
/*               |        DEM_IRT_PENDING : Disabling is currently not pos- */
/*               |        sible. The caller can retry later.                */
/* Notes         | This function is in DCM main process.                    */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_DisableDTCRecordUpdate
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal = DEM_IRT_PENDING;
    VAR( boolean, AUTOMATIC ) firstDisableUpdate = (boolean)FALSE;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_DTCRecordUpdateStatusType, AUTOMATIC ) updateStatus;

    /* When not in clear processing */
    updateStatus = Dem_CtlDTCRecordUpdateStatus;
    if( updateStatus == DEM_CTL_STS_DTC_UPDATE_ENABLE )
    {
        /* Update enable state */
        /* For shortening exclusive duration, once as update disable status */
        /* When it didn't become update disable, return update enable status */
        Dem_CtlDTCRecordUpdateStatus = DEM_CTL_STS_DTC_UPDATE_DISABLE;
        firstDisableUpdate = (boolean)TRUE;
    }
    else
    {
        /* Update disable status */
        /* Check update disable target */
        retTempVal = Dem_Control_CheckDTCUpdateAlreadyDisabled( DTCValue, DTCOrigin );
        if( retTempVal == DEM_IRT_OK )
        {
            /* When the DTC specified by argument has been update disable */
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* When the other DTC except the DTC specified by argument is in update disable status */
            /* No process */
        }
    }

    /* The first update disable processing */
    if( firstDisableUpdate == (boolean)TRUE )
    {
        retVal = Dem_Control_DisableDTCRecUpdateFirstRequest( DTCValue, DTCOrigin );
    }
    else
    {
        /* When update disable processing cannot be done or the DTC specified by argument has been update disable */
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_EnableDTCRecordUpdate                        */
/* Description   | Enables the specific-DTC's record update                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_EnableDTCRecordUpdate
( void )
{
    /* When update is disabled, discard the data held by Dem_Data */
    Dem_Data_ClearDisabledRecord();

    /* Initialize the information used in DTC update status management */
    Dem_Control_InitDTCRecordUpdateInfo();

    return ;
}

/*--------------------------------------------------------------------------*/
/* Unit Internal functions(process)                                         */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_DisableDTCRecUpdateFirstRequest              */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               | [in] DTCOrigin :                                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_WRONG_DTC :                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | refactor function.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_DisableDTCRecUpdateFirstRequest
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNumber;

    eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    misfireCylinderNumber = DEM_MISFIRE_CYL_NUM_INVALID;

    retVal  =   DEM_IRT_WRONG_DTC;

    /*  check available DTC.                    */
    retGetEventStrgIndex    =   Dem_DataAvl_GetEventStrgIndexByDTC( DTCValue, &eventStrgIndex, &misfireCylinderNumber );    /* [GUD:RET:DEM_IRT_OK] eventStrgIndex */
    if ( retGetEventStrgIndex == DEM_IRT_OK )
    {
        Dem_Data_SaveDisabledRecord( eventStrgIndex, misfireCylinderNumber );       /* [GUD]eventStrgIndex */

        /* Hold update disable information */
        Dem_Control_SetDisableDTCInfo( DTCValue, DTCOrigin, eventStrgIndex );       /* [GUD]eventStrgIndex */

        retVal = DEM_IRT_OK;
    }

    if( retVal != DEM_IRT_OK )
    {
        /* At the first update disable processing, when update disable processing cannot be done */
        /* Because it is as update disable status within exclusive duration, return update enable status */
        Dem_CtlDTCRecordUpdateStatus =  DEM_CTL_STS_DTC_UPDATE_ENABLE;
    }

    return retVal;
}

/*--------------------------------------------------------------------------*/
/* Unit Internal functions(data)                                            */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_InitDTCRecordUpdateInfo                      */
/* Description   | Initializes DTC record update info.                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_InitDTCRecordUpdateInfo
( void )
{
    /* Initialize update disable information */
    Dem_CtlDisableDTCInfo.DTCValue = (Dem_u32_DTCValueType)0U;
    Dem_CtlDisableDTCInfo.DTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
    Dem_CtlDisableDTCInfo.EventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

    /* Initialize update status */
    Dem_CtlDTCRecordUpdateStatus = DEM_CTL_STS_DTC_UPDATE_ENABLE;

    return;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetDTCRecordUpdateStatus_PrimaryMemory       */
/* Description   | Gets DTC record update status.                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_DTCRecordUpdateStatusType                        */
/*               |        DEM_CTL_STS_DTC_UPDATE_ENABLE : Update status is  */
/*               |         enable.                                          */
/*               |        DEM_CTL_STS_DTC_UPDATE_DISABLE : Update status i- */
/*               |        s disable.                                        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_DTCRecordUpdateStatusType, DEM_CODE) Dem_Control_GetDTCRecordUpdateStatus_PrimaryMemory
( void )
{
    return Dem_CtlDTCRecordUpdateStatus;
}


/****************************************************************************/
/* Function Name | Dem_Control_SetDisableDTCInfo                            */
/* Description   | Sets disable DTC info.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Diagnostic Trouble Code in UDS format             */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory the DTCs shall be read - */
/*               |        from                                              */
/*               | [in] EventStrgIndex :                                    */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_SetDisableDTCInfo
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    Dem_CtlDisableDTCInfo.DTCValue = DTCValue;
    Dem_CtlDisableDTCInfo.DTCOrigin = DTCOrigin;
    Dem_CtlDisableDTCInfo.EventStrgIndex = EventStrgIndex;

    Dem_Control_SetDisableRecordUpdateInfoForEDR();

    return;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetDisableDTCRecordEvent                     */
/* Description   | Get disable DTC record event index.                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/*               |        EventStrgIndex                                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_Control_GetDisableDTCRecordEvent
( void )
{
    return Dem_CtlDisableDTCInfo.EventStrgIndex;
}

/****************************************************************************/
/* Function Name | Dem_Control_CheckDisableDTCInfo                          */
/* Description   | Checks disable DTC.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Diagnostic Trouble Code in UDS format             */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory the DTCs shall be read - */
/*               |        from                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Target DTC is disable update status- */
/*               |        .                                                 */
/*               |        DEM_IRT_WRONG_DTC : Specified DTCValue is wrong   */
/*               |                            DTCValue.                     */
/*               |        DEM_IRT_WRONG_DTCORIGIN : Specified DTCOrigin is  */
/*               |                                  wrong DTCOrigin.        */
/*               |        DEM_IRT_NG : Target DTC is enable update status.  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckDisableDTCInfo
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal = DEM_IRT_NG;

    VAR( Dem_u08_DTCRecordUpdateStatusType, AUTOMATIC ) updateStatus;

    updateStatus = Dem_CtlDTCRecordUpdateStatus;
    if( updateStatus == DEM_CTL_STS_DTC_UPDATE_DISABLE )
    {
        /* Update disable status */
        /* Check update disable target */
        if( Dem_CtlDisableDTCInfo.DTCOrigin == DTCOrigin )
        {
            if( Dem_CtlDisableDTCInfo.DTCValue == DTCValue )
            {
                /* When the DTC specified by argument is in update disable status */
                retVal = DEM_IRT_OK;
            }
            else
            {
                /* When the other DTC except one specified by argument is in update disable status */
                retVal = DEM_IRT_WRONG_DTC;
            }
        }
        else
        {
            /* When the other DTC except one specified by argument is in update disable status */
            retVal = DEM_IRT_WRONG_DTCORIGIN;
        }
    }
    else
    {
        /* Update enable state */
        /* No process */
    }


    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_CheckDTCUpdateAlreadyDisabled                */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue :                                          */
/*               |        Diagnostic Trouble Code in UDS format             */
/*               | [in] DTCOrigin :                                         */
/*               |        select the source memory the DTCs shall be read - */
/*               |        from                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Control_CheckDTCUpdateAlreadyDisabled
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{

    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    if( Dem_CtlDisableDTCInfo.DTCValue == DTCValue )
    {
        if( Dem_CtlDisableDTCInfo.DTCOrigin == DTCOrigin )
        {
            /* When the DTC specified by argument is in update disable status */
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* When the other DTC except one specified by argument is in update disable status */
            /* No process */
        }
    }
    else
    {
        /* When the other DTC except one specified by argument is in update disable status */
        /* No process */
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
