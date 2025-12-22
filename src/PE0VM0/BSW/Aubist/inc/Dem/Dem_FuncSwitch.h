/* Dem_FuncSwitch_h(v5-10-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/FuncSwitch/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_FUNCSWITCH_H
#define DEM_FUNCSWITCH_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_OBD_SUPPORT                                 (STD_OFF)    /* DemOBDSupport */
#define DEM_OBD_MASTER_SUPPORT                          (STD_OFF)    /* DemOBDSupport is DEM_OBD_MASTER_ECU */
#define DEM_SPECIFIC_EVENT_SUPPORT                      (STD_OFF)    /* DemSpecificEventParameter */

#define DEM_OBDONEDS_SUPPORT                            (STD_OFF)    /* OBDonEDS */
#define DEM_OBDONUDS_SUPPORT                            (STD_OFF)    /* OBDonUDS */
#define DEM_WWH_OBD_SUPPORT                             (STD_OFF)    /* DemOBDCompressionType */
#define DEM_ZEVONUDS_SUPPORT                            (STD_OFF)    /* ZEVonUDS */

#define DEM_ENGINETYPE_COMPRESSION_SUPPORT              (STD_OFF)    /* DemOBDEngineType */

#define DEM_CALIBRATION_BY_CALLOUT_SUPPORT              (STD_OFF)    /* DemCalibrationByCalloutSupport */
#define DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT             (STD_OFF)    /* DemEventCombinationSupport */
#define DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT           (STD_OFF)    /* DemEventCombinationSupport */
#define DEM_COMBINEDEVENT_ONRETRIEVAL_FILDTC_SUPPORT    (STD_OFF)    /* DemEventCombinationOnRetrievalPattern */

#define DEM_USERDEFINEDMEMORY_SUPPORT                   (STD_OFF)    /* Use DemUserDefinedMemory */

#define DEM_FFD_RECORDUPDATE_AT_TESTFAILED_SUPPORT      (STD_OFF)    /* At least one DemFreezeFrameRecordUpdate is set to DEM_UPDATE_RECORD_AT_TEST_FAILED */

#define DEM_TSFF_SUPPORT                                (STD_OFF)    /* DemTimeSeriesFreezeFrameSupport */
#define DEM_TSFF_PM_SUPPORT                             (STD_OFF)    /* DemTimeSeriesFreezeFrameSupport on PrimaryMemory */
#define DEM_TSFF_UDM_SUPPORT                            (STD_OFF)    /* DemTimeSeriesFreezeFrameSupport on UserDefinedMemory */

#define DEM_OBDDTC_FORMAT_SUPPORT                       (STD_OFF)    /* DemOBDSupport */
#define DEM_OBDFFD_SUPPORT                              (STD_OFF)    /* OBDFFD exists */
#define DEM_OBDFFD_DID_SUPPORT                          (STD_OFF)    /* OBDFFD DID exists */
#define DEM_OBDFFD_RECNUM00_ONLY_SUPPORT                (STD_OFF)    /* OBDFFD RecordNumber 0x00 only exists */
#define DEM_OBDFFD_RECNUM00_F0_SUPPORT                  (STD_OFF)    /* OBDFFD RecordNumber 0x00 and 0xF0 exists */

