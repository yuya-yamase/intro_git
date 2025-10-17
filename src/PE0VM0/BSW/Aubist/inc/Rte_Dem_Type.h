/* Rte_Dem_Type_h(v5-5-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RTE/Dem_Type/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef RTE_DEM_TYPE_H
#define RTE_DEM_TYPE_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "Rte_Dem_Typedef.h"








#ifndef DEM_DTC_FORMAT_OBD
#define DEM_DTC_FORMAT_OBD ((Dem_DTCFormatType)0x00U)
#endif /* DEM_DTC_FORMAT_OBD */

#ifndef DEM_DTC_FORMAT_UDS
#define DEM_DTC_FORMAT_UDS ((Dem_DTCFormatType)0x01U)
#endif /* DEM_DTC_FORMAT_UDS */

#ifndef DEM_DTC_FORMAT_J1939
#define DEM_DTC_FORMAT_J1939 ((Dem_DTCFormatType)0x02U)
#endif /* DEM_DTC_FORMAT_J1939 */


#ifndef DEM_DTC_KIND_ALL_DTCS
#define DEM_DTC_KIND_ALL_DTCS ((Dem_DTCKindType)0x01U)
#endif /* DEM_DTC_KIND_ALL_DTCS */

#ifndef DEM_DTC_KIND_EMISSION_REL_DTCS
#define DEM_DTC_KIND_EMISSION_REL_DTCS ((Dem_DTCKindType)0x02U)
#endif /* DEM_DTC_KIND_EMISSION_REL_DTCS */


#ifndef DEM_DTC_ORIGIN_PRIMARY_MEMORY
#define DEM_DTC_ORIGIN_PRIMARY_MEMORY ((Dem_DTCOriginType)0x0001U)
#endif /* DEM_DTC_ORIGIN_PRIMARY_MEMORY */

#ifndef DEM_DTC_ORIGIN_MIRROR_MEMORY
#define DEM_DTC_ORIGIN_MIRROR_MEMORY ((Dem_DTCOriginType)0x0002U)
#endif /* DEM_DTC_ORIGIN_MIRROR_MEMORY */

#ifndef DEM_DTC_ORIGIN_PERMANENT_MEMORY
#define DEM_DTC_ORIGIN_PERMANENT_MEMORY ((Dem_DTCOriginType)0x0003U)
#endif /* DEM_DTC_ORIGIN_PERMANENT_MEMORY */

#ifndef DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY
#define DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY ((Dem_DTCOriginType)0x0004U)
#endif /* DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY */

#ifndef DEM_DTC_ORIGIN_USERDEFINED_MEMORY
#define DEM_DTC_ORIGIN_USERDEFINED_MEMORY ((Dem_DTCOriginType)0x0100U)
#endif /* DEM_DTC_ORIGIN_USERDEFINED_MEMORY */


#ifndef DEM_FIRST_FAILED_DTC
#define DEM_FIRST_FAILED_DTC ((Dem_DTCRequestType)0x01U)
#endif /* DEM_FIRST_FAILED_DTC */

#ifndef DEM_MOST_RECENT_FAILED_DTC
#define DEM_MOST_RECENT_FAILED_DTC ((Dem_DTCRequestType)0x02U)
#endif /* DEM_MOST_RECENT_FAILED_DTC */

#ifndef DEM_FIRST_DET_CONFIRMED_DTC
#define DEM_FIRST_DET_CONFIRMED_DTC ((Dem_DTCRequestType)0x03U)
#endif /* DEM_FIRST_DET_CONFIRMED_DTC */

#ifndef DEM_MOST_REC_DET_CONFIRMED_DTC
#define DEM_MOST_REC_DET_CONFIRMED_DTC ((Dem_DTCRequestType)0x04U)
#endif /* DEM_MOST_REC_DET_CONFIRMED_DTC */


#ifndef DEM_SEVERITY_MAINTENANCE_ONLY
#define DEM_SEVERITY_MAINTENANCE_ONLY ((Dem_DTCSeverityType)0x20U)
#endif /* DEM_SEVERITY_MAINTENANCE_ONLY */

#ifndef DEM_SEVERITY_CHECK_AT_NEXT_HALT
#define DEM_SEVERITY_CHECK_AT_NEXT_HALT ((Dem_DTCSeverityType)0x40U)
#endif /* DEM_SEVERITY_CHECK_AT_NEXT_HALT */

#ifndef DEM_SEVERITY_CHECK_IMMEDIATELY
#define DEM_SEVERITY_CHECK_IMMEDIATELY ((Dem_DTCSeverityType)0x80U)
#endif /* DEM_SEVERITY_CHECK_IMMEDIATELY */

#ifndef DEM_SEVERITY_NO_SEVERITY
#define DEM_SEVERITY_NO_SEVERITY ((Dem_DTCSeverityType)0x00U)
#endif /* DEM_SEVERITY_NO_SEVERITY */

#ifndef DEM_SEVERITY_WWHOBD_CLASS_NO_CLASS
#define DEM_SEVERITY_WWHOBD_CLASS_NO_CLASS ((Dem_DTCSeverityType)0x01U)
#endif /* DEM_SEVERITY_WWHOBD_CLASS_NO_CLASS */

#ifndef DEM_SEVERITY_WWHOBD_CLASS_A
#define DEM_SEVERITY_WWHOBD_CLASS_A ((Dem_DTCSeverityType)0x02U)
#endif /* DEM_SEVERITY_WWHOBD_CLASS_A */

#ifndef DEM_SEVERITY_WWHOBD_CLASS_B1
#define DEM_SEVERITY_WWHOBD_CLASS_B1 ((Dem_DTCSeverityType)0x04U)
#endif /* DEM_SEVERITY_WWHOBD_CLASS_B1 */

