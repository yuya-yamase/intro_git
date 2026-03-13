/* Dem_DTC_PFC_StoreRecord_c(v5-6-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTC_PFC_StoreRecord/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_PFC_SUPPORT == STD_ON )
#include "../../../../inc/Dem_Rc_PFCMng.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../../usr/Dem_PFC_Callout.h"
#include "../../../../inc/Dem_Rc_DataMng.h"

#include "Dem_DTC_PFC_local.h"

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
#define DEM_START_SEC_CODE_TRUST          /*  PreInit section                     */
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE_TRUST           /*  PreInit section                     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DTC_SetPFCRecordWithQualifiedInfo                    */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex                                      */
/*               | [in] EventStrgIndex                                      */
/*               | [in] CycleQualifiedInfo                                  */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC                                              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_SetPFCRecordWithQualifiedInfo
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC ) CycleQualifiedInfo
)
{
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    /*  [FuncSw]    */
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )  /* [FuncSw]     */
    VAR( boolean, AUTOMATIC ) retRegist;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    retRegist   =   (boolean)TRUE;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if ( EventStrgIndex < eventStorageNum )                             /* [GUD:if]EventStrgIndex */
    {
        /*  check output data.                              */
        retRegist   =   Dem_CmbEvt_CheckRegistPFC( EventStrgIndex );    /* [GUD]EventStrgIndex */
    }
    else
    {
        /*   INVALID event is clear PFC record data. so, INVALID event is always regist OK.     */
    }
    if ( retRegist == (boolean)TRUE )
#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )       */
#endif  /*   ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )   */
    {
        Dem_PFCMng_SetPFCRecordData( PFCRecordIndex, EventStrgIndex );              /*[UpdRec]PFC */
        Dem_PFCMng_SetCycleQualifiedInfo( PFCRecordIndex, CycleQualifiedInfo );
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_DTC_GetUpdateOrderCount                              */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] PFCRecordIndex                                      */
/*               | [in] EventStrgIndex                                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC                                              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_SetPFCRecordWithClearCondition
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    /* Set the PFCrecord. */
    Dem_PFCMng_SetPFCRecordData( PFCRecordIndex, EventStrgIndex );                  /*[UpdRec]PFC */
    Dem_PFCMng_SetCycleQualifiedInfo( PFCRecordIndex, DEM_PFC_QUALIFIEDINFO_INITIAL );
    return ;
}


/****************************************************************************/
/* Function Name | Dem_DTC_CheckRegistPFCRecord                             */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex                                      */
/*               | [in] StatusOfDTC                                         */
/* Return Value  | boolean                                                  */
/*               |      TRUE  : regist OK.                                  */
/*               |      FALSE : regist NG.                                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DTC_CheckRegistPFCRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) registEnable;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPFCRecordIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventId;
    VAR( boolean, AUTOMATIC ) retGetPFCSuppression;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordIndex;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_u08_DTCStatusEx2Type, AUTOMATIC ) extendStatusOfDTC2;
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    /*  [FuncSw]    */
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )  /* [FuncSw]     */
    VAR( boolean, AUTOMATIC ) retRegist;
#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )       */
#endif  /*  ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )        */

    registEnable    =   (boolean)FALSE;
    eventId = ((Dem_EventIdType)0x0000U);
    pfcRecordIndex = DEM_PFC_RECORD_INDEX_INITIAL;

    retGetEventId = Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, &eventId );   /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
    if( retGetEventId == DEM_IRT_OK )
    {
        (void)Dem_DataMngC_GetER_ExtendDTCStatus2( EventStrgIndex, &extendStatusOfDTC2 );  /* no return check required */   /* [GUD]EventStrgIndex */
        if ( ( extendStatusOfDTC2 & DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY ) == DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY )
        {
            retGetPFCRecordIndex = Dem_PFCMng_GetPFCRecordIndex( EventStrgIndex, &pfcRecordIndex );                         /* [GUD]EventStrgIndex */
            if( retGetPFCRecordIndex != DEM_IRT_OK )
            {
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    /*  [FuncSw]    */
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )  /* [FuncSw]     */
                retRegist   =   Dem_CmbEvt_CheckRegistPFC( EventStrgIndex );        /* [GUD]EventStrgIndex */
                if ( retRegist == (boolean)TRUE )
#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )       */
#endif  /*  ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )        */
                {
                    retGetPFCSuppression = Dem_PFC_GetPFCSuppression( eventId );
                    if( retGetPFCSuppression != (boolean)TRUE )
                    {
                        registEnable    =   (boolean)TRUE;
                    }
                }
            }
        }
    }
    return registEnable;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
