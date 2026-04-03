/* Dem_Control_OpCycleUpdCommon_c(v5-7-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_OpCycleUpdCommon/CODE                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_OpCycle_Cfg.h"
#include "../../../cfg/Dem_WWHObd_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../inc/Dem_Rc_OpCycleMng.h"
#include "../../../inc/Dem_CmnLib_DataElement.h"
#include "../../../inc/Dem_Pm_Ind_MI.h"

#include "Dem_Control_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define DEM_WWHOBD_DATAPOS0                         ((uint8)0U)
#define DEM_WWHOBD_DATAPOS1                         ((uint8)1U)
#define DEM_WWHOBD_CALCULATION_DATASIZE_TIMESES     ((uint8)2U)
#define DEM_WWHOBD_DATA_BITSHIFT_8                  ((Dem_u16_WWHOBDTimeAgingCounterType)8U)

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

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
static VAR( Dem_u16_WWHOBDTimeAgingCounterType, DEM_VAR_NO_INIT )      Dem_Control_TimeSinceEngineStartSinceLastDCY;
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Control_UpdateEventMemEntryByOpCycle_PrimaryMemory   */
/* Description   | update EventMemoryEntry of operation cycle .             */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventPos                                           */
/*               |                                                          */
/*               | [in] HealingAgingCycleFlag :                             */
/*               |              check HealingAgingCycle or not.             */
/*               | [in] FailureCycleFlag :                                  */
/*               |              check FailureCycle or not.                  */
/*               | [out] NeedGenOrderListPtr :                              */
/*               |              need GenOrderList or not.                   */
/*               |                  TRUE    :   need generate .             */
/*               |                  FALSE   :   no need generate .          */
/*               | [out] ExecHealingPtr :                                   */
/*               |              execute healing or not.                     */
/*               |                  TRUE    :   execute healing.            */
/*               |                  FALSE   :   no execute healing.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_UpdateEventMemEntryByOpCycle_PrimaryMemory
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,                    /* [PRMCHK:CALLER] */
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
)
{
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) retCheckSpecificEvent;

    /*  Primary memory.     */
    retCheckSpecificEvent = Dem_CfgInfoPm_CheckEventKindOfSpecific_ByEvtCtrlIdx( (Dem_u16_EventCtrlIndexType)EventPos );
    if( retCheckSpecificEvent == (boolean)TRUE )
    {
        Dem_Control_UpdateSpecificEventMemoryEntryByOpCycle( EventPos, HealingAgingCycleFlag, FailureCycleFlag, NeedGenOrderListPtr, ExecHealingPtr  );     /* [GUDCHK:CALLER]EventPos *//* [UpdRec]AltIUMPR */
    }
    else
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )   */
    {
        Dem_Control_NormalEventMemoryEntryByOpCycle( EventPos, HealingAgingCycleFlag, FailureCycleFlag, NeedGenOrderListPtr, ExecHealingPtr  );             /* [GUDCHK:CALLER]EventPos *//* [UpdRec]AltIUMPR */
    }

    Dem_Event_ClearTargetQualificationInfoAtOpCycUpd_NotTestedInCycle( (Dem_u16_EventCtrlIndexType)EventPos, FailureCycleFlag );        /* [GUDCHK:CALLER]EventPos *//* [UpdRec]AltIUMPR */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_UpdEvtMemEntryOfTmp_AtOpcycUpdate            */
