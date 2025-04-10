/* Dem_Pm_DTR_h(v5-3-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_DTR/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DEM_PM_DTR_H
#define DEM_PM_DTR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"

#if ( DEM_DTR_SUPPORT == STD_ON )

#include "../cfg/Dem_Dtr_Cfg.h"

#endif  /* ( DEM_DTR_SUPPORT == STD_ON ) */

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
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_DTR_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DTR_Init_AfterRecordCheckComplete
(void);

FUNC( void, DEM_CODE ) Dem_DTR_ClearDTRData
(void);

FUNC( void, DEM_CODE ) Dem_DTR_SetDTR
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC) DTRId,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) TestResult,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) LowerLimit,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) UpperLimit,
    VAR( Dem_DTRControlType, AUTOMATIC) Ctrlval
);

#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_GetDTR
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC) DTRId,
    P2VAR( Dem_DtrDataType, AUTOMATIC, AUTOMATIC) DtrDataPtr
);
#endif  /* ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON ) */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_GetAvailableOBDMIDs
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC) Obdmid,
    P2VAR( Dem_u32_DTRObdMidBmpType, AUTOMATIC, AUTOMATIC) ObdmidvaluePtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_GetNumTIDsOfOBDMID
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC ) Obdmid,
    P2VAR( Dem_u08_DTRTidIndexType, AUTOMATIC, AUTOMATIC) NumberOfTIDsPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_GetDTRData
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC ) Obdmid,
    VAR( Dem_u08_DTRTidIndexType, AUTOMATIC ) TidIndex,
    P2VAR( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
);

#endif  /* ( DEM_DTR_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_PM_DTR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

