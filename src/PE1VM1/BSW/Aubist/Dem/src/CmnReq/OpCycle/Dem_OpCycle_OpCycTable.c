/* Dem_OpCycle_OpCycTable_c(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/OpCycle_OpCycTable/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_OpCycle_Cfg.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "Dem_OpCycle_OpCycTable.h"

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

/****************************************************************************/
/* Function Name | Dem_OpCycle_GetOperationCycleTypeMember                  */
/* Description   | get OperationCycle type.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index.        */
/* Return Value  | Dem_u08_OpCycleKindType                                  */
/*               |        DEM_OPCYC_IGNITION : IG cycle.                    */
/*               |        DEM_OPCYC_OTHER    : other cycle.                 */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_OpCycleKindType, DEM_CODE ) Dem_OpCycle_GetOperationCycleTypeMember
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
)
{
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC ) opcycKind;
    VAR( Dem_u08_OpCycleTableIndexType, AUTOMATIC ) opCycTableIndex;
    VAR( Dem_u08_OpCycleTableIndexType, AUTOMATIC ) opCycleTableNum;

    opCycTableIndex     =   ( Dem_u08_OpCycleTableIndexType )OperationCycleIndex;
    opCycleTableNum     =   ( Dem_u08_OpCycleTableIndexType )Dem_OperationCycleConfigureNum;

    opcycKind   =   DEM_OPCYC_OTHER;
    if ( opCycTableIndex < opCycleTableNum )    /* [GUD:if]opCycTableIndex */
    {
        opcycKind   =   Dem_OperationCycleTable[opCycTableIndex].DemOperationCycleTypeMember;       /* [GUD]opCycTableIndex */
    }
    return opcycKind;
}

/****************************************************************************/
/* Function Name | Dem_OpCycle_GetOperationCycleAutostart                   */
/* Description   | get OperationCycle type.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index.        */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Auto start target.                        */
/*               |        FALSE : not Auto start target.                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_OpCycle_GetOperationCycleAutostart
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
)
{
    VAR( boolean, AUTOMATIC ) opcycAutostart;
    VAR( Dem_u08_OpCycleTableIndexType, AUTOMATIC ) opCycTableIndex;
    VAR( Dem_u08_OpCycleTableIndexType, AUTOMATIC ) opCycleTableNum;

    opCycTableIndex     =   ( Dem_u08_OpCycleTableIndexType )OperationCycleIndex;
    opCycleTableNum     =   ( Dem_u08_OpCycleTableIndexType )Dem_OperationCycleConfigureNum;

    opcycAutostart   =   (boolean)FALSE;
    if ( opCycTableIndex < opCycleTableNum )    /* [GUD:if]opCycTableIndex */
    {
        opcycAutostart   =   Dem_OperationCycleTable[opCycTableIndex].DemOperationCycleAutostart;       /* [GUD]opCycTableIndex */
    }
    return opcycAutostart;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
