/* Dem_ConfigInfo_Similar_c(v5-5-0)                                         */
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

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
#include "../../../cfg/Dem_Similar_Cfg.h"
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

#include "Dem_ConfigInfo_Calibration.h"

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

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex        */
/* Description   | Gets an event ID by event index.                         */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
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
/* VariableGuard | [GUD:RET:DEM_IRT_OK] SimilarStrgIndexPtr                 */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC, AUTOMATIC ) SimilarStrgIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarEventNum;

    retVal  =   DEM_IRT_NG;
    similarEventNum =   Dem_SimilarEventNum;
    if ( EventStrgIndex < similarEventNum )
    {
        *SimilarStrgIndexPtr    =   ( Dem_u16_SimilarStrgIndexType )EventStrgIndex;
        retVal  =   DEM_IRT_OK;
    }
    return retVal;
}

#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CnvSimilarStrgIndexToEventStrgIndex        */
/* Description   | Gets an event ID by event index.                         */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_CnvSimilarStrgIndexToEventStrgIndex
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex
)
{
    return ( Dem_u16_EventStrgIndexType )SimilarStrgIndex;
}
#endif  /*   ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )   */
#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_OFF )
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfoPm_CnvSimilarStrgIndexToEventStrgIndex        */
/* Description   | Gets an event ID by event index.                         */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_CnvSimilarStrgIndexToEventStrgIndex
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex
)
{
    return ( Dem_u16_EventStrgIndexType )SimilarStrgIndex;
}
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )      */
#endif  /*   ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_OFF )   */

#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )     */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
