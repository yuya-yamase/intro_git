/* Dem_ConfigInfo_Misfire_c(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_Misfire/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../cfg/Dem_Misfire_Cfg.h"
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */

#include "Dem_ConfigInfo_Calibration.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_MISFIRE_CYL_DTC_MASK                        ((Dem_u32_DTCValueType)0x00FFFF00U)
#define DEM_MISFIRE_BITSHIFT_8                          ((uint8)8U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex        */
/* Description   | Gets an event ID by event index.                         */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event ID for retrieving.                      */
/*               | [out] MisfireStrgIndexPtr :                              */
/*               |        The event ID which has been retrieved.            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success.                             */
/*               |        DEM_IRT_NG : failed.                              */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndex                      */
/* VariableGuard | [GUD:RET:DEM_IRT_OK] MisfireStrgIndexPtr                 */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC, AUTOMATIC ) MisfireStrgIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;

    retVal  =   DEM_IRT_NG;
    misfireEventNum =   Dem_MisfireEventNum;
    if ( EventStrgIndex < misfireEventNum )
    {
        *MisfireStrgIndexPtr    =   ( Dem_u16_MisfireStrgIndexType )EventStrgIndex;
        retVal  =   DEM_IRT_OK;
    }
    return retVal;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CnvMisfireStrgIndexToEventStrgIndex        */
/* Description   | Gets an event ID by event index.                         */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] MisfireStrgIndex :                                  */
/*               |        The event ID for retrieving.                      */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The event ID which has been retrieved.            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success.                             */
/*               |        DEM_IRT_NG : failed.                              */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndexPtr                   */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CnvMisfireStrgIndexToEventStrgIndex
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireStrgIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;

    retVal  =   DEM_IRT_NG;
    misfireEventNum =   Dem_MisfireEventNum;
    if ( MisfireStrgIndex < misfireEventNum )
    {
        *EventStrgIndexPtr    =   ( Dem_u16_EventStrgIndexType )MisfireStrgIndex;
        retVal  =   DEM_IRT_OK;
    }
    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetNextEventStrgIndexAfterEventStrgIndexOfMisfire */
