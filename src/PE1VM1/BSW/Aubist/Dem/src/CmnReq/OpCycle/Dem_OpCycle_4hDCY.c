/* Dem_OpCycle_4hDCY_c(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_OpCycle_4hDCY/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../cfg/Dem_OpCycle_Cfg.h"

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

#if ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OpCycle_Check4hDCY                                   */
/* Description   | Check OperationCycle ID.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index         */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : OperationCycleIndex is 4hDCY.               */
/*               |      FALSE : OperationCycleIndex is not 4hDCY.           */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_OpCycle_Check4hDCY
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) opCycle4hDcy;

    opCycle4hDcy    =   Dem_ConfDemOperationCycle4hDCYId;
    if( OperationCycleIndex == opCycle4hDcy )
    {
        retVal = TRUE;
    }
    else
    {
        retVal = FALSE;
    }

    return retVal;
}
#endif  /*   ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )  */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
