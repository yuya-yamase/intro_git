/* Rte_Dem_Typedef_h(v5-9-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RTE/Dem_Typedef/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef RTE_DEM_TYPEDEF_H_
#define RTE_DEM_TYPEDEF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef uint16 Dem_BlockIdType;
typedef uint16 Dem_ComponentIdType;
typedef uint8 Dem_DebounceResetStatusType;
typedef uint8 Dem_DebouncingStateType;
typedef uint8 Dem_DTCFormatType;
typedef uint8 Dem_DTCKindType;
typedef uint16 Dem_DTCOriginType;
typedef uint8 Dem_DTCRequestType;
typedef uint8 Dem_DTCSettingStatusType;
typedef uint8 Dem_DTCSeverityType;
typedef uint8 Dem_DTCTranslationFormatType;
typedef uint8 Dem_DTRControlType;
typedef uint16 Dem_EventIdType;
typedef uint8 Dem_EventKindType;
typedef uint8 Dem_EventStatusType;
typedef uint8 Dem_IndicatorStatusType;
typedef uint8 Dem_InitMonitorReasonType;
typedef uint8 Dem_IumprDataType;
typedef uint8 Dem_IumprDenomCondIdType;
typedef uint8 Dem_IumprDenomCondStatusType;
typedef uint8 Dem_J1939DcmDTCStatusFilterType;
typedef uint8 Dem_J1939DcmSetClearFilterType;
typedef uint8 Dem_J1939DcmSetFreezeFrameFilterType;
typedef uint32 Dem_MonitorDataType;
typedef uint8 Dem_MonitorStatusType;
typedef uint16 Dem_RatioIdType;
typedef uint16 Dem_RecordKindType;
typedef uint8 Dem_ReturnClearDTCType;
typedef uint8 Dem_ReturnControlDTCSettingType;
typedef uint8 Dem_ReturnDisableDTCRecordUpdateType;
typedef uint8 Dem_ReturnGetDTCByOccurrenceTimeType;
typedef uint8 Dem_ReturnGetExtendedDataRecordByDTCType;
typedef uint8 Dem_ReturnGetFreezeFrameDataByDTCType;
typedef uint8 Dem_ReturnGetFunctionalUnitOfDTCType;
typedef uint8 Dem_ReturnGetNextFilteredElementType;
typedef uint8 Dem_ReturnGetNumberOfFilteredDTCType;
typedef uint8 Dem_ReturnGetSeverityOfDTCType;
typedef uint8 Dem_ReturnGetSizeOfDataByDTCType;
typedef uint8 Dem_ReturnGetStatusOfDTCType;
typedef uint8 Dem_ReturnSetFilterType;
typedef uint8 Dem_UdsStatusByteType;
typedef uint8 Dem_UdsStatusHistoryByteType;
typedef uint8 Dem_ReturnStartStoredDataType;
typedef uint8 Dem_ReturnGetSizeOfDataByRecNumType;
typedef uint8 Dem_ReturnGetDTCStoredDataByRecNumType;
typedef uint8 Dem_SimilarConditionStatusType;
typedef uint32 Dem_SimilarConditionValueType;
typedef uint8 Dem_MisfireCylinderNumberType;
typedef uint16 Dem_MisfireCylinderType;
typedef uint16 Dem_MisfireCylinderStatusType;
typedef uint8 Dem_MisfireConditionType;

typedef struct Rte_struct_Dem_MisfireType Dem_MisfireType;
struct Rte_struct_Dem_MisfireType {
    Dem_MisfireCylinderType MisfireCylinder;
    Dem_MisfireConditionType MisfireCondition;
};

typedef struct Rte_struct_Dem_SpecificEventConditionType Dem_SpecificEventConditionType;
struct Rte_struct_Dem_SpecificEventConditionType {
    Dem_SimilarConditionValueType SimilarConditionArray[3];
    Dem_MisfireType MisfireInfo;
};


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* RTE_DEM_TYPEDEF_H_ */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