#ifndef DEM_SEVERITY_WWHOBD_CLASS_B2
#define DEM_SEVERITY_WWHOBD_CLASS_B2 ((Dem_DTCSeverityType)0x08U)
#endif /* DEM_SEVERITY_WWHOBD_CLASS_B2 */

#ifndef DEM_SEVERITY_WWHOBD_CLASS_C
#define DEM_SEVERITY_WWHOBD_CLASS_C ((Dem_DTCSeverityType)0x10U)
#endif /* DEM_SEVERITY_WWHOBD_CLASS_C */

#ifndef DEM_DTC_CLASS_0
#define DEM_DTC_CLASS_0 ((Dem_DTCSeverityType)0x01U)
#endif /* DEM_DTC_CLASS_0 */

#ifndef DEM_DTC_CLASS_1
#define DEM_DTC_CLASS_1 ((Dem_DTCSeverityType)0x02U)
#endif /* DEM_DTC_CLASS_1 */

#ifndef DEM_DTC_CLASS_2
#define DEM_DTC_CLASS_2 ((Dem_DTCSeverityType)0x04U)
#endif /* DEM_DTC_CLASS_2 */

#ifndef DEM_DTC_CLASS_3
#define DEM_DTC_CLASS_3 ((Dem_DTCSeverityType)0x08U)
#endif /* DEM_DTC_CLASS_3 */

#ifndef DEM_DTC_CLASS_4
#define DEM_DTC_CLASS_4 ((Dem_DTCSeverityType)0x10U)
#endif /* DEM_DTC_CLASS_4 */


#ifndef DEM_DTC_TRANSLATION_ISO15031_6
#define DEM_DTC_TRANSLATION_ISO15031_6 ((Dem_DTCTranslationFormatType)0x00U)
#endif /* DEM_DTC_TRANSLATION_ISO15031_6 */

#ifndef DEM_DTC_TRANSLATION_ISO14229_1
#define DEM_DTC_TRANSLATION_ISO14229_1 ((Dem_DTCTranslationFormatType)0x01U)
#endif /* DEM_DTC_TRANSLATION_ISO14229_1 */

#ifndef DEM_DTC_TRANSLATION_SAEJ1939_73
#define DEM_DTC_TRANSLATION_SAEJ1939_73 ((Dem_DTCTranslationFormatType)0x02U)
#endif /* DEM_DTC_TRANSLATION_SAEJ1939_73 */

#ifndef DEM_DTC_TRANSLATION_ISO11992_4
#define DEM_DTC_TRANSLATION_ISO11992_4 ((Dem_DTCTranslationFormatType)0x03U)
#endif /* DEM_DTC_TRANSLATION_ISO11992_4 */

#ifndef DEM_DTC_TRANSLATION_J2012DA_FORMAT_04
#define DEM_DTC_TRANSLATION_J2012DA_FORMAT_04 ((Dem_DTCTranslationFormatType)0x04U)
#endif /* DEM_DTC_TRANSLATION_J2012DA_FORMAT_04 */


#ifndef DEM_DTR_CTL_NORMAL
#define DEM_DTR_CTL_NORMAL ((Dem_DTRControlType)0x00U)
#endif /* DEM_DTR_CTL_NORMAL */

#ifndef DEM_DTR_CTL_NO_MAX
#define DEM_DTR_CTL_NO_MAX ((Dem_DTRControlType)0x01U)
#endif /* DEM_DTR_CTL_NO_MAX */

#ifndef DEM_DTR_CTL_NO_MIN
#define DEM_DTR_CTL_NO_MIN ((Dem_DTRControlType)0x02U)
#endif /* DEM_DTR_CTL_NO_MIN */

#ifndef DEM_DTR_CTL_RESET
#define DEM_DTR_CTL_RESET ((Dem_DTRControlType)0x03U)
#endif /* DEM_DTR_CTL_RESET */

#ifndef DEM_DTR_CTL_INVISIBLE
#define DEM_DTR_CTL_INVISIBLE ((Dem_DTRControlType)0x04U)
#endif /* DEM_DTR_CTL_INVISIBLE */

#ifndef DEM_DTR_CTL_RESET_FOR_FAILED_TID
#define DEM_DTR_CTL_RESET_FOR_FAILED_TID ((Dem_DTRControlType)0x05U)
#endif /* DEM_DTR_CTL_RESET_FOR_FAILED_TID */


#ifndef DEM_DEBOUNCE_STATUS_FREEZE
#define DEM_DEBOUNCE_STATUS_FREEZE ((Dem_DebounceResetStatusType)0x00U)
#endif /* DEM_DEBOUNCE_STATUS_FREEZE */

#ifndef DEM_DEBOUNCE_STATUS_RESET
#define DEM_DEBOUNCE_STATUS_RESET ((Dem_DebounceResetStatusType)0x01U)
#endif /* DEM_DEBOUNCE_STATUS_RESET */


#ifndef DEM_TEMPORARILY_DEFECTIVE
#define DEM_TEMPORARILY_DEFECTIVE ((Dem_DebouncingStateType)0x01U)
#endif /* DEM_TEMPORARILY_DEFECTIVE */

#ifndef DEM_FINALLY_DEFECTIVE
#define DEM_FINALLY_DEFECTIVE ((Dem_DebouncingStateType)0x02U)
#endif /* DEM_FINALLY_DEFECTIVE */

#ifndef DEM_TEMPORARILY_HEALED
#define DEM_TEMPORARILY_HEALED ((Dem_DebouncingStateType)0x04U)
#endif /* DEM_TEMPORARILY_HEALED */

#ifndef DEM_TEST_COMPLETE
#define DEM_TEST_COMPLETE ((Dem_DebouncingStateType)0x08U)
#endif /* DEM_TEST_COMPLETE */

