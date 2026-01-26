/* Dem_CmbEvt_OnRetrieval_c(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmbEvt_OnRetrieval/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#include "../../../cfg/Dem_CombinedEvent_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )

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


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp                  */
/* Description   | get number of eventStrgIndex in DTCGrpTable.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] Dem_u16_EventStrgIndexType  :                       */
/*               |        EventStrgIndex.                                   */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp. */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) numOfEventStrgIndex;

    numOfEventStrgIndex = Dem_CfgInfoPm_GetEventNumberOfSameDTCGroup( EventStrgIndex );

    return numOfEventStrgIndex;
}

/****************************************************************************/
/* Function Name | Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp                */
/* Description   | get next eventStrgIndex in DTCGrpTable.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] Dem_u16_EventStrgIndexType  :                       */
/*               |        EventStrgIndex.                                   */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp. */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) nextEventStrgIndex;

    nextEventStrgIndex = Dem_CfgInfoPm_GetNextEventStrgIndexOfSameDTCGroup( EventStrgIndex );

    return nextEventStrgIndex;
}

/****************************************************************************/
/* Function Name | Dem_CmbEvt_CheckDelegateEventStrgIndex_InDTCGrp          */
/* Description   | check whether eventCtrlIndex is delegate in same DTC group.   */
/* Preconditions | EventStrgIndex is PrimaryMemory.                         */
/* Parameters    | [in] EventStrgIndex                                      */
/* Return Value  | boolean                                                  */
/*               |          TRUE  : Delegate EventStrgIndex.                */
/*               |          FALSE : No Delegate EventStrgIndex.             */
/* Notes         | This function is for PrimaryMemory only.                 */
/*               | Use this function after checking memory type.            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_CmbEvt_CheckDelegateEventCtrlIndex_InEvtStrgGrp. */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CmbEvt_CheckDelegateEventStrgIndex_InDTCGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) bDelegate;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    bDelegate   =   (boolean)FALSE;

    /*  Delegate EventCtrlIndex.        */
    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    if ( EventStrgIndex < eventStorageNum )                                                         /* [GUD:if]EventStrgIndex */
    {
        bDelegate   =   Dem_CfgInfoPm_CheckDelegateEventStrgIndexInSameDTCGroup( EventStrgIndex );
    }

    return bDelegate;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )     */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
