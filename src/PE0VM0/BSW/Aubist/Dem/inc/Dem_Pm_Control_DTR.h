/* Dem_Pm_Control_DTR_h(v5-9-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_Control_DTR/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DEM_PM_CONTROL_DTR_H
#define DEM_PM_CONTROL_DTR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"

#if ( DEM_DTR_SUPPORT == STD_ON )


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

FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Control_SetDTR
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC) DtrId,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) TestResult,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) LowerLimit,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) UpperLimit,
    VAR( Dem_DTRControlType, AUTOMATIC) Ctrlval
);

#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Control_GetDTR
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC) DTRId,
    P2VAR( Dem_DtrDataType, AUTOMATIC, AUTOMATIC) DtrDataPtr
);
#endif  /* ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON ) */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetDTRConvertInfo
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,
    P2VAR( Dem_u08_DTRObdMidType, AUTOMATIC, AUTOMATIC ) DtrMidPtr,
    P2VAR( Dem_u08_DTRTidIndexType, AUTOMATIC, AUTOMATIC ) DtrTidPtr,
    P2VAR( Dem_u08_DTRUasidType, AUTOMATIC, AUTOMATIC ) DtrUasidPtr,
    P2VAR( Dem_s32_DTRValueRawType, AUTOMATIC, AUTOMATIC ) CompuN0DivD0Ptr,
    P2VAR( Dem_s32_DTRValueRawType, AUTOMATIC, AUTOMATIC ) CompuN1DivD0Ptr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Control_GetAvailableOBDMIDs
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC ) Obdmid,
    P2VAR( Dem_u32_DTRObdMidBmpType, AUTOMATIC, AUTOMATIC ) ObdmidvaluePtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Control_GetNumTIDsOfOBDMID
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC ) Obdmid,
    P2VAR( Dem_u08_DTRTidIndexType, AUTOMATIC, AUTOMATIC) NumberOfTIDsPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Control_GetDTRData
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC ) Obdmid,
    VAR( Dem_u08_DTRTidIndexType, AUTOMATIC ) TidIndex,
    P2VAR( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_DTR_SUPPORT == STD_ON ) */

#endif /* DEM_PM_CONTROL_DTR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

