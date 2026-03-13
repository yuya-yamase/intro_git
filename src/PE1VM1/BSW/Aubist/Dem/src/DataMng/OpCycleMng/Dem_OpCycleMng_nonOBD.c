/* Dem_OpCycleMng_c(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/OpCycleMng/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_OFF )
#include "../../../inc/Dem_Rc_OpCycleMng.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_OpCycleMng_GetCycleState                             */
/* Description   | Gets operation cycle state by operation cycle index.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] CycleQualifiedIndex : cycle qualified index.        */
/* Return Value  | Dem_OperationCycleStateType                              */
/*               |    DEM_CYCLE_NOTIFY_START                                */
/*               |           : Operation cycle is notified.                 */
/*               |    DEM_CYCLE_NOTIFY_END                                  */
/*               |           : Operation cycle is not notified.             */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_OperationCycleStateType, DEM_CODE ) Dem_OpCycleMng_GetCycleState
(
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) CycleQualifiedIndex      /* MISRA DEVIATION */
)
{
    return DEM_CYCLE_NOTIFY_END;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_OFF- */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
