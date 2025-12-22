/* Dem_CmnLib_CmbEvt_h(v5-7-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmnLib_CmbEvt/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CMNLIB_CMBEVT_H
#define DEM_CMNLIB_CMBEVT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/*------------------------------*/
/*  CombinedEvent OnStorage     */
/*------------------------------*/
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE_TRUST ) Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE_TRUST ) Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE_TRUST ) Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
/*------------------------------*/
/*  CombinedEvent OnStorage     */
/*------------------------------*/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( boolean, DEM_CODE ) Dem_CmbEvt_CheckDelegateEventCtrlIndex_InEvtStrgGrp
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);

/*------------------------------*/
/*  CombinedEvent OnRetrieval   */
/*------------------------------*/
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_CmbEvt_StartOfCheckOutputFilteredDTC
( void );
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON )
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CmbEvt_CheckOutputFilteredObdDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u16_ObdDTCValueType, AUTOMATIC ) ObdDTCValue
);
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    */
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT == STD_ON )    */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CmbEvt_CheckOutputFilteredUdsDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) UdsDTCValue
);
#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CmbEvt_CheckRegistPFC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    */
#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE_TRUST ) Dem_CmbEvt_NumOfEventStrgIndex_InDTCGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE_TRUST ) Dem_CmbEvt_GetNextEventStrgIndex_InDTCGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( boolean, DEM_CODE ) Dem_CmbEvt_CheckDelegateEventStrgIndex_InDTCGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_CMNLIB_CMBEVT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
