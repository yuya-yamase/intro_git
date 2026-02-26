/* Dem_Dcm_h(v5-5-0)                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Dcm/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_DCM_H
#define DEM_DCM_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )
#include <Dcm.h>
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */

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


FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetDTCStatusAvailabilityMask
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA ) DTCStatusMask,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetDTCSeverityAvailabilityMask
(
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA ) DTCSeverityMask
);
FUNC( Dem_ReturnGetStatusOfDTCType, DEM_CODE ) Dem_DcmGetStatusOfDTC
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DTCStatus
);
FUNC( Dem_ReturnSetFilterType, DEM_CODE ) Dem_DcmSetDTCFilter
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    VAR( boolean, AUTOMATIC ) FilterForFaultDetectionCounter
);
FUNC( Dem_ReturnGetNextFilteredElementType, DEM_CODE ) Dem_DcmGetNextFilteredDTC
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTC,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA ) DTCStatus
);
FUNC( Dem_ReturnSetFilterType, DEM_CODE ) Dem_DcmSetEDRNumberFilter
(
    VAR( uint8, AUTOMATIC ) ExtendedDataNumber
);
FUNC( Dem_ReturnGetNextFilteredElementType, DEM_CODE ) Dem_DcmGetNextEDRNumFilteredDTC
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTCPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA ) DTCStatusPtr
);
FUNC( Dem_ReturnGetNextFilteredElementType, DEM_CODE ) Dem_DcmGetNextFilteredDTCAndSeverity
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTC,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA ) DTCStatus,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA ) DTCSeverity,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DTCFunctionalUnit
);
FUNC( Dem_ReturnSetFilterType, DEM_CODE ) Dem_DcmSetDTCFilterForReadiness
(
    VAR( uint8, AUTOMATIC ) ReadinessGroupId
);
FUNC( Dem_ReturnGetNextFilteredElementType, DEM_CODE ) Dem_DcmGetNextFilteredDTCForReadiness
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTCPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA ) DTCStatusPtr
);
FUNC( Dem_ReturnSetFilterType, DEM_CODE ) Dem_DcmSetFreezeFrameRecordFilter
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) NumberOfFilteredRecords
);
FUNC( Dem_ReturnGetNextFilteredElementType, DEM_CODE ) Dem_DcmGetNextFilteredRecord
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTC,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RecordNumber
);
FUNC( Dem_ReturnDisableDTCRecordUpdateType, DEM_CODE ) Dem_DcmDisableDTCRecordUpdate
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmEnableDTCRecordUpdate
( void );
FUNC( Dem_ReturnGetFreezeFrameDataByDTCType, DEM_CODE ) Dem_DcmGetFreezeFrameDataByDTC
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) BufSize,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) NextRecordNumberPtr
);
FUNC( Dem_ReturnGetSizeOfDataByDTCType, DEM_CODE ) Dem_DcmGetSizeOfFreezeFrameByDTC
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) SizeOfFreezeFrame
);
FUNC( Dem_ReturnGetSizeOfDataByDTCType, DEM_CODE ) Dem_DcmGetSizeOfExtendedDataRecordByDTC
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( uint8, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) SizeOfExtendedDataRecord
);
FUNC( Dem_ReturnGetExtendedDataRecordByDTCType, DEM_CODE ) Dem_DcmGetExtendedDataRecordByDTC
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( uint8, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) BufSize,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) NextExtendedDataNumberPtr
);
FUNC( Dem_ReturnClearDTCType, DEM_CODE ) Dem_DcmCheckClearParameter
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( Dem_ReturnClearDTCType, DEM_CODE ) Dem_DcmClearDTC
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( Dem_DTCTranslationFormatType, DEM_CODE ) Dem_DcmGetTranslationType
( void );
FUNC( Dem_ReturnGetNumberOfFilteredDTCType, DEM_CODE ) Dem_DcmGetNumberOfFilteredDTC
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) NumberOfFilteredDTC
);
FUNC( Dem_ReturnGetNumberOfFilteredDTCType, DEM_CODE ) Dem_DcmGetNumberOfFilteredDTCAndSeverity
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) NumberOfFilteredDTCAndSeverityPtr
);
FUNC( Dem_ReturnControlDTCSettingType, DEM_CODE ) Dem_DcmDisableDTCSetting
(
    VAR( uint32, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
);
FUNC( Dem_ReturnControlDTCSettingType, DEM_CODE ) Dem_DcmEnableDTCSetting
(
    VAR( uint32, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
);
FUNC( Dem_ReturnStartStoredDataType, DEM_CODE ) Dem_DcmStartDTCStoredData
( void );
FUNC( void, DEM_CODE ) Dem_DcmEndDTCStoredData
( void );
FUNC( Dem_ReturnGetSizeOfDataByRecNumType, DEM_CODE ) Dem_DcmGetSizeOfDTCStoredDataByRecNum
(
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) SizeOfStoredDataPtr
);
FUNC( Dem_ReturnGetDTCStoredDataByRecNumType, DEM_CODE ) Dem_DcmGetDTCStoredDataByRecNum
(
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) BufSizePtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) NextRecordNumberPtr
);

