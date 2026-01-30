/* Dem_Control_PIDCalc_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_PIDCalc/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_Control_local.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_PID_PIDCalc.h"

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )
#include "../../../cfg/Dem_MasterOBD_Cfg.h"
#include "../../../usr/Dem_SavedZone_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* PID cycle counter INITIAL */
#define DEM_CTL_PID_CYC_COUNTER_INITIAL              ((Dem_u16_PIDCalcCycleCounterType)0x0000U)

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

static VAR( Dem_u16_PIDCalcCycleCounterType, DEM_VAR_NO_INIT )    Dem_CtlCalculateDistancePIDCycleCounter;
static VAR( Dem_u16_PIDCalcCycleCounterType, DEM_VAR_NO_INIT )    Dem_CtlCalculateTimeSESPIDCycleCounter;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Control_InitPIDInfo                                  */
/* Description   | Initialization of calculation cycle counter.             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_InitPIDInfo
( void )
{
    Dem_CtlCalculateDistancePIDCycleCounter = DEM_CTL_PID_CYC_COUNTER_INITIAL;
    Dem_CtlCalculateTimeSESPIDCycleCounter = DEM_CTL_PID_CYC_COUNTER_INITIAL;

    return;
}

/****************************************************************************/
/* Function Name | Dem_Control_UpdatePIDProcess                             */
/* Description   | Judgment of calculation execution based on PID calculat- */
/*               | ion cycle.                                               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_UpdatePIDProcess
( void )
{
    Dem_CtlCalculateDistancePIDCycleCounter = Dem_CtlCalculateDistancePIDCycleCounter + (Dem_u16_PIDCalcCycleCounterType)1U;
    if( Dem_CtlCalculateDistancePIDCycleCounter >= Dem_CalculationDistanceTable.DemCalculateDivideCycleCount )
    {
        Dem_CtlCalculateDistancePIDCycleCounter = DEM_CTL_PID_CYC_COUNTER_INITIAL;

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        Dem_PID_UpdateDistanceInfo();

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/

    }

    Dem_CtlCalculateTimeSESPIDCycleCounter = Dem_CtlCalculateTimeSESPIDCycleCounter + (Dem_u16_PIDCalcCycleCounterType)1U;
    if( Dem_CtlCalculateTimeSESPIDCycleCounter >= Dem_CalculationTimeSESTable.DemCalculateDivideCycleCount )
    {
        Dem_CtlCalculateTimeSESPIDCycleCounter = DEM_CTL_PID_CYC_COUNTER_INITIAL;

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        Dem_PID_UpdateTimeSESInfo();

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/

    }

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