#ifndef DEM_DTR_UPDATE
#define DEM_DTR_UPDATE ((Dem_DebouncingStateType)0x10U)
#endif /* DEM_DTR_UPDATE */


#ifndef DEM_EVENT_STATUS_PASSED
#define DEM_EVENT_STATUS_PASSED ((Dem_EventStatusType)0x00U)
#endif /* DEM_EVENT_STATUS_PASSED */

#ifndef DEM_EVENT_STATUS_FAILED
#define DEM_EVENT_STATUS_FAILED ((Dem_EventStatusType)0x01U)
#endif /* DEM_EVENT_STATUS_FAILED */

#ifndef DEM_EVENT_STATUS_PREPASSED
#define DEM_EVENT_STATUS_PREPASSED ((Dem_EventStatusType)0x02U)
#endif /* DEM_EVENT_STATUS_PREPASSED */

#ifndef DEM_EVENT_STATUS_PREFAILED
#define DEM_EVENT_STATUS_PREFAILED ((Dem_EventStatusType)0x03U)
#endif /* DEM_EVENT_STATUS_PREFAILED */

#ifndef DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED
#define DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED ((Dem_EventStatusType)0x04U)
#endif /* DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED */

#ifndef DEM_EVENT_STATUS_FAILED_TO_PASSED
#define DEM_EVENT_STATUS_FAILED_TO_PASSED ((Dem_EventStatusType)0x05U)
#endif /* DEM_EVENT_STATUS_FAILED_TO_PASSED */


#ifndef DEM_INDICATOR_OFF
#define DEM_INDICATOR_OFF ((Dem_IndicatorStatusType)0x00U)
#endif /* DEM_INDICATOR_OFF */

#ifndef DEM_INDICATOR_CONTINUOUS
#define DEM_INDICATOR_CONTINUOUS ((Dem_IndicatorStatusType)0x01U)
#endif /* DEM_INDICATOR_CONTINUOUS */

#ifndef DEM_INDICATOR_BLINKING
#define DEM_INDICATOR_BLINKING ((Dem_IndicatorStatusType)0x02U)
#endif /* DEM_INDICATOR_BLINKING */

#ifndef DEM_INDICATOR_BLINK_CONT
#define DEM_INDICATOR_BLINK_CONT ((Dem_IndicatorStatusType)0x03U)
#endif /* DEM_INDICATOR_BLINK_CONT */

#ifndef DEM_INDICATOR_SLOW_FLASH
#define DEM_INDICATOR_SLOW_FLASH ((Dem_IndicatorStatusType)0x04U)
#endif /* DEM_INDICATOR_SLOW_FLASH */

#ifndef DEM_INDICATOR_FAST_FLASH
#define DEM_INDICATOR_FAST_FLASH ((Dem_IndicatorStatusType)0x05U)
#endif /* DEM_INDICATOR_FAST_FLASH */

#ifndef DEM_INDICATOR_ON_DEMAND
#define DEM_INDICATOR_ON_DEMAND ((Dem_IndicatorStatusType)0x06U)
#endif /* DEM_INDICATOR_ON_DEMAND */

#ifndef DEM_INDICATOR_SHORT
#define DEM_INDICATOR_SHORT ((Dem_IndicatorStatusType)0x07U)
#endif /* DEM_INDICATOR_SHORT */


#ifndef DEM_INIT_MONITOR_CLEAR
#define DEM_INIT_MONITOR_CLEAR ((Dem_InitMonitorReasonType)0x01U)
#endif /* DEM_INIT_MONITOR_CLEAR */

#ifndef DEM_INIT_MONITOR_RESTART
#define DEM_INIT_MONITOR_RESTART ((Dem_InitMonitorReasonType)0x02U)
#endif /* DEM_INIT_MONITOR_RESTART */

#ifndef DEM_INIT_MONITOR_REENABLED
#define DEM_INIT_MONITOR_REENABLED ((Dem_InitMonitorReasonType)0x03U)
#endif /* DEM_INIT_MONITOR_REENABLED */

#ifndef DEM_INIT_MONITOR_STORAGE_REENABLED
#define DEM_INIT_MONITOR_STORAGE_REENABLED ((Dem_InitMonitorReasonType)0x04U)
#endif /* DEM_INIT_MONITOR_STORAGE_REENABLED */

#ifndef DEM_INIT_MONITOR_DISABLED
#define DEM_INIT_MONITOR_DISABLED ((Dem_InitMonitorReasonType)0x05U)
#endif /* DEM_INIT_MONITOR_DISABLED */


#ifndef DEM_IUMPR_DATA_DENOMINATOR
#define DEM_IUMPR_DATA_DENOMINATOR ((Dem_IumprDataType)0x01U)
#endif /* DEM_IUMPR_DATA_DENOMINATOR */

#ifndef DEM_IUMPR_DATA_NUMERATOR
#define DEM_IUMPR_DATA_NUMERATOR ((Dem_IumprDataType)0x02U)
#endif /* DEM_IUMPR_DATA_NUMERATOR */

#ifndef DEM_IUMPR_DATA_DENOMINATOR_AND_NUMERATOR
#define DEM_IUMPR_DATA_DENOMINATOR_AND_NUMERATOR ((Dem_IumprDataType)0x03U)
#endif /* DEM_IUMPR_DATA_DENOMINATOR_AND_NUMERATOR */


#ifndef DEM_IUMPR_GENERAL_DENOMINATOR
#define DEM_IUMPR_GENERAL_DENOMINATOR ((Dem_IumprDenomCondIdType)0x01U)
#endif /* DEM_IUMPR_GENERAL_DENOMINATOR */

