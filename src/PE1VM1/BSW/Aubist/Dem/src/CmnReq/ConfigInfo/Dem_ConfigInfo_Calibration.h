/* Dem_ConfigInfo_Calibration_h(v5-3-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_Calibration/HEADER                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CONFIGINFO_CALIBRATION_H
#define DEM_CONFIGINFO_CALIBRATION_H

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
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

FUNC( Dem_EventIdType, DEM_CODE_TRUST ) Dem_CfgInfoCalib_CnvEventCtrlIndexToEventId
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Dem_EventIdType, DEM_CODE_TRUST ) Dem_CfgInfoCalib_CnvUdmEventIndexToEventId
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
#endif  /*  ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoCalib_CnvEventConfigIdToEventCtrlIndex
(
    VAR( Dem_EventParameterConfigIdType, AUTOMATIC )    EventConfigureId,
    P2VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC, AUTOMATIC ) EventCtrlIndexPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_CONFIGINFO_CALIBRATION_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
