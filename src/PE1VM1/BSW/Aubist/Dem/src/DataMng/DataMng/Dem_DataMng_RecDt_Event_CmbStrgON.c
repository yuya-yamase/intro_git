/* Dem_DataMng_RecDt_Event_CmbStrgON_c(v5-9-0)                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_DataMng_RecDt_Event_CmbStrgON_c/CODE              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "Dem_DataMng_local.h"

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

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_DataMng_SetPassedBitmap
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                /* [PRMCHK:CALLER] */
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) PassedBitmapIndex,       /* [PRMCHK:CALLER] */
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) PassedBitmapData
);
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Const                                                                    */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMngC_GetER_PassedBitmap_InEvtStrgGrp             */
/* Description   | set data to PassedBitmapInEvtStrgGrp[].                  */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] PassedBitmapIndex    : bitmap buffer index.         */
/*               | [out] PassedBitmapDataPtr : bitmap value.                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndex                      */
/* VariableGuard | [GUD:RET:DEM_IRT_OK] PassedBitmapIndex                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetER_PassedBitmap_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                /* [PRMCHK:CALLER] */
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) PassedBitmapIndex,
    P2VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC, AUTOMATIC ) PassedBitmapDataPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) eventCtrlBitmapIndexMax;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    eventCtrlBitmapIndexMax = Dem_CmbEvent_EventCtrlBitmapIndexMaxNum;
    retVal = DEM_IRT_NG;

    if( EventStrgIndex < eventStorageNum )                                          /* [GUD:if]EventStrgIndex */
    {
        if( PassedBitmapIndex < eventCtrlBitmapIndexMax )                                /* [GUD:if]PassedBitmapIndex */
        {
            *PassedBitmapDataPtr    =   Dem_EventRecordList[EventStrgIndex].PassedBitmapInEvtStrgGrp[ PassedBitmapIndex ];  /* [GUD]EventStrgIndex *//* [GUD]PassedBitmapIndex */
            retVal = DEM_IRT_OK;
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataMngC_SetER_PassedBitmap_InEvtStrgGrp             */
/* Description   | set data to PassedBitmapInEvtStrgGrp[].                  */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] PassedBitmapIndex : bitmap buffer index.            */
/*               | [in] PassedBitmapData  : bitmap value.                   */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndex                      */
/* VariableGuard | [GUD:RET:DEM_IRT_OK] PassedBitmapIndex                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_PassedBitmap_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) PassedBitmapIndex,
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) PassedBitmapData
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) eventCtrlBitmapIndexMax;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    eventCtrlBitmapIndexMax = Dem_CmbEvent_EventCtrlBitmapIndexMaxNum;

    if( EventStrgIndex < eventStorageNum )                                          /* [GUD:if]EventStrgIndex */
    {
        if( PassedBitmapIndex < eventCtrlBitmapIndexMax )                                /* [GUD:if]PassedBitmapIndex */
        {
            Dem_DataMng_SetPassedBitmap( EventStrgIndex, PassedBitmapIndex, PassedBitmapData ); /* [GUD]EventStrgIndex *//* [GUD]PassedBitmapIndex */
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_DataMngC_SetER_PassedBitmapAll_InEvtStrgGrp          */
/* Description   | set data to PassedBitmapInEvtStrgGrp[].                  */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] PassedBitmapIndex : bitmap buffer index.            */
/*               | [in] PassedBitmapData  : bitmap value.                   */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] EventStrgIndex                      */
/* VariableGuard | [GUD:RET:DEM_IRT_OK] PassedBitmapIndex                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_SetER_PassedBitmapAll_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) PassedBitmapData
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) eventCtrlBitmapIndexMax;
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) passedBitmapIndex;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;
    if( EventStrgIndex < eventStorageNum )                                                      /* [GUD:if]EventStrgIndex */
    {
        eventCtrlBitmapIndexMax = Dem_CmbEvent_EventCtrlBitmapIndexMaxNum;
        for ( passedBitmapIndex = (Dem_u08_EventCtrlBitmapIndexType)0U; passedBitmapIndex < eventCtrlBitmapIndexMax; passedBitmapIndex++ )  /* [GUD:for]passedBitmapIndex */
        {
            Dem_DataMng_SetPassedBitmap( EventStrgIndex, passedBitmapIndex, PassedBitmapData ); /* [GUD]EventStrgIndex *//* [GUD]passedBitmapIndex */
        }
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_DataMng_SetPassedBitmap                              */
/* Description   | set data to PassedBitmapInEvtStrgGrp[].                  */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] PassedBitmapIndex                                   */
/*               | [in] PassedBitmapData : set value.                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DataMng_SetPassedBitmap
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                /* [PRMCHK:CALLER] */
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) PassedBitmapIndex,       /* [PRMCHK:CALLER] */
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) PassedBitmapData
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindEvent;
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) passedBitmap;

    passedBitmap    =   Dem_EventRecordList[EventStrgIndex].PassedBitmapInEvtStrgGrp[ PassedBitmapIndex ];      /* [GUDCHK:CALLER]EventStrgIndex *//* [GUDCHK:CALLER]PassedBitmapIndex */
    Dem_EventRecordList[EventStrgIndex].PassedBitmapInEvtStrgGrp[ PassedBitmapIndex ]   =   PassedBitmapData;   /* [GUDCHK:CALLER]EventStrgIndex *//* [GUDCHK:CALLER]PassedBitmapIndex */

    if ( passedBitmap != PassedBitmapData )
    {
        /* Change Dem_EventNvMStatus */
        recMngCmnKindEvent = Dem_RecMngCmnKindEvent;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindEvent, ( Dem_u16_RecordIndexType )EventStrgIndex );
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dem_EventMng_SetPassedBitmapData                         */
/* Description   | set data to PassedBitmapInEvtStrgGrp[].                  */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in/out] EventRecordPtr :                                */
/*               |        The specified event record to initialize.         */
/*               | [in] SetValue : set value.                               */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created. based on Dem_EventMng_InitRecord_Padding(). */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_EventMng_SetPassedBitmapData
(
    P2VAR( Dem_EventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) EventRecordPtr,
    VAR( Dem_u08_EventCtrlBitmapType, AUTOMATIC ) PassedBitmapData
)
{
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) idx;
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) eventCtrlBitmapIndexMax;

    eventCtrlBitmapIndexMax = Dem_CmbEvent_EventCtrlBitmapIndexMaxNum;
    for ( idx = (Dem_u08_EventCtrlBitmapIndexType)0U; idx < eventCtrlBitmapIndexMax; idx++ )  /* [GUD:for]idx */
    {
        EventRecordPtr->PassedBitmapInEvtStrgGrp[idx] = PassedBitmapData;   /* [GUD]idx *//* [ARYCHK] DEM_CMBEVT_EVENTCTRLBITMAPINDEX_MAX_NUM / 1 / idx */
    }
    return ;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_EventMng_GetPassedBitmapData                         */
