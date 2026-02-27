/* Dem_UdmDataCtl_EventEntry02Clear_TSFFD_c(v5-5-0)                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_EventEntry02Clear_TSFFD/CODE               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )

#include "Dem_UdmDataCtl_EventEntry_TSFFD_local.h"
#include "Dem_UdmDataCtl_TSFFD_local.h"

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
/* Function Name | Dem_UdmData_ClearTimeSeriesFreezeFrameRecords            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               | [in] UdmEventIndex :                                     */
/*               | [in] UdmFaultRecordPtr :                                 */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_ClearTimeSeriesFreezeFrameRecords
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr
)
{
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsffRecordClassConfigureNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) startTSFFListIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListIndexLimit;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfTSFFPerDTC;

    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

    startTSFFListIndex = UdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex;
    if( startTSFFListIndex < tsffTotalDTCNum )
    {
        tsffRecordClassConfigureNum = Dem_TSFFRecordClassConfigureNum;
        tsFFRecClassRef = Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef( UdmEventIndex );
        if( tsFFRecClassRef < tsffRecordClassConfigureNum )                                                 /* [GUD:if]tsFFRecClassRef */
        {
            tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameClassRef;      /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED: tsFFRecClassRef ]tsFFClassRef */
            numberOfTSFFPerDTC = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC;   /* [GUD]tsFFClassRef */
            tsFFListIndexLimit = startTSFFListIndex + (Dem_u16_TSFFListIndexType)numberOfTSFFPerDTC;

            for( tsFFListIndex = startTSFFListIndex; tsFFListIndex < tsFFListIndexLimit; tsFFListIndex++ )
            {
                Dem_UdmData_ClearTSFFRecord( UdmGroupKindIndex, tsFFListIndex );
            }
        }
    }
    else
    {
        /* The record number index corresponding to the loop counter is invalid. */
        /* no processing, because the fault without time series freeze frame. */
    }

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON )  */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