#ifndef DEM_IUMPR_DEN_COND_COLDSTART
#define DEM_IUMPR_DEN_COND_COLDSTART ((Dem_IumprDenomCondIdType)0x02U)
#endif /* DEM_IUMPR_DEN_COND_COLDSTART */

#ifndef DEM_IUMPR_DEN_COND_EVAP
#define DEM_IUMPR_DEN_COND_EVAP ((Dem_IumprDenomCondIdType)0x03U)
#endif /* DEM_IUMPR_DEN_COND_EVAP */

#ifndef DEM_IUMPR_DEN_COND_500MI
#define DEM_IUMPR_DEN_COND_500MI ((Dem_IumprDenomCondIdType)0x04U)
#endif /* DEM_IUMPR_DEN_COND_500MI */


#ifndef DEM_IUMPR_DEN_STATUS_NOT_REACHED
#define DEM_IUMPR_DEN_STATUS_NOT_REACHED ((Dem_IumprDenomCondStatusType)0x00U)
#endif /* DEM_IUMPR_DEN_STATUS_NOT_REACHED */

#ifndef DEM_IUMPR_DEN_STATUS_REACHED
#define DEM_IUMPR_DEN_STATUS_REACHED ((Dem_IumprDenomCondStatusType)0x01U)
#endif /* DEM_IUMPR_DEN_STATUS_REACHED */

#ifndef DEM_IUMPR_DEN_STATUS_INHIBITED
#define DEM_IUMPR_DEN_STATUS_INHIBITED ((Dem_IumprDenomCondStatusType)0x02U)
#endif /* DEM_IUMPR_DEN_STATUS_INHIBITED */


#ifndef DEM_J1939DTC_ACTIVE
#define DEM_J1939DTC_ACTIVE ((Dem_J1939DcmDTCStatusFilterType)0x00U)
#endif /* DEM_J1939DTC_ACTIVE */

#ifndef DEM_J1939DTC_PREVIOUSLY_ACTIVE
#define DEM_J1939DTC_PREVIOUSLY_ACTIVE ((Dem_J1939DcmDTCStatusFilterType)0x01U)
#endif /* DEM_J1939DTC_PREVIOUSLY_ACTIVE */

#ifndef DEM_J1939DTC_PENDING
#define DEM_J1939DTC_PENDING ((Dem_J1939DcmDTCStatusFilterType)0x02U)
#endif /* DEM_J1939DTC_PENDING */

#ifndef DEM_J1939DTC_PERMANENT
#define DEM_J1939DTC_PERMANENT ((Dem_J1939DcmDTCStatusFilterType)0x03U)
#endif /* DEM_J1939DTC_PERMANENT */

#ifndef DEM_J1939DTC_CURRENTLY_ACTIVE
#define DEM_J1939DTC_CURRENTLY_ACTIVE ((Dem_J1939DcmDTCStatusFilterType)0x04U)
#endif /* DEM_J1939DTC_CURRENTLY_ACTIVE */


#ifndef DEM_J1939DTC_CLEAR_ACTIVE
#define DEM_J1939DTC_CLEAR_ACTIVE ((Dem_J1939DcmSetClearFilterType)0x00U)
#endif /* DEM_J1939DTC_CLEAR_ACTIVE */

#ifndef DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE
#define DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE ((Dem_J1939DcmSetClearFilterType)0x01U)
#endif /* DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE */

#ifndef DEM_J1939DTC_CLEAR_ACTIVE_AND_PREVIOUSLY_ACTIVE
#define DEM_J1939DTC_CLEAR_ACTIVE_AND_PREVIOUSLY_ACTIVE ((Dem_J1939DcmSetClearFilterType)0x02U)
#endif /* DEM_J1939DTC_CLEAR_ACTIVE_AND_PREVIOUSLY_ACTIVE */


#ifndef DEM_J1939DCM_FREEZEFRAME
#define DEM_J1939DCM_FREEZEFRAME ((Dem_J1939DcmSetFreezeFrameFilterType)0x00U)
#endif /* DEM_J1939DCM_FREEZEFRAME */

#ifndef DEM_J1939DCM_EXPANDED_FREEZEFRAME
#define DEM_J1939DCM_EXPANDED_FREEZEFRAME ((Dem_J1939DcmSetFreezeFrameFilterType)0x01U)
#endif /* DEM_J1939DCM_EXPANDED_FREEZEFRAME */

#ifndef DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME
#define DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME ((Dem_J1939DcmSetFreezeFrameFilterType)0x02U)
#endif /* DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME */


#ifndef DEM_MONITOR_STATUS_TF
#define DEM_MONITOR_STATUS_TF ((Dem_MonitorStatusType)0x01U)
#endif /* DEM_MONITOR_STATUS_TF */

#ifndef DEM_MONITOR_STATUS_TFTOC
#define DEM_MONITOR_STATUS_TFTOC ((Dem_MonitorStatusType)0x02U)
#endif /* DEM_MONITOR_STATUS_TFTOC */

#ifndef DEM_MONITOR_STATUS_PDTC
#define DEM_MONITOR_STATUS_PDTC ((Dem_MonitorStatusType)0x04U)
#endif /* DEM_MONITOR_STATUS_PDTC */

#ifndef DEM_MONITOR_STATUS_CDTC
#define DEM_MONITOR_STATUS_CDTC ((Dem_MonitorStatusType)0x08U)
#endif /* DEM_MONITOR_STATUS_CDTC */

#ifndef DEM_MONITOR_STATUS_TNCSLC
#define DEM_MONITOR_STATUS_TNCSLC ((Dem_MonitorStatusType)0x10U)
#endif /* DEM_MONITOR_STATUS_TNCSLC */

#ifndef DEM_MONITOR_STATUS_TFSLC
#define DEM_MONITOR_STATUS_TFSLC ((Dem_MonitorStatusType)0x20U)
#endif /* DEM_MONITOR_STATUS_TFSLC */

