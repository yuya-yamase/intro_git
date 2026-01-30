/* Dem_CmnLib_Control_h(v5-10-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmnIf_Control/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CMNLIB_CONTROL_H
#define DEM_CMNLIB_CONTROL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Initialization state */
#define DEM_CTL_STS_INIT_UNINITIALIZED      ((Dem_u08_InitStatusType)0x00U)
#define DEM_CTL_STS_INIT_PREINIT_COMPLETE   ((Dem_u08_InitStatusType)0x11U)
#define DEM_CTL_STS_INIT_INITIALIZING       ((Dem_u08_InitStatusType)0x22U)
#define DEM_CTL_STS_INIT_COMPLETE           ((Dem_u08_InitStatusType)0x33U)

/* DTC setting state */
#define DEM_CTL_STS_DTC_SETTING_ENABLE      ((Dem_u08_DTCSettingStatusType)0x00U)
#define DEM_CTL_STS_DTC_SETTING_TO_ENABLE   ((Dem_u08_DTCSettingStatusType)0x11U)
#define DEM_CTL_STS_DTC_SETTING_DISABLE     ((Dem_u08_DTCSettingStatusType)0x22U)
#define DEM_CTL_STS_DTC_SETTING_TO_DISABLE  ((Dem_u08_DTCSettingStatusType)0x33U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes - PreInit section                                    */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  Dem_Control                     */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ChkAfterInit
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ChkAfterPreInit
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ChkAfterCompleteInit
( void );


/*----------------------------------*/
/*  Dem_Control_Clear               */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Control_GetClearType
(
    P2VAR( Dem_u32_DTCGroupType, AUTOMATIC, AUTOMATIC ) DTCGroupPtr,
    P2VAR( Dem_DTCOriginType, AUTOMATIC, AUTOMATIC ) DTCOriginPtr
);
FUNC( Dem_DTCOriginType, DEM_CODE ) Dem_Control_GetClearDTCOrigin
( void );
FUNC( boolean, DEM_CODE ) Dem_Control_CheckExecClearDTCProcess
( void );
FUNC( boolean, DEM_CODE ) Dem_Control_CheckExecClearDTCProcessActive
( void );

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_CMNLIB_CONTROL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

