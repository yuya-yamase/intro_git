/* Dem_CmnLib_DataCtl_SamplingFFDAccess_h(v5-5-0)                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmnLib_DataCtl_SamplingFFDAccess/HEADER               */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_CMNLIB_DATACTL_SAMPLINGFFDACCESS_H
#define DEM_CMNLIB_DATACTL_SAMPLINGFFDACCESS_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_TSFF_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Position information for sampling freeze frame record */
typedef struct
{
    Dem_u16_UdmFFDIndexType RecordStatus;   /* The position of "RecordStatus". */
    Dem_u16_UdmFFDIndexType DataStart;      /* The position of "Data[0]. */
} Dem_SamplingFreezeFrameRecordPosType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC_P2VAR( uint8, DEM_VAR_NO_INIT, DEM_CODE ) Dem_Data_GetSamplingFreezeFrameRecordDataPtr
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingFreezeFrameMemoryRef,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) SamplingFreezeFrameRecordIndex
);

FUNC( void, DEM_CODE ) Dem_Data_GetSamplingFreezeFrameRecordPosition
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingFreezeFrameMemoryRef,
    P2VAR( Dem_SamplingFreezeFrameRecordPosType, AUTOMATIC, AUTOMATIC ) SamplingFreezeFrameRecordPosPtr
);

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
FUNC( Dem_u16_SmpTSFFDIndexType, DEM_CODE ) Dem_Data_GetSamplingFFDRecordNum
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingFreezeFrameMemoryRef
);
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#endif  /* ( DEM_TSFF_SUPPORT == STD_ON )   */

#endif  /* DEM_CMNLIB_DATACTL_SAMPLINGFFDACCESS_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