#define DEM_VERSION_INFO_API                            (STD_OFF)    /* DemVersionInfoApi */
#define DEM_ASYNCDATAQUE_USE                            (STD_OFF)    /* Use ExecAsyncDataQueTable */
#define DEM_MONITORDATA_SUPPORT                         (STD_OFF)    /* DemProvideMonitorData */
#define DEM_READFUNC_MONITORDATA_SUPPORT                (STD_OFF)    /* DemProvideMonitorData and OBDDTCExtendedDataRecord and DemUserDefinedMemory */
#define DEM_EVENT_AVAILABILITY_SUPPORT                  (STD_ON)     /* DemAvailabilitySupport */
#define DEM_EVENT_AVAILABILITY_FIM_REPORT               (STD_OFF)    /* DemTriggerFiMReports and DemAvailabilitySupport */
#define DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT             (STD_OFF)    /* DemClearEventAllowed */
#define DEM_CLEAR_EVENT_ALLOWED_BY_CALLOUT_SUPPORT      (STD_OFF)    /* DemClearEventAllowedByCalloutSupport */
#define DEM_INDICATOR_USE                               (STD_OFF)    /* DemIndicatorAttribute */
#define DEM_USER_DEFINED_INDICATOR_SUPPORT              (STD_OFF)    /* DemIndicator */
#define DEM_FF_PRESTORAGE_SUPPORT                       (STD_OFF)    /* DemMaxNumberPrestoredFF */
#define DEM_FFD_OUTPUT_JUDGE_SUPPORT                    (STD_OFF)    /* DemUseFreezeFrameDataOutputJudge */
#define DEM_FF_CHECKSUM_SUPPORT                         (STD_OFF)    /* DemFreezeFrameChecksumSupport */
#define DEM_EVENT_DISPLACEMENT_SUPPORT                  (STD_OFF)    /* DemEventDisplacementStrategy */
#define DEM_EVENT_DISPLACEMENT_CALLOUT_SUPPORT          (STD_OFF)    /* DemEventDisplacementStrategy */
#define DEM_EVENT_DISPLACEMENT_BY_DTCSTATUS_SUPPORT     (STD_OFF)    /* DemEventDisplacementStrategy and DemEventDisplacementByDTCStatus */
#define DEM_EVENT_DISPLACEMENT_BY_CDTC_NONOBDONLY_SUPPORT    (STD_OFF)    /* DemEventDisplacementByDTCStatusTarget */
#define DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT     (STD_OFF)    /* Parameters in the DemMaxNumberOfFreezeFrameTriggerClass */
#define DEM_EVENTPRIORITY_PM_SUPPORT                    (STD_OFF)    /* Use EventPriority in PrimaryMemory */
#define DEM_EVENTPRIORITY_CALLOUT_SUPPORT               (STD_OFF)    /* Use EventPriority Callout */
#define DEM_DTC_OCCURRENCE_TIME_SUPPORT                 (STD_OFF)    /* DemTriggerDcmReports */
#define DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT   (STD_OFF)    /* DemOccurrenceTimeDTCUpdateAtAging */
#define DEM_TRIGGER_BSWM_REPORTS                        (STD_OFF)    /* DemTriggerBswMReports */
#define DEM_TRIGGER_DCM_REPORTS                         (STD_OFF)    /* DemTriggerDcmReports */
#define DEM_TRIGGER_FIM_REPORTS                         (STD_OFF)    /* DemTriggerFiMReports */
#define DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT           (STD_OFF)    /* DemDTCStoredData */
#define DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT       (STD_OFF)    /* DemUseGetUDSDTCByConfirmedDTCOrder */
#define DEM_GETOCCURRENCECOUNTER_SUPPORT                (STD_ON)     /* DemUseGetEventOccurrenceCounter */

#define DEM_CYCLEQUALIFIED_SUPPORT                      (STD_OFF)    /* DemOBDSupport */
#define DEM_PID_SUPPORT                                 (STD_OFF)    /* DemOBDSupport */
#define DEM_PID_WARMUPCYC_SUPPORT                       (STD_OFF)    /* DemOBDSupport */
#define DEM_PID_READINESS_SUPPORT                       (STD_OFF)    /* DemOBDSupport */
#define DEM_PID_CALC_DEMINTERNALPID_SUPPORT             (STD_OFF)    /* DemOBDSupport is DEM_OBD_MASTER_ECU */
#define DEM_PID21AND4D_CALCCONDITION_CDTC_SUPPORT       (STD_OFF)    /* DemOBDDemInternalPID21AndPID4DCalculateCondition */

#define DEM_READINESSSUPPORT_BY_CALLOUT_SUPPORT         (STD_OFF)    /* DemOBDReadinessSupportJudgeType */
#define DEM_USERDTC_GETNUMBEROFUSERDTC_CALLOUT_USE      (STD_OFF)    /* Use GetNumberOfUserDTC Callout */

#define DEM_PFC_SUPPORT                                 (STD_OFF)    /* DemMaxNumberEventEntryPermanent */
#define DEM_PFC_RECORD_SUPPRESSION_SUPPORT              (STD_OFF)    /* DemOBDPFCRecordSuppressionSupport */
#define DEM_PFC_ORDER_MIL_SUPPORT                       (STD_OFF)    /* DemOBDPFCRecordOrderType is DEM_PFC_ORDER_MIL */
#define DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT     (STD_OFF)    /* DemOBDOutputDemInternalPFCToDcm */

