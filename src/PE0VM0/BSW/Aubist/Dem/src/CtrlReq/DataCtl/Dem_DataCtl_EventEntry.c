/* Dem_DataCtl_EventeEntry_c(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_EventeEntry/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_Pm_PreFFD.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "Dem_DataCtl_local.h"
#include "Dem_DataCtl_EventEntry_local.h"
#include "Dem_DataCtl_TSFFD_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

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

/****************************************************************************/
/* Saved temporary area of event memory entry                               */
/****************************************************************************/
VAR( Dem_TmpEventMemoryEntryType, DEM_VAR_NO_INIT ) Dem_TmpEventMemoryEntry;

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
VAR( Dem_u08_FFValidTriggerType, DEM_VAR_NO_INIT ) Dem_TmpUpperLimitReachedTrigger;
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Temporary area for event displacement                                    */
/****************************************************************************/
VAR( Dem_EventDisplacementType, DEM_VAR_NO_INIT ) Dem_EventDisplacement;

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
VAR( Dem_Copy_FaultRecordOverwrittenType, DEM_VAR_NO_INIT ) Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM];
#endif  /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Data_SaveEventMemoryEntryToTmp                       */
/* Description   | Saves an event memory entry specified by event index to  */
/*               |  temporary area.                                         */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SaveEventMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Saves the event memory entry corresponding to the specified event ID. */
    retVal = Dem_Data_SaveEventMemoryEntry( EventStrgIndex );

    /* Returns with the result. */
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_UpdateEventMemoryEntryFromTmp                   */
/* Description   | Updates the event memory entry from temporary area.      */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_UpdateEventMemoryEntryFromTmp
( void )
{

    /* Compares the event memory entry corresponding to the event index of temporary area from temporary area. */
    Dem_Data_CompareEventMemoryEntryToTmp();

    /* Set the flag whether to update the consistency id */
    Dem_Data_SetConsistencyIdUpdateFlg();

    /* Stores the event memory entry from the event memory entry of temporary area. */
    Dem_Data_StoreEventMemoryEntryFromTmp();


    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_CheckFaultRecordOverwrite                       */
/* Description   | Checks if the fault record will be overwritten.          */
/* Preconditions | None                                                     */
/* Parameters    | [out] EventStrgIndexPtr : EventStrgIndex                 */
/*               | [out] DTCStatusAtOverwrittenPtr :                        */
/*               |          statusofDTC at overwritten.                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : The fault reocrd will be overwritten.     */
/*               |        FALSE : The fault reocrd will not be overwritten. */
/* Notes         | Called from Dem_MainFunction                             */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_Data_CheckFaultRecordOverwrite
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusAtOverwrittenPtr
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    eventStrgIndex = Dem_EventDisplacement.EventStrgIndexOfFaultRecordOverwritten;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( eventStrgIndex < eventStorageNum )                                                                  /* [GUD:if]eventStrgIndex */
    {
        /* The fault reocrd will be overwritten. */
        retVal = (boolean)TRUE;
        (*EventStrgIndexPtr) = eventStrgIndex;
        (*DTCStatusAtOverwrittenPtr) = Dem_EventDisplacement.DTCStatusAtFaultRecordOverwritten;
    }
    else
    {
        /* The fault reocrd will not be overwritten. */
        retVal = (boolean)FALSE;
    }

    return retVal;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF )
FUNC( boolean, DEM_CODE ) Dem_Data_CheckFaultRecordOverwrite
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,    /* MISRA DEVIATION */
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusAtOverwrittenPtr      /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) retVal;

    /* The fault reocrd will not be overwritten. */
    retVal = (boolean)FALSE;

    return retVal;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF ) */

/****************************************************************************/
/* Function Name | Dem_Data_CheckTSFFDeleteByFFROverwritten                 */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : The fault reocrd will be overwritten.     */
/*               |        FALSE : The fault reocrd will not be overwritten. */
/* Notes         | Called from Dem_MainFunction                             */
/****************************************************************************/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_Data_CheckTSFFDeleteByFFROverwritten
( void )
{
    return Dem_EventDisplacement.TSFFDeleteByFFROverwritten;
}
#endif /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