#ifndef DEM_MONITOR_STATUS_TNCTOC
#define DEM_MONITOR_STATUS_TNCTOC ((Dem_MonitorStatusType)0x40U)
#endif /* DEM_MONITOR_STATUS_TNCTOC */

#ifndef DEM_MONITOR_STATUS_WIR
#define DEM_MONITOR_STATUS_WIR ((Dem_MonitorStatusType)0x80U)
#endif /* DEM_MONITOR_STATUS_WIR */


#ifndef DEM_RECORDKIND_PRIMEM_EVENT
#define DEM_RECORDKIND_PRIMEM_EVENT ((Dem_RecordKindType)0U)
#endif /* DEM_RECORDKIND_PRIMEM_EVENT */

#ifndef DEM_RECORDKIND_PRIMEM_FAULT
#define DEM_RECORDKIND_PRIMEM_FAULT ((Dem_RecordKindType)1U)
#endif /* DEM_RECORDKIND_PRIMEM_FAULT */

#ifndef DEM_RECORDKIND_PRIMEM_FFD
#define DEM_RECORDKIND_PRIMEM_FFD ((Dem_RecordKindType)2U)
#endif /* DEM_RECORDKIND_PRIMEM_FFD */

#ifndef DEM_RECORDKIND_CLRINFO
#define DEM_RECORDKIND_CLRINFO ((Dem_RecordKindType)3U)
#endif /* DEM_RECORDKIND_CLRINFO */

#ifndef DEM_RECORDKIND_TOTALNUM
#define DEM_RECORDKIND_TOTALNUM ((Dem_RecordKindType)4U)
#endif /* DEM_RECORDKIND_TOTALNUM */


#ifndef DEM_CLEAR_OK
#define DEM_CLEAR_OK ((Dem_ReturnClearDTCType)0x00U)
#endif /* DEM_CLEAR_OK */

#ifndef DEM_CLEAR_WRONG_DTC
#define DEM_CLEAR_WRONG_DTC ((Dem_ReturnClearDTCType)0x01U)
#endif /* DEM_CLEAR_WRONG_DTC */

#ifndef DEM_CLEAR_WRONG_DTCORIGIN
#define DEM_CLEAR_WRONG_DTCORIGIN ((Dem_ReturnClearDTCType)0x02U)
#endif /* DEM_CLEAR_WRONG_DTCORIGIN */

#ifndef DEM_CLEAR_FAILED
#define DEM_CLEAR_FAILED ((Dem_ReturnClearDTCType)0x03U)
#endif /* DEM_CLEAR_FAILED */

#ifndef DEM_CLEAR_PENDING
#define DEM_CLEAR_PENDING ((Dem_ReturnClearDTCType)0x04U)
#endif /* DEM_CLEAR_PENDING */

#ifndef DEM_CLEAR_BUSY
#define DEM_CLEAR_BUSY ((Dem_ReturnClearDTCType)0x05U)
#endif /* DEM_CLEAR_BUSY */

#ifndef DEM_CLEAR_MEMORY_ERROR
#define DEM_CLEAR_MEMORY_ERROR ((Dem_ReturnClearDTCType)0x06U)
#endif /* DEM_CLEAR_MEMORY_ERROR */


#ifndef DEM_CONTROL_DTC_SETTING_OK
#define DEM_CONTROL_DTC_SETTING_OK ((Dem_ReturnControlDTCSettingType)0x00U)
#endif /* DEM_CONTROL_DTC_SETTING_OK */

#ifndef DEM_CONTROL_DTC_SETTING_N_OK
#define DEM_CONTROL_DTC_SETTING_N_OK ((Dem_ReturnControlDTCSettingType)0x01U)
#endif /* DEM_CONTROL_DTC_SETTING_N_OK */

#ifndef DEM_CONTROL_DTC_WRONG_DTCGROUP
#define DEM_CONTROL_DTC_WRONG_DTCGROUP ((Dem_ReturnControlDTCSettingType)0x02U)
#endif /* DEM_CONTROL_DTC_WRONG_DTCGROUP */


#ifndef DEM_DISABLE_DTCRECUP_OK
#define DEM_DISABLE_DTCRECUP_OK ((Dem_ReturnDisableDTCRecordUpdateType)0x00U)
#endif /* DEM_DISABLE_DTCRECUP_OK */

#ifndef DEM_DISABLE_DTCRECUP_WRONG_DTC
#define DEM_DISABLE_DTCRECUP_WRONG_DTC ((Dem_ReturnDisableDTCRecordUpdateType)0x01U)
#endif /* DEM_DISABLE_DTCRECUP_WRONG_DTC */

#ifndef DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN
#define DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN ((Dem_ReturnDisableDTCRecordUpdateType)0x02U)
#endif /* DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN */

#ifndef DEM_DISABLE_DTCRECUP_PENDING
#define DEM_DISABLE_DTCRECUP_PENDING ((Dem_ReturnDisableDTCRecordUpdateType)0x03U)
#endif /* DEM_DISABLE_DTCRECUP_PENDING */


#ifndef DEM_OCCURR_OK
#define DEM_OCCURR_OK ((Dem_ReturnGetDTCByOccurrenceTimeType)0x00U)
#endif /* DEM_OCCURR_OK */

#ifndef DEM_OCCURR_NOT_AVAILABLE
#define DEM_OCCURR_NOT_AVAILABLE ((Dem_ReturnGetDTCByOccurrenceTimeType)0x01U)
#endif /* DEM_OCCURR_NOT_AVAILABLE */


#ifndef DEM_RECORD_OK
#define DEM_RECORD_OK ((Dem_ReturnGetExtendedDataRecordByDTCType)0x00U)
#endif /* DEM_RECORD_OK */

