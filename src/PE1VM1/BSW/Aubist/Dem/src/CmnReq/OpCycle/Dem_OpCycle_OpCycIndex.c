/* Dem_OpCycle_OpCycIndex_c(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/OpCycle_OpCycIndex/CODE                               */
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
/* Function Name | Dem_OpCycle_CheckOpCycleValue                            */
/* Description   | The range check that is in a state for an index,         */
/*               | an operation cycle for an operation cycle.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index.        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Values are normal.                   */
/*               |        DEM_IRT_NG : Values are abnormal.                 */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OpCycle_CheckOpCycleValue
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) opCycleConfigureNum;
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) opCycleRecordStateNum;
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    VAR( boolean, AUTOMATIC ) checkResult4hDcy;
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    retVal = DEM_IRT_NG;
    opCycleConfigureNum = Dem_OperationCycleConfigureNum;
    opCycleRecordStateNum = Dem_OperationCycleRecordStateNum;

    if( OperationCycleIndex < opCycleConfigureNum )
    {
        if( OperationCycleIndex >= opCycleRecordStateNum )
        {
            retVal = DEM_IRT_OK;
        }
    }

#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    checkResult4hDcy = Dem_OpCycle_Check4hDCY( OperationCycleIndex );
    if ( checkResult4hDcy == (boolean)TRUE )
    {
        retVal = DEM_IRT_NG;
    }
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    return retVal;
}


#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OpCycle_CheckQualifiedCycleValue                     */
/* Description   | The range check that is in a state for an index,         */
/*               | an operation cycle for an operation cycle.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index.        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Values are normal.                   */
/*               |        DEM_IRT_NG : Values are abnormal.                 */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OpCycle_CheckQualifiedCycleValue
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) opCycleStateNum;

    retVal = DEM_IRT_NG;
    opCycleStateNum = Dem_OperationCycleStateNum;

    if( OperationCycleIndex < opCycleStateNum )
    {
        retVal = DEM_IRT_OK;
    }

    return retVal;
}
#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_ON- */

/****************************************************************************/
/* Function Name | Dem_OpCycle_GetOpCycleIndexValAreaInOpCycleTable         */
/* Description   | Convert OpeationCycle Index to OperationCycle Id.        */
/* Preconditions | none                                                     */
/* Parameters    | [out] StartOfOperationCycleIndexPtr   : startindex.      */
/* Parameters    | [out] MaxOfOperationCycleTableNumPtr : max number.       */
/* Return Value  | Dem_u08_OperationCycleIdType                             */
/* Notes         |  none.                                                   */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OpCycle_GetRestartOpCycleIndexAreaInOpCycleTable
(
    P2VAR( Dem_u08_OpCycleIndexType, AUTOMATIC, AUTOMATIC ) StartOfOperationCycleIndexPtr,
    P2VAR( Dem_u08_OpCycleIndexType, AUTOMATIC, AUTOMATIC ) MaxOfOperationCycleTableNumPtr
)
{
    /*  ---- Dem_OperationCycleTable index[].------------   */
    /*      OperationCycleId : Qualified ID                 */
    /*      OperationCycleId : Qualified ID                 */
    /*      ---- Dem_OperationCycleRecordStateNum ---       */
    /*      OperationCycleId : RestartCycle ID              */
    /*      OperationCycleId : RestartCycle ID              */
    /*  ---- Dem_OperationCycleConfigureNum --------------  */

    /*  get RestartCycle ID start position.     */
    *StartOfOperationCycleIndexPtr       = Dem_StartOfRestartOperationCycleId;
    *MaxOfOperationCycleTableNumPtr      = Dem_OperationCycleConfigureNum;

    return ;
}


/****************************************************************************/
/* Function Name | Dem_OpCycle_CnvOpCycleIndexToId                          */
/* Description   | Convert OpeationCycle Index to OperationCycle Id.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index.        */
/* Return Value  | Dem_u08_OperationCycleIdType                             */
/* Notes          |  none.                                                  */
/****************************************************************************/
FUNC( Dem_u08_OperationCycleIdType, DEM_CODE ) Dem_OpCycle_CnvOpCycleIndexToId
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex
)
{
    return ( Dem_u08_OperationCycleIdType )OperationCycleIndex;
}

/****************************************************************************/
/* Function Name | Dem_OpCycle_CnvOpCycleIdToOpCycleIndex                   */
/* Description   | Convert OpeationCycle Id to OperationCycle Index.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] Dem_u08_OperationCycleIdType : Operation cycle index. */
/* Return Value  | Dem_u08_OpCycleIndexType                                 */
/* Notes         |  none.                                                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_OpCycleIndexType, DEM_CODE ) Dem_OpCycle_CnvOpCycleIdToOpCycleIndex
(
    VAR( Dem_u08_OperationCycleIdType, AUTOMATIC ) OperationCycleId
)
{
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) operationCycleIndex;

    operationCycleIndex =   ( Dem_u08_OpCycleIndexType )OperationCycleId;

    return operationCycleIndex;
}

#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OpCycle_CnvOpCycleIdToCycleQualifiedIndex            */
/* Description   | Convert OpeationCycle Id to CycleQualified Index.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] Dem_u08_OperationCycleIdType : Operation cycle index. */
/* Return Value  | Dem_u08_CycleQualifiedIndexType                          */
/* Notes         |  none.                                                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_CycleQualifiedIndexType, DEM_CODE ) Dem_OpCycle_CnvOpCycleIdToCycleQualifiedIndex
(
    VAR( Dem_u08_OperationCycleIdType, AUTOMATIC ) OperationCycleId
)
{
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) cycleQualifiedIndex;

    cycleQualifiedIndex =   ( Dem_u08_OpCycleIndexType )OperationCycleId;

    return cycleQualifiedIndex;
}
#endif  /*   ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )          */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