#define DEM_IUMPR_SUPPORT                               (STD_OFF)    /* DemRatio */
#define DEM_IUMPR_RATIO_SUPPORT                         (STD_OFF)    /* DemRatio */
#define DEM_IUMPR_EDR_SUPPORT                           (STD_OFF)    /* IUMPR ExtendedDataRecord */
#define DEM_IUMPR_NODI_SELECT_BY_CALLOUT_SUPPORT        (STD_OFF)    /* DemOBDIUMPRNODISelectionByCallout */

#define DEM_ALTIUMPR_SUPPORT                            (STD_OFF)    /* Alternative IUMPR */

#define DEM_DTR_SUPPORT                                 (STD_OFF)    /* DemDtr */
#define DEM_DTR_RAWDATASTORAGE_SUPPORT                  (STD_OFF)    /* DemOBDDtrRawDataStorage */
#define DEM_DTR_EDR_SUPPORT                             (STD_OFF)    /* DTR ExtendedDataRecord */

#define DEM_SIMILAR_EVENT_CONFIGURED                    (STD_OFF)    /* DemSimilarConditionPerEvent */
#define DEM_MISFIRE_EVENT_CONFIGURED                    (STD_OFF)    /* DemMisfire */
#define DEM_MISFIRE_CAT_EVENT_CONFIGURED                (STD_OFF)    /* DemMisfireCatalystDamage */

#define DEM_PENDINGCLEARCOUNT_PATTERN2_SUPPORT          (STD_OFF)    /* DemPendingClearCounterUpdatePattern */
#define DEM_SIMCONDCLEAR_PATTERN2_SUPPORT               (STD_OFF)    /* DemSimilarConditionClearPattern */

#define DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT   (STD_OFF)    /* DemOBDCheck4000RPMOccurredByEmissionMisfireEvent */

#define DEM_MISFIRE_OUTPUT_UDSOBDFFD_MULTIPLE_FAILED_CYL_SUPPORT    (STD_OFF)     /* DemMisfireOutputUDSOBDFreezeFramePattern */

#define DEM_ORDERTYPE_CONFIRMED_USE                     (STD_OFF)    /* Use ConfirmedFaultOrderList */
#define DEM_ORDERTYPE_CONFIRMED_ORDERLIST_USE           (STD_OFF)    /* Use ConfirmedFaultOrderList */

#define DEM_NVM_SYNC_PROCESS_ENABLE                     (STD_ON)     /* NvM Sync Process */

#define DEM_CLRINFO_RECORD_PADDING_EXIST                (STD_ON)     /* Padding exists in ClearInformation Record */
#define DEM_EVENT_RECORD_PADDING_EXIST                  (STD_OFF)    /* Padding exists in EventRecord */
#define DEM_FAULT_RECORD_PADDING_EXIST                  (STD_OFF)    /* Padding exists in FaultRecord */
#define DEM_IUMPR_RECORD_PADDING_EXIST                  (STD_OFF)    /* Padding exists in IUMPRRecord */
#define DEM_ALTIUMPR_RECORD_PADDING_EXIST               (STD_OFF)    /* Padding exists in AltIUMPRRecord */
#define DEM_DTR_RECORD_PADDING_EXIST                    (STD_OFF)    /* Padding exists in DtrRecord */
#define DEM_INDMI_RECORD_PADDING_EXIST                  (STD_OFF)    /* Padding exists in B1CounterRecord */
#define DEM_SIMILAR_RECORD_PADDING_EXIST                (STD_OFF)    /* Padding exists in SimilarRecord */
#define DEM_MISFIRE_RECORD_PADDING_EXIST                (STD_OFF)    /* Padding exists in MisfireRecord */
#define DEM_MISFIRECOM_RECORD_PADDING_EXIST             (STD_OFF)    /* Padding exists in MisfireComRecord */
#define DEM_UDMEVENT_RECORD_PADDING_EXIST               (STD_OFF)    /* Padding exists in UdmEventRecord */

#define DEM_PDTCFFD_CLRTRIGGER_TRIGGEROFF_SUPPORT       (STD_OFF)    /* DemPendingFreezeFrameClearTrigger */
#define DEM_TFTOCFFD_CLRTRIGGER_AGINGONLY_SUPPORT       (STD_ON)     /* DemTestFailedThisOperationCycleFreezeFrameClearTrigger */

#define DEM_DTR_FLOAT_SUPPORT                           (STD_OFF)    /* DemOBDFloatSupport */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* DEM_FUNCSWITCH_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