#ifndef DEM_RECORD_WRONG_DTC
#define DEM_RECORD_WRONG_DTC ((Dem_ReturnGetExtendedDataRecordByDTCType)0x01U)
#endif /* DEM_RECORD_WRONG_DTC */

#ifndef DEM_RECORD_WRONG_DTCORIGIN
#define DEM_RECORD_WRONG_DTCORIGIN ((Dem_ReturnGetExtendedDataRecordByDTCType)0x02U)
#endif /* DEM_RECORD_WRONG_DTCORIGIN */

#ifndef DEM_RECORD_WRONG_NUMBER
#define DEM_RECORD_WRONG_NUMBER ((Dem_ReturnGetExtendedDataRecordByDTCType)0x03U)
#endif /* DEM_RECORD_WRONG_NUMBER */

#ifndef DEM_RECORD_WRONG_BUFFERSIZE
#define DEM_RECORD_WRONG_BUFFERSIZE ((Dem_ReturnGetExtendedDataRecordByDTCType)0x04U)
#endif /* DEM_RECORD_WRONG_BUFFERSIZE */

#ifndef DEM_RECORD_PENDING
#define DEM_RECORD_PENDING ((Dem_ReturnGetExtendedDataRecordByDTCType)0x05U)
#endif /* DEM_RECORD_PENDING */


#ifndef DEM_GET_FFDATABYDTC_OK
#define DEM_GET_FFDATABYDTC_OK ((Dem_ReturnGetFreezeFrameDataByDTCType)0x00U)
#endif /* DEM_GET_FFDATABYDTC_OK */

#ifndef DEM_GET_FFDATABYDTC_WRONG_DTC
#define DEM_GET_FFDATABYDTC_WRONG_DTC ((Dem_ReturnGetFreezeFrameDataByDTCType)0x01U)
#endif /* DEM_GET_FFDATABYDTC_WRONG_DTC */

#ifndef DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN
#define DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN ((Dem_ReturnGetFreezeFrameDataByDTCType)0x02U)
#endif /* DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN */

#ifndef DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER
#define DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER ((Dem_ReturnGetFreezeFrameDataByDTCType)0x03U)
#endif /* DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER */

#ifndef DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE
#define DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE ((Dem_ReturnGetFreezeFrameDataByDTCType)0x04U)
#endif /* DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE */

#ifndef DEM_GET_FFDATABYDTC_PENDING
#define DEM_GET_FFDATABYDTC_PENDING ((Dem_ReturnGetFreezeFrameDataByDTCType)0x05U)
#endif /* DEM_GET_FFDATABYDTC_PENDING */


#ifndef DEM_GET_FUNCTIONALUNITOFDTC_OK
#define DEM_GET_FUNCTIONALUNITOFDTC_OK ((Dem_ReturnGetFunctionalUnitOfDTCType)0x00U)
#endif /* DEM_GET_FUNCTIONALUNITOFDTC_OK */

#ifndef DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC
#define DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC ((Dem_ReturnGetFunctionalUnitOfDTCType)0x01U)
#endif /* DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC */


#ifndef DEM_FILTERED_OK
#define DEM_FILTERED_OK ((Dem_ReturnGetNextFilteredElementType)0x00U)
#endif /* DEM_FILTERED_OK */

#ifndef DEM_FILTERED_NO_MATCHING_ELEMENT
#define DEM_FILTERED_NO_MATCHING_ELEMENT ((Dem_ReturnGetNextFilteredElementType)0x01U)
#endif /* DEM_FILTERED_NO_MATCHING_ELEMENT */

#ifndef DEM_FILTERED_PENDING
#define DEM_FILTERED_PENDING ((Dem_ReturnGetNextFilteredElementType)0x02U)
#endif /* DEM_FILTERED_PENDING */

#ifndef DEM_FILTERED_BUFFER_TOO_SMALL
#define DEM_FILTERED_BUFFER_TOO_SMALL ((Dem_ReturnGetNextFilteredElementType)0x03U)
#endif /* DEM_FILTERED_BUFFER_TOO_SMALL */


#ifndef DEM_NUMBER_OK
#define DEM_NUMBER_OK ((Dem_ReturnGetNumberOfFilteredDTCType)0x00U)
#endif /* DEM_NUMBER_OK */

#ifndef DEM_NUMBER_FAILED
#define DEM_NUMBER_FAILED ((Dem_ReturnGetNumberOfFilteredDTCType)0x01U)
#endif /* DEM_NUMBER_FAILED */

#ifndef DEM_NUMBER_PENDING
#define DEM_NUMBER_PENDING ((Dem_ReturnGetNumberOfFilteredDTCType)0x02U)
#endif /* DEM_NUMBER_PENDING */


#ifndef DEM_GET_SEVERITYOFDTC_OK
#define DEM_GET_SEVERITYOFDTC_OK ((Dem_ReturnGetSeverityOfDTCType)0x00U)
#endif /* DEM_GET_SEVERITYOFDTC_OK */

#ifndef DEM_GET_SEVERITYOFDTC_WRONG_DTC
#define DEM_GET_SEVERITYOFDTC_WRONG_DTC ((Dem_ReturnGetSeverityOfDTCType)0x01U)
#endif /* DEM_GET_SEVERITYOFDTC_WRONG_DTC */

#ifndef DEM_GET_SEVERITYOFDTC_NOSEVERITY
#define DEM_GET_SEVERITYOFDTC_NOSEVERITY ((Dem_ReturnGetSeverityOfDTCType)0x02U)
#endif /* DEM_GET_SEVERITYOFDTC_NOSEVERITY */

