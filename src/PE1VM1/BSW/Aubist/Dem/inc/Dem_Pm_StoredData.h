/* Dem_Pm_StoredData_h(v5-7-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/Pm_StoredData/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_PM_STOREDDATA_H
#define DEM_PM_STOREDDATA_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )
typedef struct
{
    Dem_u16_EventStrgIndexType      EventStrgIndex;
    boolean                         AlreadyOutputFlg;
} Dem_StoredData_TmpOutputDataType;

#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE ) Dem_StoredData_Init
( void );


FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_StartDTCStoredData
( void );


FUNC( void, DEM_CODE ) Dem_StoredData_EndDTCStoredData
( void );


FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetSizeOfDTCStoredDataByRecNum
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) SizeOfStoredDataPtr
);


FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetDTCStoredDataByRecNum
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
);

/*------------------------------*/
/*  Dem_StoredData_MakeData.c   */
/*------------------------------*/
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_StoredData_SetDTCAndStatusOfStoredData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_StoredData_GetStoredData
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) CapturedDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) CapturedDataPtr,
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) FreezeFrameClassRef,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);

#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_STOREDDATA_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
