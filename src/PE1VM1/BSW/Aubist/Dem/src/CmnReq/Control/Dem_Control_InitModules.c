/* Dem_Control_InitModules_c(v5-9-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_InitModules/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_CmnLib_DataAvl.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_CmnLib_TSFFD.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Control_WWHOBD.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Pm_StoredData.h"
#include "../../../inc/Dem_Pm_Ind.h"
#include "../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../inc/Dem_Pm_PID.h"
#include "../../../inc/Dem_Pm_DTR.h"
#include "../../../inc/Dem_Pm_IUMPR.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_Pm_PreFFD.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_Pm_OccrDTC.h"
#include "../../../inc/Dem_Pm_AltIUMPR.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../inc/Dem_Udm_Control.h"

#include "Dem_Control_cmn_local.h"

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

/****************************************************************************/
/* Function Name | Dem_Control_Init_DemInit                                 */
/* Description   | Initialize sub-modules at Dem_Init.                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | this function is under next conditions.                  */
/*               |   - BEFORE  record check completed.                      */
/*               |   - BEFORE generate of fault order lists.                */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_Init_DemInit
( void )
{
    /* Internal variable initialization */
    Dem_Control_InitAsyncReq();
    Dem_Control_Clear_ClearDTCInfo();
    Dem_Control_InitDTCSettingStatus();
    Dem_Control_InitDTCRecordUpdateInfo();
    Dem_Control_InitDTCStoredDataStatus();
    Dem_Control_InitInfoForOpCycleStart();

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_Control_InitPIDInfo();
#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON ) */

#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_Control_InitIUMPRInfo();
#endif  /*   ( DEM_IUMPR_SUPPORT == STD_ON )    */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_Control_InitIndMI();
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    /* Initialization of each unit */
    Dem_Event_InitQualification();
    Dem_DataCtl_Init();

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_DTC_InitForPFC();
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )            */

#if ( DEM_PID_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_PID_Init();
#endif  /*   ( DEM_PID_SUPPORT == STD_ON )          */

#if ( DEM_TSFF_SUPPORT == STD_ON )  /*  [FuncSw]    */
    Dem_TSFFD_Init();
#endif  /*   ( DEM_TSFF_SUPPORT == STD_ON )         */

    Dem_StoredData_Init();

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_OccrDTC_Init();
#endif  /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )            */

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
    Dem_MonSts_Init();
#endif  /*   ( DEM_TRIGGER_FIM_REPORTS == STD_ON )  */

#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_IUMPR_Init();
#endif  /*   ( DEM_IUMPR_SUPPORT == STD_ON )    */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_Init();
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_UdmControl_Init();
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */

#if ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_OpCycle_ClearProgressEngine1000RPM();
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )                          */


    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_Init_AfterRecordCheckComplete                */
/* Description   | Initialize sub-modules after record check completed.     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | this function is under next conditions.                  */
/*               |   - AFTER  record check completed.                       */
/*               |   - BEFORE generate of fault order lists.                */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/*   v5-7-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_Init_AfterRecordCheckComplete
( void )
{
    Dem_Data_SetNumOfFaultAndFFD();

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_Event_InitQualification_AfterRecordCheckComplete();
#endif  /*  ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )        */

    /* Call Init of DataCtl after consistency check is finished */
    Dem_DataCtl_Init_AfterRecordCheckComplete();

#if ( DEM_TSFF_SUPPORT == STD_ON )    /* [FuncSw] */
    /* Initializes time-series freeze frame related  memory. */
    Dem_Data_InitTSFFD_AfterRecordCheckComplete();
#endif  /*  ( DEM_TSFF_SUPPORT == STD_ON )  */

#if ( DEM_DTR_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_DTR_Init_AfterRecordCheckComplete();
#endif  /* ( DEM_DTR_SUPPORT == STD_ON )    */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_UdmControl_Init_AfterRecordCheckComplete();
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    /* follow the order, Generate IndMIIndexList -> Restart operationcycle(AutoStart). */
    Dem_IndMI_Init_AfterRecordCheckComplete();
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_Init_GenFaultOrderLists                      */
/* Description   | generate fault order lists.                              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_Init_GenFaultOrderLists
( void )
{
    /*  generate order list.              */
    Dem_Data_GenerateFaultOrderList();

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /* [FuncSw] */
    Dem_Data_GenerateConfirmedFaultOrderList();
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )      */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_Data_GenerateMILFaultOrderList();
#endif  /*   ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )        */

    Dem_Data_ClearSearchFFDIndex();

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_UdmControl_GenerateRecordInfo();
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_Init_AfterOrderListGenAndNoExecEndJobOfOpCycRestart      */
/* Description   | Initializes Dem_Control(after fault orderlist generate completed.)   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | this function is under next conditions.                  */
/*               |   - AFTER  generate of fault order lists.                */
/*               |   - BEFORE exec exit job of operation cycle restart.     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_Init_AfterOrderListGenAndNoExecEndJobOfOpCycRestart
( void )
{
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
    /* In  [OperationCycle auto restart : exec end job], exec B1Record Update. */
    /* follow the order, Generate IndMIIndexList -> B1Record Update. */
    Dem_IndMI_Init_AfterOrderListGenerateComplete();
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_Init_AfterOrderListGenerateComplete          */
/* Description   | Initializes Dem_Control(after fault orderlist generate completed.)   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | this function is under next conditions.                  */
/*               |   - AFTER  generate of fault order lists.                */
/*               |   - AFTER exec exit job of operation cycle restart.      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_Init_AfterOrderListGenerateComplete
( void )
{
#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_PID_ConfirmedDTCClear();                           /* [UpdRec]PID */
#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )             */

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_OccrDTC_Init_AfterOrderListGenerateComplete();     /* [UpdRec]OccrDTC */
#endif  /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )             */

    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
