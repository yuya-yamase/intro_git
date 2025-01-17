/* Dem_Ind_c(v5-5-0)                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Ind/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Indicator_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnIf_Ind.h"
#include "../../../inc/Dem_Pm_Ind.h"
#include "Dem_Ind_cmn_local.h"

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
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_Ind_GetIndicatorStatus                               */
/* Description   | Get Indicator Status by Indicator Id.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in]  IndicatorId :                                      */
/*               |        Indicator Id.                                     */
/*               | [out] IndicatorStatusPtr                                 */
/*               |          DEM_INDICATOR_OFF        : Indicator Off        */
/*               |          DEM_INDICATOR_CONTINUOUS : Indicator On         */
/*               |          DEM_INDICATOR_BLINKING   : Indicator Blinking   */
/*               |          DEM_INDICATOR_BLINK_CONT : Indicator On and Bl- */
/*               |                                     inking               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Success.                             */
/*               |        DEM_IRT_NG : Failed.                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetIndicatorStatus
(
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) IndicatorId,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) milIndicatorRef;
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) ecuIndicatorRef;

    milIndicatorRef = Dem_MILIndicatorRef;
    ecuIndicatorRef = Dem_EcuIndicatorRef;

    if( IndicatorId == ecuIndicatorRef )
    {
        *IndicatorStatusPtr = Dem_Ind_GetIndicatorStatusByWIRStatus();

        retVal = DEM_IRT_OK;
    }
    else if ( IndicatorId == milIndicatorRef )
    {
        /*--------------------------------------------------------------------------*/
        /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
        /* These are the reasons why this function needs to get exclusive.          */
        /*  - This function call [DataMng] function directory.                      */
        /*  - This function called from SW-C/Dcm context.                           */
        /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
        SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
        SchM_Exit_Dem_EventMemory();
        /*--------------------------------------------------------------------------*/
        retVal = Dem_Ind_GetMILStatus( IndicatorStatusPtr );
    }
    else
    {
        retVal = Dem_Ind_GetUserDefinedIndicatorStatus( IndicatorId, IndicatorStatusPtr );
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Ind_GetIndicatorStatusByEventCtrlIndex               */
/* Description   | Get Indicator Status by Indicator Id.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        Event index.                                      */
/*               | [in]  IndicatorId :                                      */
/*               |        Indicator Id.                                     */
/*               | [out] IndicatorStatusPtr                                 */
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
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Ind_GetIndicatorStatusByEventCtrlIndex
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) IndicatorId,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) milIndicatorRef;
    VAR( Dem_u08_IndicatorIdType, AUTOMATIC ) ecuIndicatorRef;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    VAR( Dem_u08_MemoryKindType, AUTOMATIC ) memKind;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

    milIndicatorRef = Dem_MILIndicatorRef;
    ecuIndicatorRef = Dem_EcuIndicatorRef;

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    /* check eventIndex kind. */
    memKind = Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex( EventCtrlIndex );
    if( memKind != DEM_MEMKIND_PRIMARY )
    {
        /*  userDefinedMemory       */
        if( IndicatorId == ecuIndicatorRef )
        {
            retVal = DEM_IRT_NG;
        }
        else if ( IndicatorId == milIndicatorRef )
        {
            retVal = DEM_IRT_NG;
        }
        else
        {
            retVal = Dem_Ind_GetUserDefinedIndicatorStatusByEventCtrlIndex( EventCtrlIndex, IndicatorId, IndicatorStatusPtr );
        }
    }
    else
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */
    {
        /*  primaryMemory.  */
        if( IndicatorId == ecuIndicatorRef )
        {
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                        /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
            retVal =   Dem_Ind_GetIndicatorStatusByWIRStatusAndEventStrgIndex( eventStrgIndex, IndicatorStatusPtr );
        }
        else if ( IndicatorId == milIndicatorRef )
        {
            eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                        /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
            /*--------------------------------------------------------------------------*/
            /* Need to get exclusive [SchM_Enter_Dem_EventMemory].                      */
            /* These are the reasons why this function needs to get exclusive.          */
            /*  - This function call [DataMng] function directory.                      */
            /*  - This function called from SW-C/Dcm context.                           */
            /*  Waits to finish the exclusive section in the Dem_MainFunction context.  */
            SchM_Enter_Dem_EventMemory();    /* waits completion of updating Diag record data by Dem_MainFunction.      */
            SchM_Exit_Dem_EventMemory();
            /*--------------------------------------------------------------------------*/
            retVal = Dem_Ind_GetMILStatusByEventStrgIndex( eventStrgIndex, IndicatorStatusPtr );
        }
        else
        {
            retVal = Dem_Ind_GetUserDefinedIndicatorStatusByEventCtrlIndex( EventCtrlIndex, IndicatorId, IndicatorStatusPtr );
        }
    }
    return retVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