#if ( DEM_TSFF_PM_SUPPORT == STD_OFF )
FUNC( boolean, DEM_CODE ) Dem_Data_CheckTSFFDeleteByFFROverwritten
( void )
{
    return (boolean)FALSE;
}
#endif /* ( DEM_TSFF_PM_SUPPORT == STD_OFF ) */

#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF )
FUNC( boolean, DEM_CODE ) Dem_Data_CheckTSFFDeleteByFFROverwritten
( void )
{
    return (boolean)FALSE;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF ) */

/****************************************************************************/
/* Function Name | Dem_Data_CheckStorePredictiveFFDOfTmp                    */
/* Description   | Check PredictiveFFD is stored from temporary area.       */
/* Preconditions | The event memory entry usage status in the temporary RA- */
/*               | M area is "using".                                       */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : PredictiveFFD is stored.             */
/*               |        DEM_IRT_NG : PredictiveFFD is not stored.         */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CheckStorePredictiveFFDOfTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )    EventStrgIndex
)
{
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) freezeframeRecNumClassRef;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassRefIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    P2VAR( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) faultRecordPtr;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecordClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecordClassPtr;

    faultRecordPtr = &Dem_TmpEventMemoryEntry.FaultRecord;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    /* Initializes the auto variable. */
    retVal = DEM_IRT_NG;


    /* Checks the reference of freeze frame class. */
    Dem_CfgInfoPm_GetNumOfFreezeFrameRecordClass( &ffrRecordClassConfigureNum, &nonOBDFFRClassPerDTCMaxNum );
    Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass( EventStrgIndex, &freezeFrameClassRef, &freezeframeRecNumClassRef );     /* [GUD:OUT:Not DEM_FFCLASSINDEX_INVALID] freezeFrameClassRef *//* [GUD:OUT:Not DEM_FFRECNUMCLASSINDEX_INVALID] freezeframeRecNumClassRef */

    if( freezeFrameClassRef != DEM_FFCLASSINDEX_INVALID )                                                               /* [GUD:if] freezeFrameClassRef */
    {
        /* Checks the reference of freeze frame record number class. */
        if( freezeframeRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )                                               /* [GUD:if] freezeframeRecNumClassRef */
        {
            /* Holds the FreezeFrameRecNumClass table pointed to */
            /* by the FreezeFrameRecNumClass table list Index of the held DTCAttribute table. */
            freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[ freezeframeRecNumClassRef ];                  /* [GUD] freezeframeRecNumClassRef */
            for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )  /* [GUD:for] freezeFrameRecordClassRefIndex */
            {
                if( faultRecordPtr->RecordNumberIndex[freezeFrameRecordClassRefIndex] < nonObdFFDRecordNum )                                            /* [GUD] freezeFrameRecordClassRefIndex */
                {
                    /* Holds the DemFreezeFrameRecordIndex pointed to */
                    /* by the DemFreezeFrameRecordClassRef Index of the held FreezeFrameRecNumClass table. */
                    freezeFrameRecordClassIndex = freezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];              /* [GUD] freezeFrameRecordClassRefIndex */
                    if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                                      /* [GUD:if] freezeFrameRecordClassIndex */
                    {
                        freezeFrameRecordClassPtr = &Dem_FreezeFrameRecordClassTable[freezeFrameRecordClassIndex];                                      /* [GUD] freezeFrameRecordClassIndex *//* [GUD:CFG:IF_GUARDED: freezeFrameRecordClassIndex ]freezeFrameRecordClassPtr */
                        if( freezeFrameRecordClassPtr->DemFreezeFrameRecordTrigger == DEM_TRIGGER_ON_FDC_THRESHOLD )                                    /* [GUD] freezeFrameRecordClassPtr */
                        {
                            retVal = DEM_IRT_OK;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            /* DTC without DemFreezeFrameRecNumClass */
            /* No Process */
        }
    }
    else
    {
        /* DTC without DemFreezeFrameClass */
        /* No Process */
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
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
