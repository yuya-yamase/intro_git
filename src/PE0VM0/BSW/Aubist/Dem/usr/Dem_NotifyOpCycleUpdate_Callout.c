/* Dem_NotifyOpCycleUpdate_Callout_c(v5-10-0)                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/NotifyOpCycleUpdate_Callout/CODE                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_NotifyOpCycleUpdate_Callout.h"

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
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_NotifyOperationCycleUpdated                          */
/* Description   | notify operation cycle updated.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleId : operation cycle ID               */
/*               | [in] DrivingCycleQualified :                             */
/*               |        Driving cycle qualified or not.                   */
/*               |          TRUE    :   cycle qualified.                    */
/*               |          FALSE   :   cycle is not qualified.             */
/*               | [in] WarmUpCycleQualified :                              */
/*               |        Warmup cycle qualified or not.                    */
/*               |          TRUE    :   cycle qualified.                    */
/*               |          FALSE   :   cycle is not qualified.             */
/* Return Value  | none.                                                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifyOperationCycleUpdated
(
    VAR( uint8, AUTOMATIC ) OperationCycleId,
    VAR( boolean, AUTOMATIC ) DrivingCycleQualified,
    VAR( boolean, AUTOMATIC ) WarmUpCycleQualified
)
{
    return ;
}


#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