/* Description   | output next EventStrgIndex after misfire eventStrgIndex. */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetNextEventStrgIndexAfterEventStrgIndexOfMisfire
( void )
{
    /*  output next EventStrgIndex after misfire eventStrgIndex.    */

    return ( Dem_u16_EventStrgIndexType )Dem_MisfireEventNum;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission          */
/* Description   | Get an event ID by event index.                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission
( void )
{
    return Dem_MisfireEmissionEventIndex;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission          */
/* Description   | Get an event ID by event index.                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_MisfireStrgIndexType                             */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:AllValue] ReturnValue                           */
/****************************************************************************/
FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireEmission
( void )
{
    return ( Dem_u16_MisfireStrgIndexType )Dem_MisfireEmissionEventIndex;
}

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission          */
/* Description   | Get an event ID by event index.                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:AllValue] ReturnValue                           */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventStrgIndex_MisfireCAT
( void )
{
    return Dem_MisfireCatEventIndex;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission          */
/* Description   | Get an event ID by event index.                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_MisfireStrgIndexType                             */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireCAT
( void )
{
    return ( Dem_u16_MisfireStrgIndexType )Dem_MisfireCatEventIndex;
}
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex    */
/* Description   | Get an event ID by event index.                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event ID for retrieving.                      */
/*               | [out] SimilarStrgIndexPtr :                              */
/*               |        The event ID which has been retrieved.            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The event ID retrieving is successf- */
/*               |        ul.                                               */
/*               |        DEM_IRT_NG : The event ID retrieving is failed.   */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                /* [PRMCHK:CALLER] */
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) MisfirePairEventStrgIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttr;

    retVal = DEM_IRT_NG;

    eventAttr   =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemEventAttribute;         /* [GUDCHK:CALLER]EventStrgIndex */
    if( ( eventAttr & DEM_EVTATTR_MISFIRE ) == DEM_EVTATTR_MISFIRE )
    {
        if( ( eventAttr & DEM_EVTATTR_MISFIRE_CAT ) == DEM_EVTATTR_MISFIRE_CAT )
        {
            /*  this is misfire CAT : pair event is misfire Emission.  */
            *MisfirePairEventStrgIndexPtr = Dem_MisfireEmissionEventIndex;
        }
        else
        {
            /*  this is misfire Emission : pair event is  misfire CAT.  */
            *MisfirePairEventStrgIndexPtr = Dem_MisfireCatEventIndex;
        }
        retVal = DEM_IRT_OK;
    }

    return retVal;
}
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )      */

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex    */
/* Description   | Get an event ID by event index.                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event ID for retrieving.                      */
/*               | [out] SimilarStrgIndexPtr :                              */
/*               |        The event ID which has been retrieved.            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The event ID retrieving is successf- */
/*               |        ul.                                               */
/*               |        DEM_IRT_NG : The event ID retrieving is failed.   */
/* Notes         |                                                          */
/* history       | v5-1-0 : Dem_Misfire_GetAnotherEventIndex                */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                            /* MISRA DEVIATION */
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) MisfirePairEventStrgIndexPtr  /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /*  single misfire event.(only misfire Emission event.)     */
    /*  there is no pair event.                                 */

    retVal = DEM_IRT_NG;

    return retVal;
}
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF )     */

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp       */
/* Description   | Check Specific Event                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventCtrlIndex                                     */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : Misfire Event                               */
/*               |      FALSE : Normal Event                                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:TRUE] EventStrgIndex                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    retVal = (boolean)FALSE;

    if ( EventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]EventStrgIndex */
    {
        /*  get data.        */
        eventAttr   =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemEventAttribute;                 /* [GUD]EventStrgIndex */

        if( ( eventAttr & DEM_EVTATTR_MISFIRE ) == DEM_EVTATTR_MISFIRE )
        {
            /*  misfire event.         */
            retVal = (boolean)TRUE;
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp         */
/* Description   | Get Specific Event Kind.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventCtrlIndex                                     */
/*               |                                                          */
/* Return Value  | Dem_EventKindType                                        */
/*               |      DEM_EVTKIND_TYPE_NON_OBD_EVENT                      */
/*               |                  : no Misfire Event                      */
/*               |      |= DEM_EVTKIND_TYPE_MISFIRE_EVENT                   */
/*               |                  : Misfire Event                         */
/*               |      |= DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT               */
/*               |                  : CAT Misfire Event                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_EventKindType, DEM_CODE ) Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
    VAR( Dem_u16_EventAttributeType, AUTOMATIC ) eventAttr;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    /*  get data.        */
    eventKind   =   DEM_EVTKIND_TYPE_NON_OBD_EVENT;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if ( EventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]EventStrgIndex */
    {
        eventAttr   =   Dem_EventParameterStorageTable[ EventStrgIndex ].DemEventAttribute;                 /* [GUD]EventStrgIndex */

        /* Misfire event Judgment */
        if( ( eventAttr & DEM_EVTATTR_MISFIRE ) == DEM_EVTATTR_MISFIRE )
        {
            if( ( eventAttr & DEM_EVTATTR_MISFIRE_CAT ) == DEM_EVTATTR_MISFIRE_CAT )
            {
                /*  not emission misfire event == cat misfire event.        */
                eventKind = ( DEM_EVTKIND_TYPE_MISFIRE_EVENT | DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT );
            }
            else
            {
                eventKind = DEM_EVTKIND_TYPE_MISFIRE_EVENT;
            }
        }
    }

    return eventKind;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetObdFFDCylIndexOfMisfire                 */
/* Description   | Get the OBD FFD Cylnder Index by Trigger.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] Trigger :                                           */
/* Return Value  | Dem_u08_MisfireObdFFDCylIndexType                        */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_MisfireObdFFDCylIndexType, DEM_CODE ) Dem_CfgInfoPm_GetObdFFDCylIndexOfMisfire
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
)
{
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) retMisfireObdFFDCylIndex;

    if( Trigger == DEM_TRIGGER_ON_CONFIRMED )
    {
        retMisfireObdFFDCylIndex = Dem_MisfireObdFFDCylIndexConfirmed;
    }
    else if( Trigger == DEM_TRIGGER_ON_PENDING )
    {
        retMisfireObdFFDCylIndex = Dem_MisfireObdFFDCylIndexPending;
    }
    else if( Trigger == DEM_TRIGGER_ON_TEST_FAILED_THIS_OPERATION_CYCLE )
    {
        retMisfireObdFFDCylIndex = Dem_MisfireObdFFDCylIndexTFTOC;
    }
    else
    {
        retMisfireObdFFDCylIndex = DEM_MISFIRE_OBD_FFDCYL_INDEX_INVALID;
    }
    return retMisfireObdFFDCylIndex;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetFFDCylIndexOfMisfire                    */
/* Description   | Get the FFD Cylnder Index by Trigger.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] Trigger :                                           */
/* Return Value  | Dem_u08_MisfireFFDCylIndexType                           */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_MisfireFFDCylIndexType, DEM_CODE ) Dem_CfgInfoPm_GetFFDCylIndexOfMisfire
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
)
{
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) retMisfireFFDCylIndex;

    if( Trigger == DEM_TRIGGER_ON_CONFIRMED )
    {
        retMisfireFFDCylIndex = Dem_MisfireFFDCylIndexConfirmed;
    }
    else if( Trigger == DEM_TRIGGER_ON_PENDING )
    {
        retMisfireFFDCylIndex = Dem_MisfireFFDCylIndexPending;
    }
    else if( Trigger == DEM_TRIGGER_ON_TEST_FAILED_THIS_OPERATION_CYCLE )
    {
        retMisfireFFDCylIndex = Dem_MisfireFFDCylIndexTFTOC;
    }
    else if( Trigger == DEM_TRIGGER_ON_FDC_THRESHOLD )
    {
        retMisfireFFDCylIndex = Dem_MisfireFFDCylIndexFDCThreshold;
    }
    else
    {
        retMisfireFFDCylIndex = DEM_MISFIRE_FFDCYL_INDEX_INVALID;
    }

    return retMisfireFFDCylIndex;
}
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CheckMisfireEventFirstIndex                */
/* Description   | Check Misfire Event is Last Index                        */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : MisfireEvent LastIndex                      */
/*               |      FALSE : not Last Index                              */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckMisfireEventFirstIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventFirstIndex;

    retVal = (boolean)FALSE;

    misfireEventFirstIndex = Dem_MisfireEmissionEventIndex;

    if ( EventStrgIndex == misfireEventFirstIndex )
    {
        retVal = (boolean)TRUE;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CheckMisfireEventLastIndex                 */
/* Description   | Check Misfire Event is Last Index                        */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventStrgIndex                                     */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : MisfireEvent LastIndex                      */
/*               |      FALSE : not Last Index                              */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckMisfireEventLastIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventLastIndex;

    retVal = (boolean)FALSE;

    retCnvId = Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );

    if ( retCnvId == DEM_IRT_OK )
    {
        misfireEventLastIndex = Dem_MisfireEventNum;
        misfireEventLastIndex = misfireEventLastIndex - (Dem_u16_MisfireStrgIndexType)1U;

        if ( misfireIndex >= misfireEventLastIndex )
        {
            retVal = (boolean)TRUE;
        }
    }
    return retVal;
}
#endif /* ( DEM_ALTIUMPR_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_MergeMultipleCylinderBit                   */
/* Description   | merge the multiple cylinder                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireCylinder :                                   */
/*               |      The misfire cylinder bit                            */
/* Return Value  | Dem_MisfireCylinderType :                                */
/*               |      MisfireCylinder with multiple cylinder set          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_SetMultipleCylinder(v5-3-0).     */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_CfgInfoPm_MergeMultipleCylinderBit
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireCylinderBitCheck;
    VAR( boolean, AUTOMATIC ) misfireCalculateRandomMultipleCylinder;

    retCylinder = MisfireCylinder;

    misfireCalculateRandomMultipleCylinder = Dem_MisfireCalculateRandomMultipleCylinder;
    if( misfireCalculateRandomMultipleCylinder == (boolean)TRUE )
    {
        if( MisfireCylinder != DEM_MISFIRE_CYLINDER_NON )
        {
            misfireCylinderBitCheck =   ( MisfireCylinder & (Dem_MisfireCylinderType)( MisfireCylinder - DEM_MISFIRE_CHECK_CYLINDER_BIT ) );
            if( misfireCylinderBitCheck != DEM_MISFIRE_CYLINDER_NON )
            {
                retCylinder = retCylinder | DEM_MISFIRE_CYLINDER_RM;
            }
        }
    }

    return retCylinder;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetMisfireLowestCylinderBitFromCylBit      */
/* Description   | Get the lowest cylinder bit                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireCylinder :                                   */
/*               |      The misfire cylinder bit                            */
/* Return Value  | Dem_MisfireCylinderType :                                */
/*               |      The lowest cylinder                                 */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_GetLowestCylinder(v5-3-0).       */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_CfgInfoPm_GetMisfireLowestCylinderBitFromCylBit
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) loopCnt;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireCylinderBitCheck;

    misfireCylinderNum      = Dem_MisfireCylinderNum;
    misfireCylinderBitCheck = DEM_MISFIRE_CYLINDER_NON;

    for( loopCnt = DEM_MISFIRE_CYL_NUM_RM; loopCnt < misfireCylinderNum; loopCnt++ )
    {
        misfireCylinderBitCheck = MisfireCylinder & (Dem_MisfireCylinderType)(DEM_MISFIRE_CHECK_CYLINDER_BIT << loopCnt);
        if( misfireCylinderBitCheck != DEM_MISFIRE_CYLINDER_NON )
        {
            break;
        }
    }

    return misfireCylinderBitCheck;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetMisfireCylinderNumberFromCylBit         */
/* Description   | Get misfire cylinder number                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireCylinder :                                   */
/*               |      The misfire cylinder bit                            */
/* Return Value  | Dem_MisfireCylinderNumberType                            */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_GetCylinderNum(v5-3-0).          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderNumberType, DEM_CODE ) Dem_CfgInfoPm_GetMisfireCylinderNumberFromCylBit
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinder;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) loopCnt;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireCylinderBitCheck;

    misfireCylinderNum  = Dem_MisfireCylinderNum;
    misfireCylinder     = DEM_MISFIRE_CYL_NUM_INVALID;

    for( loopCnt = DEM_MISFIRE_CYL_NUM_RM; loopCnt < misfireCylinderNum; loopCnt++ )
    {
        misfireCylinderBitCheck =   MisfireCylinder & (Dem_MisfireCylinderType)(DEM_MISFIRE_CHECK_CYLINDER_BIT << loopCnt);
        if( misfireCylinderBitCheck != DEM_MISFIRE_CYLINDER_NON )
        {
            misfireCylinder = loopCnt;
            break;
        }
    }

    return misfireCylinder;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetMisfireCylinderNumberByUdsDTC           */
/* Description   | get misfire cylinder number by DTC.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCValue : DTC value.                               */
/* Return Value  | Dem_MisfireCylinderNumberType                            */
/*               |        cylinder number.                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_GetCylinderFromDTC(v5-3-0).      */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderNumberType, DEM_CODE ) Dem_CfgInfoPm_GetMisfireCylinderNumberByUdsDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue
)
{
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinder;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireSearchCylinderNum;

    misfireCylinderNum  =   Dem_MisfireCylinderNum;
    misfireCylinder     =   DEM_MISFIRE_CYL_NUM_INVALID;

    for( misfireSearchCylinderNum = (Dem_MisfireCylinderNumberType)0U; misfireSearchCylinderNum < misfireCylinderNum; misfireSearchCylinderNum++ )  /* [GUD:for]misfireSearchCylinderNum */
    {
        if( DTCValue == Dem_Misfire_CylUdsDTCTable[ misfireSearchCylinderNum ] )                            /* [GUD]misfireSearchCylinderNum */
        {
            misfireCylinder =   misfireSearchCylinderNum;
            break;
        }
    }
    return misfireCylinder;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber           */
/* Description   | get UdsDTC by misfire cylinder number.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] Dem_MisfireCylinderNumberType : cylinder number.    */
/* Return Value  | Dem_u32_DTCValueType                                     */
/*               |       UDS DTC value.                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u32_DTCValueType, DEM_CODE ) Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;

    dtcValue        =   DEM_DTC_VALUE_INVALID;

    misfireCylinderNum  =   Dem_MisfireCylinderNum;
    if ( MisfireCylinderNumber < misfireCylinderNum )                                           /* [GUD:if]MisfireCylinderNumber */
    {
        dtcValue    =   Dem_Misfire_CylUdsDTCTable[ MisfireCylinderNumber ];                    /* [GUD]MisfireCylinderNumber */
    }
    return dtcValue;
}

#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetOBDDTCByMisfireCylinderNumber           */
/* Description   | get UdsDTC by misfire cylinder number.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] Dem_MisfireCylinderNumberType : cylinder number.    */
/* Return Value  | Dem_u32_DTCValueType                                     */
/*               |       OBD DTC value.                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_GetEDSDTC(v5-3-0).               */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u32_DTCValueType, DEM_CODE ) Dem_CfgInfoPm_GetOBDDTCByMisfireCylinderNumber
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) tmpDTC;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;

    dtcValue        =   DEM_DTC_VALUE_INVALID;

    misfireCylinderNum  =   Dem_MisfireCylinderNum;
    if ( MisfireCylinderNumber < misfireCylinderNum )                                           /* [GUD:if]MisfireCylinderNumber */
    {
        tmpDTC = Dem_Misfire_CylUdsDTCTable[ MisfireCylinderNumber ];                           /* [GUD]MisfireCylinderNumber */
        dtcValue = (Dem_u32_DTCValueType)( tmpDTC & DEM_MISFIRE_CYL_DTC_MASK ) >> DEM_MISFIRE_BITSHIFT_8;
    }

    return dtcValue;
}
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )     */

/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_GetMisfireType_InEvtStrgGrp                */
/* Description   | Get the misfire type by eventindex.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | Dem_u08_MisfireKindType                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_GetEventMisfireType(v5-3-0).     */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_MisfireKindType, DEM_CODE ) Dem_CfgInfoPm_GetMisfireType_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) misfireType;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;

    misfireType = DEM_MISFIRE_KIND_INVALID;
    eventKind   =   Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );     /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */

    /*  check misfire event : emission.     */
    if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
    {
        if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
        {
            misfireType = DEM_MISFIRE_KIND_CAT;
        }
        else
        {
            misfireType = DEM_MISFIRE_KIND_EMISSION;
        }
    }
    return misfireType;
}

#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
