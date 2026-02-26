/* Dem_Control_Healing_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_Healing/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_Control_local.h"

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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Unit External functions                                                  */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Unit Internal functions(process)                                         */
/*--------------------------------------------------------------------------*/

#if ( DEM_INDICATOR_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_ProcessHealing                               */
/* Description   | Recovery process of MIL lighting state.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex : Event index.                       */
/*               | [in] OldDTCStatusStPtr  :   DTC status.                  */
/*               | [in/out] NewDTCStatusStPtr   : DTC status.               */
/* Return Value  | boolean                                                  */
/*               |              execute healing or not.                     */
/*               |                  TRUE    :   execute healing.            */
/*               |                  FALSE   :   no execute healing.         */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Control_ProcessHealing
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,            /* [PRMCHK:CALLER] */
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
)
{
    VAR( Dem_u08_HealingCounterType, AUTOMATIC ) healingCounter;
    VAR( Dem_u08_HealingCounterType, AUTOMATIC ) healingCounterThreshold;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetHealingCounterFromTmp;
    VAR( boolean, AUTOMATIC ) execHealing;
    VAR( boolean, AUTOMATIC ) isActiveFault;
    VAR( boolean, AUTOMATIC ) isWIRIndicator;
#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isMILIndicator;
#endif  /*   ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )        */

    execHealing =   (boolean)FALSE;

    /* Indicator Flag is ON                                 */
    if( ( OldDTCStatusStPtr->ExtendDTCStatus & DEM_DTCSTATUSEX_STATUS_INDICATOR ) == DEM_DTCSTATUSEX_STATUS_INDICATOR )
    {
        /*  get configuration mode.                         */

        /*  if Indicator use, increment Healing counter.    */
        isActiveFault    =   Dem_CfgInfoPm_GetIsActiveFault( EventStrgIndex );                          /* [GUDCHK:CALLER]EventStrgIndex */
        if( isActiveFault == (boolean)TRUE )
        {
            healingCounterThreshold         =   Dem_CfgInfoPm_GetHealingThreshold( EventStrgIndex );    /* [GUDCHK:CALLER]EventStrgIndex */
            retGetHealingCounterFromTmp     =   Dem_Data_GetHealingCounterFromTmp( &healingCounter );
            if( retGetHealingCounterFromTmp == DEM_IRT_OK )
            {
                if( healingCounter < DEM_HEALING_COUNT_MAX_VALUE )
                {
                    healingCounter++;
                }
                else
                {
                    /* No process */
                }

                if( healingCounter >= healingCounterThreshold )
                {
                    /*  Reset IndicatorStatus bit.          */
                    NewDTCStatusStPtr->ExtendDTCStatus  =  Dem_DTC_ExDTC_ResetIndicatorBit( NewDTCStatusStPtr->ExtendDTCStatus );
                    NewDTCStatusStPtr->ExtendDTCStatus2 =  Dem_DTC_ExDTC2_ResetContinuousMIHistoryBit( NewDTCStatusStPtr->ExtendDTCStatus2 );

                    isWIRIndicator  =   Dem_CfgInfoPm_ChkDTCCls_WIRbitOFFAtHealing( EventStrgIndex );   /* [GUDCHK:CALLER]EventStrgIndex */
                    if( isWIRIndicator == (boolean)TRUE )
                    {
                        NewDTCStatusStPtr->DTCStatus    = Dem_DTC_ResetWIRStatusBit( NewDTCStatusStPtr->DTCStatus );
                    }

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) /*  [FuncSw]    */
                    /*  if MIL use, clear MIL order list.   */
                    isMILIndicator  =   Dem_CfgInfoPm_ChkDTCCls_HasContinuousMI( EventStrgIndex );      /* [GUDCHK:CALLER]EventStrgIndex */
                    if( isMILIndicator == (boolean)TRUE )
                    {
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
                        if ( ( OldDTCStatusStPtr->ExtendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY ) == DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY )
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
                        {
                            Dem_Data_ClearMILOccurrenceOrderInfo();
                        }
                    }
#endif  /*   ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )        */

                    execHealing =   (boolean)TRUE;

                    healingCounter  = DEM_HEALING_COUNT_INITIAL_VALUE;
                }
                else
                {
                    /* No process */
                }

                Dem_Data_SetHealingCounterToTmp( healingCounter );
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return execHealing;
}

#endif  /* ( DEM_INDICATOR_USE == STD_ON )    */

#if ( DEM_INDICATOR_USE == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Control_ProcessHealing                               */
/* Description   | Recovery process of MIL lighting state.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex : Event index.                       */
/*               | [in] OldDTCStatusStPtr  :   DTC status.                  */
/*               | [in/out] NewDTCStatusStPtr   : DTC status.               */
/* Return Value  | boolean                                                  */
/*               |              execute healing or not.                     */
/*               |                  FALSE   :   no execute healing.         */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Control_ProcessHealing
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                /* MISRA DEVIATION */
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,  /* MISRA DEVIATION */
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr        /* MISRA DEVIATION */
)
{
    /*  This is empty function for function switching.  */
    return (boolean)FALSE;
}

#endif /* DEM_INDICATOR_USE -STD_OFF- */

/*--------------------------------------------------------------------------*/
/* Unit Internal functions(data)                                            */
/*--------------------------------------------------------------------------*/

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-0-1         :2019-10-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
