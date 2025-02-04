/* Dem_OccrDTC_c(v5-5-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/OccrDTC/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )

#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_OccrDTC.h"
#include "../../../inc/Dem_Rc_OccrDTCMng.h"

#include "Dem_OccrDTC_local.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
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
/* Function Name | Dem_OccrDTC_GetDTCByOccurrenceTime                       */
/* Description   | Get DTC By Occurrence Time                               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  DTCRequest  :                                      */
/*               |          DEM_MOST_RECENT_FAILED_DTC                      */
/*               |          DEM_MOST_REC_DET_CONFIRMED_DTC                  */
/*               | [out] DTCValuePtr :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT :                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OccrDTC_GetDTCByOccurrenceTime
(
    VAR( Dem_DTCRequestType, AUTOMATIC ) DTCRequest,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) readEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetDTC;

    retVal = DEM_IRT_OK;

    /* Get event of occurrence time record */
    if( DTCRequest == DEM_MOST_REC_DET_CONFIRMED_DTC )
    {
        readEventStrgIndex = Dem_OccrDTCMng_GetMostRecentConfirmedData();
        eventStorageNum = Dem_PrimaryMemEventStorageNum;

        if( readEventStrgIndex == DEM_EVENTSTRGINDEX_INVALID )
        {
            /* Event is not occurred */
            retVal = DEM_IRT_NO_MATCHING_ELEMENT;
        }
        else if( readEventStrgIndex >= eventStorageNum )
        {
            /* Event is abnormal*/
            retVal = DEM_IRT_NG;
        }
        else
        {
            availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( readEventStrgIndex );
            if( availableStatus == (boolean)TRUE )
            {
                /* Event is normal */
                retGetDTC = Dem_DataAvl_GetUDSDTCByEventStrgIndex( readEventStrgIndex, DTCValuePtr );   /* [GUD:RET:DEM_IRT_OK] readEventStrgIndex */
                if ( retGetDTC != DEM_IRT_OK )
                {
                    retVal = DEM_IRT_NG;
                }
            }
            else
            {
                /* Event is not available */
                retVal = DEM_IRT_NG;
            }
        }
    }
    else
    {
        /* argument is out of range */
        retVal = DEM_IRT_NG;
    }
    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
