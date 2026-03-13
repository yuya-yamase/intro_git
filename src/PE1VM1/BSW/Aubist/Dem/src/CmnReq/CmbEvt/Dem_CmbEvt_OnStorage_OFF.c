/* Dem_CmbEvt_OnStorage_OFF_c(v5-5-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmbEvt_OnStorage_OFF/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#include "../../../cfg/Dem_CombinedEvent_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_OFF )

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST          /*  PreInit section               */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp        */
/* Description   | get delegate eventCtrlIndex in EventStorageIndexGroup.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex                                      */
/* Return Value  | Dem_u16_EventCtrlIndexType                               */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE_TRUST ) Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;

    eventCtrlIndex  =   (Dem_u16_EventCtrlIndexType)EventStrgIndex;

    return eventCtrlIndex;
}

/****************************************************************************/
/* Function Name | Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp            */
/* Description   | get next eventCtrlIndex in EvnetStorageIndexGroup.       */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex                                      */
/* Return Value  | Dem_u16_EventCtrlIndexType                               */
/* Notes         | This function is for PrimaryMemory only.                 */
/*               | Use this function after checking memory type.            */
/****************************************************************************/
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE_TRUST ) Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;

    eventCtrlIndex  =   EventCtrlIndex;

    return eventCtrlIndex;
}

/****************************************************************************/
/* Function Name | Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp              */
/* Description   | get number of eventCtrlIndex in EvnetStorageIndexGroup.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex                                      */
/* Return Value  | Dem_u16_EventCtrlIndexType                               */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE_TRUST ) Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;

    eventCtrlIndex  =   (Dem_u16_EventCtrlIndexType)1U;

    return eventCtrlIndex;
}


#define DEM_STOP_SEC_CODE_TRUST           /*  PreInit section               */
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex            */
/* Description   | convert eventCtrlIndex to eventStrgIndex.                */
/* Preconditions | EventCtrlIndex is PrimaryMemory.                         */
/* Parameters    | [in] EventCtrlIndex                                      */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         | This function is for PrimaryMemory only.                 */
/*               | Use this function after checking memory type.            */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:Not DEM_EVENTSTRGINDEX_INVALID] ReturnValue     */
/* VariableGuard | [GUD:RET:IF_GUARDED: EventCtrlIndex ] ReturnValue    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    eventStrgIndex = ( Dem_u16_EventStrgIndexType )EventCtrlIndex;

    return eventStrgIndex;
}

/****************************************************************************/
/* Function Name | Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex            */
/* Description   | check whether eventCtrlIndex is delegate in EvnetStorageIndexGroup.   */
/* Preconditions | EventCtrlIndex is PrimaryMemory.                         */
/* Parameters    | [in] EventCtrlIndex                                      */
/* Return Value  | boolean                                                  */
/*               |          TRUE  : Delegate EventCtrlIndex.                */
/*               |          FALSE : No Delegate EventCtrlIndex.             */
/* Notes         | This function is for PrimaryMemory only.                 */
/*               | Use this function after checking memory type.            */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_CmbEvt_CheckDelegateEventCtrlIndex_InEvtStrgGrp
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) bDelegate;

    bDelegate   =   (boolean)TRUE;

    return bDelegate;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /*   ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_OFF )     */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