#ifndef DEM_GET_SEVERITYOFDTC_PENDING
#define DEM_GET_SEVERITYOFDTC_PENDING ((Dem_ReturnGetSeverityOfDTCType)0x03U)
#endif /* DEM_GET_SEVERITYOFDTC_PENDING */


#ifndef DEM_GETSIZEBYDTC_OK
#define DEM_GETSIZEBYDTC_OK ((Dem_ReturnGetSizeOfDataByDTCType)0x00U)
#endif /* DEM_GETSIZEBYDTC_OK */

#ifndef DEM_GETSIZEBYDTC_WRONG_DTC
#define DEM_GETSIZEBYDTC_WRONG_DTC ((Dem_ReturnGetSizeOfDataByDTCType)0x01U)
#endif /* DEM_GETSIZEBYDTC_WRONG_DTC */

#ifndef DEM_GETSIZEBYDTC_WRONG_DTCORIGIN
#define DEM_GETSIZEBYDTC_WRONG_DTCORIGIN ((Dem_ReturnGetSizeOfDataByDTCType)0x02U)
#endif /* DEM_GETSIZEBYDTC_WRONG_DTCORIGIN */

#ifndef DEM_GETSIZEBYDTC_WRONG_RECNUM
#define DEM_GETSIZEBYDTC_WRONG_RECNUM ((Dem_ReturnGetSizeOfDataByDTCType)0x03U)
#endif /* DEM_GETSIZEBYDTC_WRONG_RECNUM */

#ifndef DEM_GETSIZEBYDTC_PENDING
#define DEM_GETSIZEBYDTC_PENDING ((Dem_ReturnGetSizeOfDataByDTCType)0x04U)
#endif /* DEM_GETSIZEBYDTC_PENDING */


#ifndef DEM_STATUS_OK
#define DEM_STATUS_OK ((Dem_ReturnGetStatusOfDTCType)0x00U)
#endif /* DEM_STATUS_OK */

#ifndef DEM_STATUS_WRONG_DTC
#define DEM_STATUS_WRONG_DTC ((Dem_ReturnGetStatusOfDTCType)0x01U)
#endif /* DEM_STATUS_WRONG_DTC */

#ifndef DEM_STATUS_WRONG_DTCORIGIN
#define DEM_STATUS_WRONG_DTCORIGIN ((Dem_ReturnGetStatusOfDTCType)0x02U)
#endif /* DEM_STATUS_WRONG_DTCORIGIN */

#ifndef DEM_STATUS_FAILED
#define DEM_STATUS_FAILED ((Dem_ReturnGetStatusOfDTCType)0x03U)
#endif /* DEM_STATUS_FAILED */

#ifndef DEM_STATUS_PENDING
#define DEM_STATUS_PENDING ((Dem_ReturnGetStatusOfDTCType)0x04U)
#endif /* DEM_STATUS_PENDING */


#ifndef DEM_FILTER_ACCEPTED
#define DEM_FILTER_ACCEPTED ((Dem_ReturnSetFilterType)0x00U)
#endif /* DEM_FILTER_ACCEPTED */

#ifndef DEM_WRONG_FILTER
#define DEM_WRONG_FILTER ((Dem_ReturnSetFilterType)0x01U)
#endif /* DEM_WRONG_FILTER */

#ifndef DEM_WRONG_CONDITION
#define DEM_WRONG_CONDITION ((Dem_ReturnSetFilterType)0x02U)
#endif /* DEM_WRONG_CONDITION */


#ifndef DEM_UDS_STATUS_TF
#define DEM_UDS_STATUS_TF ((Dem_UdsStatusByteType)0x01U)
#endif /* DEM_UDS_STATUS_TF */

#ifndef DEM_UDS_STATUS_TFTOC
#define DEM_UDS_STATUS_TFTOC ((Dem_UdsStatusByteType)0x02U)
#endif /* DEM_UDS_STATUS_TFTOC */

#ifndef DEM_UDS_STATUS_PDTC
#define DEM_UDS_STATUS_PDTC ((Dem_UdsStatusByteType)0x04U)
#endif /* DEM_UDS_STATUS_PDTC */

#ifndef DEM_UDS_STATUS_CDTC
#define DEM_UDS_STATUS_CDTC ((Dem_UdsStatusByteType)0x08U)
#endif /* DEM_UDS_STATUS_CDTC */

#ifndef DEM_UDS_STATUS_TNCSLC
#define DEM_UDS_STATUS_TNCSLC ((Dem_UdsStatusByteType)0x10U)
#endif /* DEM_UDS_STATUS_TNCSLC */

#ifndef DEM_UDS_STATUS_TFSLC
#define DEM_UDS_STATUS_TFSLC ((Dem_UdsStatusByteType)0x20U)
#endif /* DEM_UDS_STATUS_TFSLC */

#ifndef DEM_UDS_STATUS_TNCTOC
#define DEM_UDS_STATUS_TNCTOC ((Dem_UdsStatusByteType)0x40U)
#endif /* DEM_UDS_STATUS_TNCTOC */

#ifndef DEM_UDS_STATUS_WIR
#define DEM_UDS_STATUS_WIR ((Dem_UdsStatusByteType)0x80U)
#endif /* DEM_UDS_STATUS_WIR */

#ifndef DEM_START_STOREDDATA_OK
#define DEM_START_STOREDDATA_OK ((Dem_ReturnStartStoredDataType)0x00U)
#endif /* DEM_START_STOREDDATA_OK */

#ifndef DEM_START_STOREDDATA_PENDING
#define DEM_START_STOREDDATA_PENDING ((Dem_ReturnStartStoredDataType)0x01U)
#endif /* DEM_START_STOREDDATA_PENDING */


#ifndef DEM_GETSIZE_STOREDDATA_OK
#define DEM_GETSIZE_STOREDDATA_OK ((Dem_ReturnGetSizeOfDataByRecNumType)0x00U)
#endif /* DEM_GETSIZE_STOREDDATA_OK */