/* Description   | Delete of the event memory information.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventKindPattern : event kind.                      */
/*               | [in] EventStrgIndex                                      */
/*               | [in] PendingRecoveryExecFlag                             */
/*               | [in] AgingExecFlag                                       */
/*               | [in] DTCStatus                                           */
/*               | [out] NeedGenOrderListPtr                                */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_UpdEvtMemEntryOfTmp_AtOpcycUpdate
(
    VAR( Dem_u08_EventKindPtnType, AUTOMATIC ) EventKindPattern,    /* MISRA DEVIATION */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,    /* MISRA DEVIATION *//* [PRMCHK:CALLER] */
    VAR( boolean, AUTOMATIC ) PendingRecoveryExecFlag,
    VAR( boolean, AUTOMATIC ) AgingExecFlag,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr
)
{
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    VAR( boolean, AUTOMATIC ) useB1Counter;
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    /*  update event memory entry   */
    if ( PendingRecoveryExecFlag == (boolean)TRUE )
    {
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
        /* B1Counter Hold */
        useB1Counter  =   Dem_CfgInfoPm_ChkDTCCls_UseB1Counter( EventStrgIndex );   /* [GUDCHK:CALLER]EventStrgIndex */
        if ( useB1Counter == (boolean)TRUE )
        {
            if ( ( DTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )
            {
                Dem_IndMI_HoldB1Counter( EventStrgIndex );      /* [GUDCHK:CALLER]EventStrgIndex */
            }
        }
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

        if ( AgingExecFlag == (boolean)TRUE )
        {
            /*----------------------------------*/
            /*  PendingOFF and Aging            */
            /*----------------------------------*/
            /*  bit2 : 1->0     bit3 : 1->0     */
            /*----------------------------------*/
            Dem_Data_UpdEvtMemEntryOfTmp_PendingOFFAndAgingEvent();
            *NeedGenOrderListPtr   =   (boolean)TRUE;
        }
        else
        {
            /*----------------------------------*/
            /*  PendingOFF                      */
            /*----------------------------------*/
            /*  bit2 : 1->0     bit3 : -        */
            /*----------------------------------*/
            Dem_Data_UpdEvtMemEntryOfTmp_PendingOFFEvent( DTCStatus );
            *NeedGenOrderListPtr   =   (boolean)TRUE;
        }
    }
    else
    {
        if ( AgingExecFlag == (boolean)TRUE )
        {
            /*----------------------------------*/
            /*  Aging                           */
            /*----------------------------------*/
            /*  bit2 : -,       bit3 : 1->0     */
            /*----------------------------------*/
            Dem_Data_UpdEvtMemEntryOfTmp_AgingEvent( DTCStatus );
            *NeedGenOrderListPtr   =   (boolean)TRUE;
        }
        else
        {
            /*----------------------------------*/
            /*  no change                       */
            /*----------------------------------*/
            /*  bit2 : -        bit3 : -        */
            /*----------------------------------*/
            Dem_Data_UpdateEventMemoryEntryFromTmp();
            *NeedGenOrderListPtr   =   (boolean)FALSE;
        }
    }


#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    if ( EventKindPattern == DEM_EVTKINDPTN_PRIMEM_SPECIFIC )
    {
        Dem_DTC_UpdateSpecificPermanentMemoryEntryToTmp();
    }
    else
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */
    {
        /*  DEM_EVTKINDPTN_PRIMEM_NORMAL          */
        Dem_DTC_UpdatePermanentMemoryEntryToTmp();
    }
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )      */

    return;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_JudgeAndGetTimeSinceEngineStartSinceLastDCY  */
/* Description   | Judge and get time since engine start since last DCY.    */
/* Preconditions | none                                                     */
/* Parameters    | [in] ThisCycleKindIndex :                                */
/*               |              This operation cycle kind index             */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-6-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_JudgeAndGetTimeSinceEngineStartSinceLastDCY
(
    VAR( Dem_u08_OpCycleKindIndexType, AUTOMATIC ) ThisCycleKindIndex
)
{
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;
    VAR( Dem_u16_DataElementClassIndexType, AUTOMATIC ) dataElementClassIndex;
    VAR( Dem_u16_DataElementClassIndexType, AUTOMATIC ) elementClassTableNum;
    P2CONST( AB_83_ConstV Dem_DataElementClassType, AUTOMATIC, DEM_CONFIG_DATA ) dataElementClassPtr;
    VAR( uint8, AUTOMATIC ) dataBuffer[DEM_WWHOBD_CALCULATION_DATASIZE_TIMESES];

    Dem_Control_TimeSinceEngineStartSinceLastDCY = (Dem_u16_WWHOBDTimeAgingCounterType)0U;

    if ( ( ThisCycleKindIndex == DEM_OPCYCKIND_THISCYCLE_WARMUP ) || ( ThisCycleKindIndex == DEM_OPCYCKIND_THISCYCLE_DCY ) )
    {
        elementClassTableNum  = Dem_DataElementNum;
        dataElementClassIndex = Dem_WWHOBD_TimeSinceEngineStartSinceLastDCY_FuncIndex;
        if( dataElementClassIndex < elementClassTableNum )                                                                          /* [GUD:if]dataElementClassIndex */
        {
            dataElementClassPtr = &Dem_DataElementClassTable[dataElementClassIndex];                                                /* [GUD]dataElementClassIndex */
            resultOfCallback = Dem_DataElement_ReadData( dataElementClassPtr, dataBuffer , DEM_MONITORDATA_OTHER );                 /* [GUD]dataElementClassIndex */
            if( resultOfCallback == (Std_ReturnType)E_OK )
            {
                Dem_Control_TimeSinceEngineStartSinceLastDCY = ( Dem_u16_WWHOBDTimeAgingCounterType )(((( Dem_u16_WWHOBDTimeAgingCounterType)dataBuffer[DEM_WWHOBD_DATAPOS0]) << DEM_WWHOBD_DATA_BITSHIFT_8 ) | (( Dem_u16_WWHOBDTimeAgingCounterType)dataBuffer[DEM_WWHOBD_DATAPOS1] ));/* [ARYCHK] DEM_WWHOBD_CALCULATION_DATASIZE_TIMESES / 1 / DEM_WWHOBD_DATAPOS0 *//* [ARYCHK] DEM_WWHOBD_CALCULATION_DATASIZE_TIMESES / 1 / DEM_WWHOBD_DATAPOS1 */
            }
            else
            {
                /* No process */
            }
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetTimeSinceEngineStartSinceLastDCY          */
/* Description   | Get time since engine start since last DCY               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_WWHOBDTimeAgingCounterType                       */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u16_WWHOBDTimeAgingCounterType, DEM_CODE ) Dem_Control_GetTimeSinceEngineStartSinceLastDCY
( void )
{
    return Dem_Control_TimeSinceEngineStartSinceLastDCY;
}
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