/* Description   | get data to PassedBitmapInEvtStrgGrp[].                  */
/*               |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [out] EventRecordPtr :                                   */
/*               |        The specified event record .                      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created. based on Dem_EventMng_InitRecord_Padding(). */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_EventMng_GetPassedBitmapData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,                /* [PRMCHK:CALLER] */
    P2VAR( Dem_EventRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) EventRecordPtr
)
{
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) idx;
    VAR( Dem_u08_EventCtrlBitmapIndexType, AUTOMATIC ) eventCtrlBitmapIndexMax;

    eventCtrlBitmapIndexMax = Dem_CmbEvent_EventCtrlBitmapIndexMaxNum;
    for ( idx = (Dem_u08_EventCtrlBitmapIndexType)0U; idx < eventCtrlBitmapIndexMax; idx++ )  /* [GUD:for]idx */
    {
        EventRecordPtr->PassedBitmapInEvtStrgGrp[idx] = Dem_EventRecordList[EventStrgIndex].PassedBitmapInEvtStrgGrp[idx];  /* [GUD]idx *//* [GUDCHK:CALLER]EventStrgIndex *//* [ARYCHK] DEM_CMBEVT_EVENTCTRLBITMAPINDEX_MAX_NUM / 1 / idx */
    }
    return ;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */
#endif /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )          */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