FUNC( void, DEM_CODE ) Dem_DcmControlDTCStatusChangedNotification
(
    VAR( boolean, AUTOMATIC ) TriggerNotification
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetDTCByOccurrenceTime
(
    VAR( Dem_DTCRequestType, AUTOMATIC ) DTCRequest,
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTCValue
);


/*======================================*/
/*  for PrimaryOBD, MasterOBD           */
/*======================================*/
#if ( DEM_PID_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID01
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID01value
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID1C
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID1Cvalue
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID21
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID30
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID30value
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID31
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID41
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID41value
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID4D
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID4E
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPIDF501
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDF501value
);
#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */

#if ( DEM_OBD_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetDTCOfOBDFreezeFrame
(
    VAR( uint8, AUTOMATIC ) FrameNumber,
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTC
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfOBDFreezeFrame
(
    VAR( uint8, AUTOMATIC ) PID,
    VAR( uint8, AUTOMATIC ) DataElementIndexOfPID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) BufSize
);
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

/*======================================*/
/*  for TestResult                      */
/*======================================*/

#if ( DEM_DTR_SUPPORT == STD_ON )

FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetAvailableOBDMIDs
(
    VAR(uint8, AUTOMATIC) Obdmid,
    P2VAR(uint32, AUTOMATIC, AUTOMATIC) Obdmidvalue
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetNumTIDsOfOBDMID
(
    VAR(uint8, AUTOMATIC) Obdmid,
    P2VAR(uint8 , AUTOMATIC, AUTOMATIC) numberOfTIDs
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetDTRData
(
    VAR(uint8, AUTOMATIC) Obdmid,
    VAR(uint8, AUTOMATIC) TIDindex,
    P2VAR(uint8 , AUTOMATIC, AUTOMATIC) TIDvalue,
    P2VAR(uint8 , AUTOMATIC, AUTOMATIC) UaSID,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) Testvalue,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) Lowlimvalue,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) Upplimvalue
);

#endif  /* ( DEM_DTR_SUPPORT == STD_ON )    */


/*======================================*/
/*  for IUMPR                           */
/*======================================*/

#if ( DEM_IUMPR_SUPPORT == STD_ON )

FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetInfoTypeValue08
(
    VAR( Dcm_OpStatusType, AUTOMATIC )          OpStatus,
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   Iumprdata08,
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   Iumprdata08BufferSize
);

FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetInfoTypeValue0B
(
    VAR( Dcm_OpStatusType, AUTOMATIC )          OpStatus,
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   Iumprdata0B,
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   Iumprdata0BBufferSize
);


#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>




#endif /* DEM_DCM_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

