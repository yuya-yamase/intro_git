/* Dem_DTC_GetDTCStatusByDTC_c(v5-7-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTC_GetDTCStatusByDTC/CODE                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../cfg/Dem_Data_Cfg.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_Pm_DataAvl.h"
#include "../../../../inc/Dem_Pm_DTC.h"
#include "../../../../inc/Dem_Rc_DataMng.h"

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
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCStatusByDTC                                */
/* Description   | Gets the UDS DTC status byte corresponding to specified  */
/*               |  event ID.                                               */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] TargetEventStrgIndex :                              */
/*               |        The event index corresponding to the event ID.    */
/*               | [out] DTCStatusPtr :                                     */
/*               |        The UDS DTC status byte which has been retrieved- */
/*               |        .                                                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The UDS DTC status byte retrieving - */
/*               |        is successful.                                    */
/*               |        DEM_IRT_NG : The UDS DTC status byte retrieving - */
/*               |        is failed.                                        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) retStatusOfDTC;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) tempStatusOfDTC;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndexCnt;
    VAR( boolean, AUTOMATIC ) eventAvailableDef;

    /* Set initial value. */
    retVal = DEM_IRT_NG;

    /* set target event. */
    eventStrgIndex = TargetEventStrgIndex;
    /* get num of event index in DTC group. */
    eventStrgIndexNum = Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp( eventStrgIndex );

    if( eventStrgIndexNum == ( Dem_u16_EventStrgIndexType )1U )
    {
        /* Check available status. */
        eventAvailableDef = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
        if( eventAvailableDef == (boolean)TRUE )
        {
            /* Gets the status of DTC of the event record corresponding to the specified event index. */
            (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &retStatusOfDTC );   /* no return check required */

            retVal = DEM_IRT_OK;
        }
        else
        {
            retStatusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
        }
    }
    else
    {
        retStatusOfDTC  = DEM_DTCSTATUS_BYTE_ALL_OFF;
        tempStatusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
        for( eventStrgIndexCnt = ( Dem_u16_EventStrgIndexType )0U; eventStrgIndexCnt < eventStrgIndexNum; eventStrgIndexCnt++ )
        {
            /* Check available status. */
            eventAvailableDef = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( eventStrgIndex );
            if( eventAvailableDef == (boolean)TRUE )
            {
                /* Gets the status of DTC of the event record corresponding to the specified event index. */
                (void)Dem_DataMngC_GetER_StatusOfDTC( eventStrgIndex, &tempStatusOfDTC );   /* no return check required */

                /* Merge StatusOfDTC */
                retStatusOfDTC = ( retStatusOfDTC | tempStatusOfDTC );
                retVal = DEM_IRT_OK;
            }
            /* get next event index. */
            eventStrgIndex = Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp( eventStrgIndex );
        }

        /* Checks the result of retrieving the event record. */
        if( retVal == DEM_IRT_OK )
        {
            /* Retrieving the event record is successful. */

            /* Bit4 is set as below. */
            /* (Event[1].bit4 OR Event[2].bit4 OR ... OR  Event[n].bit4) AND NOT(Event[1].bit5 OR Event[2].bit5 OR ... OR  Event[n].bit5) */
            /* So Check Bit5. Bit5 is on, set Bit4 to 0. */
            if( ( retStatusOfDTC & DEM_UDS_STATUS_TFSLC ) == DEM_UDS_STATUS_TFSLC )
            {
                retStatusOfDTC = ( retStatusOfDTC & ~DEM_UDS_STATUS_TNCSLC );
            }

            /* Bit6 is set as below. */
            /* (Event[1].bit6 OR Event[2].bit6 OR ... OR  Event[n].bit6) AND NOT(Event[1].bit1 OR Event[2].bit1 OR ... OR  Event[n].bit1) */
            /* So Check Bit1. Bit1 is on, set Bit6 to 0. */
            if( ( retStatusOfDTC & DEM_UDS_STATUS_TFTOC ) == DEM_UDS_STATUS_TFTOC )
            {
                retStatusOfDTC = ( retStatusOfDTC & ~DEM_UDS_STATUS_TNCTOC );
            }
        }
        else
        {
            retStatusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
        }
    }

    /* Stores StatusOfDTC of the event memory entry of temporary area to the specified parameter. */
    *DTCStatusPtr = retStatusOfDTC;

    return retVal;
}

#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )     */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DTC_GetDTCStatusByDTC                                */
/* Description   | Gets the UDS DTC status byte corresponding to specified  */
/*               |  event ID.                                               */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] TargetEventStrgIndex :                              */
/*               |        The event index corresponding to the event ID.    */
/*               | [out] DTCStatusPtr :                                     */
/*               |        The UDS DTC status byte which has been retrieved- */
/*               |        .                                                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The UDS DTC status byte retrieving - */
/*               |        is successful.                                    */
/*               |        DEM_IRT_NG : The UDS DTC status byte retrieving - */
/*               |        is failed.                                        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_DataMngC_GetER_StatusOfDTC( TargetEventStrgIndex, DTCStatusPtr );

    return retVal;
}

#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
