/* Dem_Ind_MI_CtrlShortMI_WWH_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Ind_MI_CtrlShortMI_WWH/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )

#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../inc/Dem_Pm_Ind.h"
#include "../../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../../inc/Dem_Rc_DataMng.h"
#include "../../../../inc/Dem_CmnLib_DTC_DTCStatus.h"

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

static FUNC( void, DEM_CODE ) Dem_IndMI_SetWIRStatusForShortMIEvent
( void );

static FUNC( void, DEM_CODE ) Dem_IndMI_ResetWIRStatusForShortMIEvent
( void );

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>
static VAR( Dem_u08_DemBooleanType, DEM_VAR_NO_INIT )  Dem_IndMI_SetWIRAtShortMIFlg;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_IndMI_Init_AfterOrderListGenerateComplete            */
/* Description   | Init Dem_IndMI                                           */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMI_Init_AfterOrderListGenerateComplete
( void )
{
    Dem_IndMI_SetWIRStatusForShortMIEvent();
    Dem_IndMI_SetWIRAtShortMIFlg = (Dem_u08_DemBooleanType)DEM_BOOLEAN_TRUE;

    Dem_IndMI_GenerateEventStrgIndexToIndMIIndexList();

    return;
}


/****************************************************************************/
/* Function Name | Dem_IndMI_SetMILAtShortMI                                */
/* Description   | set MIL at short MI.                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] MILStatus : MIL status.                             */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IndMI_SetMILAtShortMI
(
    VAR( Dem_u08_DemBooleanType, AUTOMATIC ) MILStatus
)
{
    if ( MILStatus != Dem_IndMI_SetWIRAtShortMIFlg )
    {
        if ( MILStatus == (Dem_u08_DemBooleanType)DEM_BOOLEAN_TRUE )
        {
            /* For Short-MI Events, Bit7 turns ON */
            Dem_IndMI_SetWIRStatusForShortMIEvent();
        }
        else
        {
            /* For Short-MI Events, Bit7 turns OFF */
            Dem_IndMI_ResetWIRStatusForShortMIEvent();
        }
    }

    Dem_IndMI_SetWIRAtShortMIFlg = MILStatus;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_GetMILAtShortMIFlg                             */
/* Description   | get Dem_IndMI_SetWIRAtShortMIFlg value.                  */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | Dem_u08_DemBooleanType : Dem_IndMI_SetWIRAtShortMIFlg    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_DemBooleanType, DEM_CODE ) Dem_IndMI_GetMILAtShortMIFlg
( void )
{
    return Dem_IndMI_SetWIRAtShortMIFlg;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_SetWIRStatusForShortMIEvent                    */
/* Description   | StatusOfDTC Bit7 turns on for all short-MI events        */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IndMI_SetWIRStatusForShortMIEvent
( void )
{
    VAR( boolean, AUTOMATIC ) OrderExistFlag;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC_Old;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC_New;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( boolean, AUTOMATIC ) isContMIorShortMI;

    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;

    eventStorageNum = Dem_CfgInfoPm_GetMaxNumberOfOBDEvent(); /*  event index check  : range of OBD event(may include nonOBD event).  */

    for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < failRecordNum; orderListIndex++ )
    {
        eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
        statusOfDTC_Old = DEM_DTCSTATUS_BYTE_ALL_OFF;

        Dem_Data_GetConfirmedOrderEventStrgIndex( orderListIndex, &eventStrgIndex, &faultIndex, &statusOfDTC_Old, &OrderExistFlag );

        if( OrderExistFlag == (boolean)TRUE )
        {
            /*  if eventStrgIndex is invalid or nonOBD range, skip priority check.      */
            if( eventStrgIndex < eventStorageNum )      /* [GUD:if]eventStrgIndex */
            {
                isContMIorShortMI = Dem_IndMI_IsContMIorShortMI_ByEventStrgIndex( eventStrgIndex ); /* [GUD]eventStrgIndex */

                if ( isContMIorShortMI == (boolean)TRUE )
                {
                    statusOfDTC_New = Dem_DTC_SetWIRStatusBit( statusOfDTC_Old );

                    if ( statusOfDTC_Old != statusOfDTC_New )
                    {
                        Dem_DataMngC_SetER_StatusOfDTC( eventStrgIndex, statusOfDTC_New );      /* [GUD]eventStrgIndex */
                    }
                }
            }
        }
        else
        {
            break;
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_IndMI_ResetWIRStatusForShortMIEvent                  */
/* Description   | StatusOfDTC Bit7 turns off for all short-MI events       */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IndMI_ResetWIRStatusForShortMIEvent
( void )
{
    VAR( boolean, AUTOMATIC ) OrderExistFlag;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_IndicatorStatusType, AUTOMATIC ) indicatorStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC_Old;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC_New;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;
    eventStorageNum = Dem_CfgInfoPm_GetMaxNumberOfOBDEvent(); /*  event index check  : range of OBD event(may include nonOBD event).  */

    for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < failRecordNum; orderListIndex++ )
    {
        eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
        statusOfDTC_Old = DEM_DTCSTATUS_BYTE_ALL_OFF;

        Dem_Data_GetConfirmedOrderEventStrgIndex( orderListIndex, &eventStrgIndex, &faultIndex, &statusOfDTC_Old, &OrderExistFlag );

        if( OrderExistFlag == (boolean)TRUE )
        {
            /*  if eventStrgIndex is invalid or nonOBD range, skip priority check.      */
            if( eventStrgIndex < eventStorageNum )      /* [GUD:if]eventStrgIndex */
            {
                (void)Dem_IndMI_GetMILStatusByEventStrgIndex( eventStrgIndex, &indicatorStatus ); /* no return check required *//* [GUD]eventStrgIndex */

                if ( indicatorStatus == DEM_INDICATOR_SHORT )
                {
                    statusOfDTC_New = Dem_DTC_ResetWIRStatusBit( statusOfDTC_Old );

                    if ( statusOfDTC_Old != statusOfDTC_New )
                    {
                        Dem_DataMngC_SetER_StatusOfDTC( eventStrgIndex, statusOfDTC_New );
                    }
                }
            }
        }
        else
        {
            break;
        }
    }
    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )      */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
