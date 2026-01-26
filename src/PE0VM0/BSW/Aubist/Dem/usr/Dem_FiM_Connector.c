/* Dem_FiM_Connector_c(v5-0-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/FiM_Connector/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
#include <FiM_Dem.h>
#include "Dem_FiM_Connector.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_FiM_DemInit                                          */
/* Description   | DemInit for FiM                                          */
/* Preconditions | none.                                                    */
/* Parameters    | [in] OpStatusType :                                      */
/*               |        DEM_FIM_OPSTATUS_INITIAL                          */
/*               |        DEM_FIM_OPSTATUS_PENDING                          */
/*               | [in] TriggerType  :                                      */
/*               |        DEM_FIM_INITMODE_DEMINIT                          */
/*               |        DEM_FIM_INITMODE_OPERATIONCYCLE_ONLY              */
/*               |        DEM_FIM_INITMODE_DTC_CLEAR                        */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK                                              */
/*               |        FIM_E_PENDING                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_FiM_DemInit
(
    VAR( Dem_FiM_OpStatusType, AUTOMATIC ) OpStatusType,
    VAR( Dem_FiM_DemInitTriggerType, AUTOMATIC ) TriggerType
)
{
    VAR( Std_ReturnType, AUTOMATIC ) resultFimDemInit;

    resultFimDemInit = FiM_DemInit( OpStatusType, TriggerType );

    return resultFimDemInit;
}


/****************************************************************************/
/* Function Name | Dem_FiM_DemTriggerOnMonitorStatus                        */
/* Description   | Dem Trigger On MonitorStatus for FiM                     */
/* Preconditions | none.                                                    */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] OldMonitorStatus  :                                 */
/*               |        Monitor status before change.                     */
/*               | [in] NewMonitorStatus  :                                 */
/*               |        Detected / reported of Monitor status.            */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_FiM_DemTriggerOnMonitorStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_MonitorStatusType, AUTOMATIC ) OldMonitorStatus,
    VAR( Dem_MonitorStatusType, AUTOMATIC ) NewMonitorStatus
)
{
    FiM_DemTriggerOnMonitorStatus( EventId, OldMonitorStatus, NewMonitorStatus );

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_TRIGGER_FIM_REPORTS == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
