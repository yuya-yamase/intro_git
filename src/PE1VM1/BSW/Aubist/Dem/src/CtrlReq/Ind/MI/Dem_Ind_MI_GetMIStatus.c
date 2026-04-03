/* Dem_Ind_MI_GetMIStatus_c(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Ind_MI_GetMIStatus/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_CmnLib_Control.h"
#include "../../../../inc/Dem_Pm_DataAvl.h"
#include "../../../../inc/Dem_Pm_Ind.h"
#include "../../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../../inc/Dem_Pm_Misfire.h"
#include "../../../../inc/Dem_Rc_DataMng.h"

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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_IndMI_GetMILStatus                                   */
/* Description   | Get MIL Status .                                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] IndicatorStatusPtr                                 */
/*               |        Pointer to data for set Indicator Status.         */
/*               |        This pointer is pointing to                       */
/*               |        Dem_GetIndicatorStatus 2nd parameter.             */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/*               |          DEM_INDICATOR_BLINKING   : Indicator Blinking   */
/*               |          DEM_INDICATOR_BLINK_CONT : Indicator On and Bl- */
/*               |                                     inking               */
/*               |          DEM_INDICATOR_SHORT      : Indicator Short      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMI_GetMILStatus
(
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( boolean, AUTOMATIC ) milStatus;
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) indicatorStatus;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_MisfireIndStatusType, AUTOMATIC ) retGetMILStatus;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    milStatus   =   Dem_Data_GetMILStatus_NormalEvent();

    indicatorStatus =   DEM_INDICATOR_OFF;
    if ( milStatus == (boolean)TRUE )
    {
        indicatorStatus =   DEM_INDICATOR_CONTINUOUS;
    }

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    availableMisfireKind    =   Dem_DataAvl_GetMisfireCylDTCAvailable();
    retGetMILStatus         =   Dem_Misfire_GetMILStatus( availableMisfireKind );

    if( ( retGetMILStatus & DEM_MISFIRE_IND_CONTINUOUS ) == DEM_MISFIRE_IND_CONTINUOUS )
    {
        indicatorStatus     =   DEM_INDICATOR_CONTINUOUS;
    }

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   /*  [FuncSw]    */
    /*  check blinking status       */
    if( ( retGetMILStatus & DEM_MISFIRE_IND_BLINKING ) == DEM_MISFIRE_IND_BLINKING )
    {
        if( indicatorStatus == DEM_INDICATOR_CONTINUOUS )
        {
            indicatorStatus = DEM_INDICATOR_BLINK_CONT;
        }
        else
        {
            indicatorStatus = DEM_INDICATOR_BLINKING;
        }
    }
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )         */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    *IndicatorStatusPtr = indicatorStatus;

    return DEM_IRT_OK;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_GetMILStatusByEventStrgIndex                   */
/* Description   | Get MIL Status by Event.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        Event index.                                      */
/* Parameters    | [out] IndicatorStatusPtr                                 */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/*               |          DEM_INDICATOR_BLINKING   : Indicator Blinking   */
/*               |          DEM_INDICATOR_BLINK_CONT : Indicator On and Bl- */
/*               |                                     inking               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMI_GetMILStatusByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) eventOBDKind;
    VAR( boolean, AUTOMATIC ) isMILIndicator;
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    retVal = DEM_IRT_NG;

    *IndicatorStatusPtr = DEM_INDICATOR_OFF;

    /* Waits to finish the exclusive section in the DemMainFunction context. */
    SchM_Enter_Dem_EventMemory();
    SchM_Exit_Dem_EventMemory();

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    eventKind = Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );                     /* [GUD:RET:Not DEM_EVTKIND_TYPE_NON_OBD_EVENT] EventStrgIndex  */
    if( ( eventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
    {
        /*  check MIL status with blinking.       */
        Dem_Misfire_GetIndStatusByEventStrgIndex_CAT( EventStrgIndex, IndicatorStatusPtr );         /* [GUD]EventStrgIndex */
        retVal = DEM_IRT_OK;
    }
    else
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )         */
    {
        eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );       /* [GUD:RET:TRUE] EventStrgIndex */
        if ( eventOBDKind == (boolean)TRUE )    /*  OBD     */
        {
            /* check Indicator type */
            isMILIndicator  =   Dem_CfgInfoPm_ChkDTCCls_HasMILInd( EventStrgIndex );        /* [GUD]EventStrgIndex */
            if( isMILIndicator == (boolean)TRUE )
            {
                statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;
                (void)Dem_DataMngC_GetER_StatusOfDTC( EventStrgIndex, &statusOfDTC );       /* no return check required */
                if( ( statusOfDTC & DEM_UDS_STATUS_WIR ) != DEM_DTCSTATUS_BYTE_ALL_OFF )
                {
                    *IndicatorStatusPtr = DEM_INDICATOR_CONTINUOUS;
                }
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_OFF )      */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