#ifndef DEM_GETSIZE_STOREDDATA_FAILED
#define DEM_GETSIZE_STOREDDATA_FAILED ((Dem_ReturnGetSizeOfDataByRecNumType)0x01U)
#endif /* DEM_GETSIZE_STOREDDATA_FAILED */

#ifndef DEM_GETSIZE_STOREDDATA_PENDING
#define DEM_GETSIZE_STOREDDATA_PENDING ((Dem_ReturnGetSizeOfDataByRecNumType)0x02U)
#endif /* DEM_GETSIZE_STOREDDATA_PENDING */

#ifndef DEM_GETSIZE_STOREDDATA_WRONG_RECNUM
#define DEM_GETSIZE_STOREDDATA_WRONG_RECNUM ((Dem_ReturnGetSizeOfDataByRecNumType)0x03U)
#endif /* DEM_GETSIZE_STOREDDATA_WRONG_RECNUM */


#ifndef DEM_GET_STOREDDATA_OK
#define DEM_GET_STOREDDATA_OK ((Dem_ReturnGetDTCStoredDataByRecNumType)0x00U)
#endif /* DEM_GET_STOREDDATA_OK */

#ifndef DEM_GET_STOREDDATA_FAILED
#define DEM_GET_STOREDDATA_FAILED ((Dem_ReturnGetDTCStoredDataByRecNumType)0x01U)
#endif /* DEM_GET_STOREDDATA_FAILED */

#ifndef DEM_GET_STOREDDATA_PENDING
#define DEM_GET_STOREDDATA_PENDING ((Dem_ReturnGetDTCStoredDataByRecNumType)0x02U)
#endif /* DEM_GET_STOREDDATA_PENDING */

#ifndef DEM_GET_STOREDDATA_WRONG_RECNUM
#define DEM_GET_STOREDDATA_WRONG_RECNUM ((Dem_ReturnGetDTCStoredDataByRecNumType)0x03U)
#endif /* DEM_GET_STOREDDATA_WRONG_RECNUM */

#ifndef DEM_GET_STOREDDATA_WRONG_BUFFERSIZE
#define DEM_GET_STOREDDATA_WRONG_BUFFERSIZE ((Dem_ReturnGetDTCStoredDataByRecNumType)0x04U)
#endif /* DEM_GET_STOREDDATA_WRONG_BUFFERSIZE */


#ifndef DEM_MISFIRE_WITHIN_FIRST1000RPM
#define DEM_MISFIRE_WITHIN_FIRST1000RPM ((Dem_MisfireConditionType)0x00U)
#endif /* DEM_MISFIRE_WITHIN_FIRST1000RPM */

#ifndef DEM_MISFIRE_AFTER_FIRST1000RPM
#define DEM_MISFIRE_AFTER_FIRST1000RPM ((Dem_MisfireConditionType)0x01U)
#endif /* DEM_MISFIRE_AFTER_FIRST1000RPM */

#ifndef DEM_MISFIRE_OUTOF_FTPCYCLE
#define DEM_MISFIRE_OUTOF_FTPCYCLE ((Dem_MisfireConditionType)0x00U)
#endif /* DEM_MISFIRE_OUTOF_FTPCYCLE */

#ifndef DEM_MISFIRE_DURING_FTPCYCLE
#define DEM_MISFIRE_DURING_FTPCYCLE ((Dem_MisfireConditionType)0x01U)
#endif /* DEM_MISFIRE_DURING_FTPCYCLE */


#ifndef DEM_EVTKIND_TYPE_NON_OBD_EVENT
#define DEM_EVTKIND_TYPE_NON_OBD_EVENT ((Dem_EventKindType)0x00U)
#endif /* DEM_EVTKIND_TYPE_NON_OBD_EVENT */

#ifndef DEM_EVTKIND_TYPE_OBD_EVENT
#define DEM_EVTKIND_TYPE_OBD_EVENT ((Dem_EventKindType)0x01U)
#endif /* DEM_EVTKIND_TYPE_OBD_EVENT */

#ifndef DEM_EVTKIND_TYPE_SIMILAR_EVENT
#define DEM_EVTKIND_TYPE_SIMILAR_EVENT ((Dem_EventKindType)0x02U)
#endif /* DEM_EVTKIND_TYPE_SIMILAR_EVENT */

#ifndef DEM_EVTKIND_TYPE_MISFIRE_EVENT
#define DEM_EVTKIND_TYPE_MISFIRE_EVENT ((Dem_EventKindType)0x04U)
#endif /* DEM_EVTKIND_TYPE_MISFIRE_EVENT */

#ifndef DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT
#define DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ((Dem_EventKindType)0x08U)
#endif /* DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT */


#ifndef DEM_UDS_STATUS_HISTORY_PASSED
#define DEM_UDS_STATUS_HISTORY_PASSED ((Dem_UdsStatusHistoryByteType)0x01U)
#endif /* DEM_UDS_STATUS_HISTORY_PASSED */

#ifndef DEM_UDS_STATUS_HISTORY_CDTC
#define DEM_UDS_STATUS_HISTORY_CDTC ((Dem_UdsStatusHistoryByteType)0x02U)
#endif /* DEM_UDS_STATUS_HISTORY_CDTC */


#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */


/****************************************************************************/
/* AUBASS definition for Array                                              */
/****************************************************************************/
#define DEM_MAX_DATA_ARRAY_SIZE                ((uint16)17U)
#define DEM_MAX_PID_DATA_ARRAY_SIZE            ((uint16)1U)
#define DEM_MAX_PFC_DATA_ARRAY_SIZE            ((uint16)1U)


#endif /* RTE_DEM_TYPE_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
