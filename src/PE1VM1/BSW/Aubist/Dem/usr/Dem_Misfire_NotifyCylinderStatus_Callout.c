/* Dem_Misfire_NotifyCylinderStatus_Callout_c(v5-0-0)                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Misfire_NotifyCylinderStatus_Callout/CODE             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_Misfire_NotifyCylinderStatus_Callout.h"

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
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
/* Function Name | Dem_NotifyCylinderDTCStatusChanged                       */
/* Description   | Notify changed cylinder DTC status.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireCylinderNumber : cylinder number.            */
/*               | [in] MisfireDTCStatusOld   : DTC status of misfire.      */
/*               | [in] MisfireDTCStatusNew   : DTC status of misfire.      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifyCylinderDTCStatusChanged
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) MisfireDTCStatusOld,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) MisfireDTCStatusNew
)
{
    return ;
}

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
