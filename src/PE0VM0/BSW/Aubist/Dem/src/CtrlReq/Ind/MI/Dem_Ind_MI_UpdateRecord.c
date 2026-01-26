/* Dem_Ind_MI_UpdateRecord_c(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Ind_MI_UpdateRecord/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )

#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_CmnLib_Control.h"
#include "../../../../inc/Dem_Pm_Ind.h"
#include "../../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../../inc/Dem_Rc_DataMng.h"
#include "../../../../inc/Dem_Rc_OdrLst.h"
#include "Dem_Ind_MI_local.h"

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

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_IndMI_UpdateMILOrder
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) MILOccurrenceOrderPtr
);
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )  */

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
/* Function Name | Dem_IndMI_UpdateRecordWithMILInfo                        */
/* Description   | update record                                            */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               | [in] NewDTCStatusStPtr                                   */
/*               | [in] UpdateMIL                                           */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMI_UpdateRecordWithMILInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_DTCStatusStType,   AUTOMATIC,   AUTOMATIC ) NewDTCStatusStPtr,
    VAR( boolean, AUTOMATIC ) UpdateMIL                         /* MISRA DEVIATION */
)
{
    VAR( boolean, AUTOMATIC ) updatedERFlag;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetER;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) oldDTCStatusSt;

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) updatedFRFlag;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) milOccurrenceOrder;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )      */

    updatedERFlag   =   (boolean)FALSE;

    /*--------------------------------------*/
    /*  get current statusOfDTC.            */
    /*--------------------------------------*/
    retGetER    =   Dem_DataMngC_GetER_DTCStatusSt( EventStrgIndex, &oldDTCStatusSt );
    if ( retGetER == DEM_IRT_OK )
    {
        if ( oldDTCStatusSt.DTCStatus        != NewDTCStatusStPtr->DTCStatus        )
        {
            updatedERFlag   =   (boolean)TRUE;
        }
        else if ( oldDTCStatusSt.ExtendDTCStatus  != NewDTCStatusStPtr->ExtendDTCStatus  )
        {
            updatedERFlag   =   (boolean)TRUE;
        }
        else if ( oldDTCStatusSt.ExtendDTCStatus2 != NewDTCStatusStPtr->ExtendDTCStatus2 )
        {
            updatedERFlag   =   (boolean)TRUE;
        }
        else
        {
            /*  no process.     */
        }
    }

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )     /*  [FuncSw]    */
    faultIndex      =   DEM_FAULTINDEX_INVALID;
    updatedFRFlag   =   (boolean)FALSE;

    /*--------------------------------------*/
    /*  update MIL order                    */
    /*--------------------------------------*/
    if ( UpdateMIL == (boolean)TRUE )
    {
        /*  get fault record.                   */
        (void)Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex ); /* no return check required */

        updatedFRFlag   =   Dem_IndMI_UpdateMILOrder( faultIndex, &milOccurrenceOrder );
    }

    if ( updatedFRFlag == (boolean)TRUE )
    {
        /*--------------------------------------------------*/
        /*  Starts exclusion.                               */
        /*--------------------------------------------------*/
        SchM_Enter_Dem_EventMemory();

        /*  update event record. (statusOfDTC is update or not)     */
        /*  update with consistencyID.                              */
        /* Update a record(contain consistencyId) corresponding to an FaultIndex.                  */
        Dem_DataMngC_SetFR_MILOccurrenceOrder_WithUpdateConsistencyID( faultIndex, milOccurrenceOrder, &consistencyId );
        Dem_DataMngC_SetER_DTCStatusSt_AtUpdateFaultRecord( EventStrgIndex, NewDTCStatusStPtr, consistencyId );

        /*--------------------------------------------------*/
        /*  Finishes exclusion.                             */
        /*--------------------------------------------------*/
        SchM_Exit_Dem_EventMemory();
    }
    else
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )      */
    {
        if ( updatedERFlag == (boolean)TRUE )
        {
            /*  update event record.            */
            /*  update only data.               */
            Dem_DataMngC_SetER_DTCStatusSt( EventStrgIndex, NewDTCStatusStPtr );
        }
    }

    return ;
}

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_IndMI_UpdateMILOrder                                 */
/* Description   | update MIL order list.                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex                                          */
/*               | [out] MILOccurrenceOrderPtr                              */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : update data.                              */
/*               |        FALSE : not update data.                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_IndMI_UpdateMILOrder
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) MILOccurrenceOrderPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetMILOccr;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) numberOfObdMILDTCs;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) milOccurrenceOrder;
    VAR( boolean, AUTOMATIC ) updatedFRFlag;

    updatedFRFlag   =   (boolean)FALSE;

    /*  get current MIL occurrence info.    */
    failRecordNum = Dem_FailRecordNum;

    if ( FaultIndex < failRecordNum )
    {
        /*  get current number of ObdMILDTCs    */
        numberOfObdMILDTCs  =   Dem_DataMngC_GetNumberOfObdMILDTCs();

        /*  get MIL occurrence order.           */
        if( numberOfObdMILDTCs < (Dem_u08_OrderIndexType)failRecordNum )
        {
            milOccurrenceOrder  = DEM_FAIL_OCCURRENCE_NUM_INVALID;

            /*  get next order value.           */
            retGetMILOccr = Dem_OdrLst_MIL_GetNextOccurrenceOrder( &milOccurrenceOrder );

            if( retGetMILOccr == DEM_IRT_OK )
            {
                /*  regist MIL orderlist        */
                Dem_OdrLst_MIL_RegistComplete( FaultIndex, numberOfObdMILDTCs, milOccurrenceOrder );

                /*  increment number.           */
                Dem_DataMngC_IncrementNumberOfObdMILDTCs();

                *MILOccurrenceOrderPtr  =   milOccurrenceOrder;

                updatedFRFlag           =   (boolean)TRUE;
            }
        }
    }
    return updatedFRFlag;
}
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
