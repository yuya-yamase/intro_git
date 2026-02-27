/* Dem_OpCycle_CycleQualified_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/OpCycle_CycleQualified/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )

#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_OpCycle_Cfg.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_Rc_OpCycleMng.h"
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
/* Function Name | Dem_OpCycle_GetIGCycleQualified                          */
/* Description   | get IG cycle qualified.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index.        */
/*               | [out] IGCycleUpdatedPtr : IG cycle updated or not.       */
/*               |                  TRUE    :   this is IG Cycle.           */
/*               |                  FALSE   :   this isnot IG Cycle.        */
/*               | [out] OBDDCYQualifiedPtr : OBDDCY cycle updated or not.  */
/*               |                  TRUE    :   OBDDCY Cycle  updated       */
/*               |                  FALSE   :   OBDDCY Cycle isnot updated  */
/*               | [out] WarmUpQualifiedPtr : WarmUp cycle updated or not.  */
/*               |                  TRUE    :   WarmUp Cycle  updated       */
/*               |                  FALSE   :   WarmUp Cycle isnot updated  */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OpCycle_GetIGCycleQualified
(
    VAR( Dem_u08_OpCycleIndexType, AUTOMATIC ) OperationCycleIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IGCycleUpdatedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OBDDCYQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) WarmUpQualifiedPtr
)
{
    VAR( boolean, AUTOMATIC ) igCycle;
    VAR( boolean, AUTOMATIC ) drivingCycleQualified;
    VAR( boolean, AUTOMATIC ) warmUpCycleQualified;

    VAR( Dem_OperationCycleStateType, AUTOMATIC ) obdDcyFlag;
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) warmUpCycleFlag;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) opCycleObdDcy;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) opCycleWarmUp;
    VAR( Dem_u08_OpCycleKindType, AUTOMATIC ) opcycKind;

    igCycle                 = (boolean)FALSE;
    drivingCycleQualified   = (boolean)FALSE;
    warmUpCycleQualified    = (boolean)FALSE;

    /*  IG cycle ?          */
    opcycKind   =   Dem_OpCycle_GetOperationCycleTypeMember( OperationCycleIndex );
    if( opcycKind == DEM_OPCYC_IGNITION )
    {
        igCycle = (boolean)TRUE;
        opCycleObdDcy = Dem_ConfDemOperationCycleObdDcy;
        obdDcyFlag = Dem_OpCycleMng_GetCycleState( opCycleObdDcy );

        /*  OBD_DCY ?           */
        if( obdDcyFlag == DEM_CYCLE_NOTIFY_START )
        {
            drivingCycleQualified   = (boolean)TRUE;
            opCycleWarmUp           = Dem_ConfDemOperationCycleWarmUp;
            warmUpCycleFlag         = Dem_OpCycleMng_GetCycleState( opCycleWarmUp );

            /*  Warmup ?            */
            if( warmUpCycleFlag == DEM_CYCLE_NOTIFY_START )
            {
                warmUpCycleQualified    = (boolean)TRUE;
            }
        }
    }
    *IGCycleUpdatedPtr    =   igCycle;
    *OBDDCYQualifiedPtr   =   drivingCycleQualified;
    *WarmUpQualifiedPtr   =   warmUpCycleQualified;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_OpCycle_ResetObdDcyCycleQualified                    */
/* Description   | Reset qualified info at Driving Cycle updated.           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OpCycle_ResetObdDcyCycleQualified
( void )
{
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) opCycleObdDcy;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) opCycleWarmUp;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) opCyclePFCCycle;

    opCycleObdDcy = Dem_ConfDemOperationCycleObdDcy;
    opCycleWarmUp = Dem_ConfDemOperationCycleWarmUp;
    opCyclePFCCycle = Dem_ConfDemOperationCyclePFCCycle;

    Dem_OpCycleMng_SetCycleState( opCycleObdDcy, DEM_CYCLE_NOTIFY_END );
    Dem_OpCycleMng_SetCycleState( opCycleWarmUp, DEM_CYCLE_NOTIFY_END );
    Dem_OpCycleMng_SetCycleState( opCyclePFCCycle, DEM_CYCLE_NOTIFY_END );

    return ;
}

#if ( DEM_PFC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_OpCycle_SetCycleStartNoticeFlag                      */
/* Description   | Set an operation cycle start notice flag.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleIndex : Operation cycle index.        */
/*               | [in] CycleState : Operation cycle state.                 */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OpCycle_SetCycleStartNoticeFlag
(
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) CycleQualifiedIndex,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) CycleState
)
{
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) pfcCycleIndex;

    Dem_OpCycleMng_SetCycleState( CycleQualifiedIndex, CycleState );

    pfcCycleIndex = (Dem_u08_CycleQualifiedIndexType)Dem_ConfDemOperationCyclePFCCycle;
    if( CycleQualifiedIndex == pfcCycleIndex )
    {
        Dem_DTC_SetPFCCycleQualified();
    }

    return ;
}
#endif /* DEM_PFC_SUPPORT -STD_ON- */

#if ( DEM_PFC_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_OpCycle_SetCycleStartNoticeFlag                      */
/* Description   | Set an operation cycle start notice flag.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] CycleQualifiedIndex : Operation cycle index.        */
/*               | [in] CycleState : Operation cycle state.                 */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_OpCycle_SetCycleStartNoticeFlag
(
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) CycleQualifiedIndex,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) CycleState
)
{

    Dem_OpCycleMng_SetCycleState( CycleQualifiedIndex, CycleState );

    return ;
}
#endif /* DEM_PFC_SUPPORT -STD_OFF- */

/****************************************************************************/
/* Function Name | Dem_OpCycle_GetCycleStartNoticeFlag                      */
/* Description   | Get the operation cycle notice flag.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] CycleQualifiedIndex : Operation cycle index.        */
/* Return Value  | Dem_OperationCycleStateType                              */
/*               |    DEM_CYCLE_NOTIFY_START                                */
/*               |           : Operation cycle is notified.                 */
/*               |    DEM_CYCLE_NOTIFY_END                                  */
/*               |           : Operation cycle is not notified.             */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_OperationCycleStateType, DEM_CODE ) Dem_OpCycle_GetCycleStartNoticeFlag
(
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) CycleQualifiedIndex
)
{
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) cycleState;

    cycleState = Dem_OpCycleMng_GetCycleState( CycleQualifiedIndex );

    return cycleState;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_ON- */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-0-1         :2019-10-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
