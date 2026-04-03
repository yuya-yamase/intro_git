/* Dem_Control_PrestoreFFD_c(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_PrestoreFFD_/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )

#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_PreFFD.h"
#include "../../../usr/Dem_SavedZone_Callout.h"
#include "Dem_Control_local.h"

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
/* Function Name | Dem_Control_PrestoreFreezeFrame                          */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId    : Event identifier.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Pre-storage was succeed.             */
/*               |        DEM_IRT_NG : Pre-storage was failed.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_PrestoreFreezeFrame
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retTempVal = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                              /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - start.   */
            Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
            /*--------------------------------------*/

            retTempVal = Dem_PreFFD_PrestoreFreezeFrame( eventCtrlIndex );

            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - end.     */
            Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
            /*--------------------------------------*/

            if( retTempVal == DEM_IRT_OK )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_ClearPrestoredFreezeFrame                    */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId    : Event identifier.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Clearing was succeed.                */
/*               |        DEM_IRT_NG : Clearing was failed.                 */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ClearPrestoredFreezeFrame
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retTempVal = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                              /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retTempVal == DEM_IRT_OK )
        {
            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - start.   */
            Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
            /*--------------------------------------*/

            retTempVal = Dem_PreFFD_ClearPrestoredFreezeFrame( eventCtrlIndex );

            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - end.     */
            Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
            /*--------------------------------------*/

            if( retTempVal == DEM_IRT_OK )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/




#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* - DEM_FF_PRESTORAGE_SUPPORT == STD_ON -  */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
