/* Dem_Control_Misfire_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_Misfire/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../cfg/Dem_Misfire_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Control_Misfire.h"
#include "../../../inc/Dem_Pm_Misfire.h"
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
/* Function Name | Dem_Control_GetCurrentFailedCylinder                     */
/* Description   | Get current failed cylinder.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId     : Event identifier.                     */
/*               | [out] CylinderPtr : Cylinder status.                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetCurrentFailedCylinder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
        retGetEventCtrlIndex = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                                /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retGetEventCtrlIndex == DEM_IRT_OK )
        {
            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [MisfireMng] function directory.                   */
            /*  - This function called from SW-C context.                               */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();
            /*--------------------------------------------------------------------------*/
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                        /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

            retVal = Dem_Misfire_GetCurrentFailedCylinder( eventStrgIndex, CylinderPtr );
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetFailedCylinderAtThisOC                    */
/* Description   | Get accumulate failed cylinder at this operation cycle.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId     : Event identifier.                     */
/*               | [out] CylinderPtr : Cylinder status.                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetFailedCylinderAtThisOC
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
        retGetEventCtrlIndex = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                                /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retGetEventCtrlIndex == DEM_IRT_OK )
        {
            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [MisfireMng] function directory.                   */
            /*  - This function called from SW-C context.                               */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();
            /*--------------------------------------------------------------------------*/
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                        /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: eventCtrlIndex ]eventStrgIndex */

            retVal = Dem_Misfire_GetFailedCylinderAtThisOC( eventStrgIndex, CylinderPtr );
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetFailedCylinderSinceLastClear              */
/* Description   | Get accumulate failed cylinder since last clear.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId     : Event identifier.                     */
/*               | [out] CylinderPtr : Cylinder status.                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetFailedCylinderSinceLastClear
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
        retGetEventCtrlIndex = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                                /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retGetEventCtrlIndex == DEM_IRT_OK )
        {
            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [MisfireMng] function directory.                   */
            /*  - This function called from SW-C context.                               */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();
            /*--------------------------------------------------------------------------*/
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                        /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: eventCtrlIndex ]eventStrgIndex */

            retVal = Dem_Misfire_GetFailedCylinderSinceLastClear( eventStrgIndex, CylinderPtr );
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetFailedCylinder                            */
/* Description   | Get accumulate failed cylinder.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId     : Event identifier.                     */
/*               | [out] CylinderPtr : Cylinder status.                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetFailedCylinder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;
        retGetEventCtrlIndex = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                                /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
        if( retGetEventCtrlIndex == DEM_IRT_OK )
        {
            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [MisfireMng] function directory.                   */
            /*  - This function called from SW-C context.                               */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();
            /*--------------------------------------------------------------------------*/
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                        /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: eventCtrlIndex ]eventStrgIndex */

            retVal = Dem_Misfire_GetFailedCylinder( eventStrgIndex, CylinderPtr );
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetCylinderDTCStatus                         */
/* Description   | Get current Misfire statusOfDTC.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireCylinderNumber : Cylinder Number.            */
/*               | [in] UDSStatusBytePtr      : statusOfDTC of Cylinder.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetCylinderDTCStatus
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) UDSStatusBytePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;

    retVal = DEM_IRT_NG;

    /*  check initialize status.            */
    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        misfireCylinderNum = Dem_MisfireCylinderNum;
        if ( MisfireCylinderNumber < misfireCylinderNum )
        {
            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [MisfireMng] and [DataMng] function directory.     */
            /*  - This function called from SW-C context.                               */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();
            /*--------------------------------------------------------------------------*/

            *UDSStatusBytePtr = Dem_Misfire_GetCylinderDTCStatus( MisfireCylinderNumber );

            /*------------------------------------------*/
            /*  convert to output statusOfDTC.          */
            /*------------------------------------------*/
            (*UDSStatusBytePtr) =   Dem_DTC_CnvDTCStatus_ForOutput( (*UDSStatusBytePtr) );

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
