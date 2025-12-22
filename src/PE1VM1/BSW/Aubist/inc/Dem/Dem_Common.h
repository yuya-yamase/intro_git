/* Dem_Common_h(v5-10-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Common/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DEM_COMMON_H
#define DEM_COMMON_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <SchM_Dem.h>
#include <Dem/Dem_CommonTypes.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* AUTOSAR Conformity                                                       */
/****************************************************************************/
/*  typedef uint8       Dem_StorageTriggerType;  */
#define DEM_TRIGGER_ON_NONE                             ((Dem_u08_StorageTriggerType)0x00U)
#define DEM_TRIGGER_ON_CONFIRMED                        ((Dem_u08_StorageTriggerType)0x01U)     /*  used in Configurator        */
#define DEM_TRIGGER_ON_FDC_THRESHOLD                    ((Dem_u08_StorageTriggerType)0x02U)     /*  used in Configurator        */
#define DEM_TRIGGER_ON_PENDING                          ((Dem_u08_StorageTriggerType)0x04U)     /*  used in Configurator        */
#define DEM_TRIGGER_ON_TEST_FAILED_THIS_OPERATION_CYCLE ((Dem_u08_StorageTriggerType)0x08U)     /*  used in Configurator        */
#define DEM_TRIGGER_ON_TRIGGERTYPE_MASK                 ((Dem_u08_StorageTriggerType)0x0FU)

#define DEM_TRIGGER_ON_UPD_TEST_FAILED                  ((Dem_u08_StorageTriggerType)0x80U)
#define DEM_TRIGGER_ON_UPDATETYPE_MASK                  ((Dem_u08_StorageTriggerType)0xC0U)


/* typedef uint8        Dem valid trigger definition */
#define DEM_VALID_TRIGGER_NONE                  ((Dem_u08_FFValidTriggerType)0x00U)
#define DEM_VALID_TRIGGER_CONFIRMED             ((Dem_u08_FFValidTriggerType)0x01U)
#define DEM_VALID_TRIGGER_FDC_THRESHOLD         ((Dem_u08_FFValidTriggerType)0x02U)
#define DEM_VALID_TRIGGER_PENDING               ((Dem_u08_FFValidTriggerType)0x04U)
#define DEM_VALID_TRIGGER_TFTOC                 ((Dem_u08_FFValidTriggerType)0x08U)
#define DEM_VALID_TRIGGER_TEST_FAILED           ((Dem_u08_FFValidTriggerType)0x40U)
#define DEM_VALID_TRIGGER_TEST_FAILED_AT_CDTC   ((Dem_u08_FFValidTriggerType)0x80U)

/* typedef uint8        request caller type.         */
#define DEM_CALLER_NONE                     ((Dem_u08_RequestCallerType)0x00U)
#define DEM_CALLER_CDD                      ((Dem_u08_RequestCallerType)0x01U)
#define DEM_CALLER_DCM                      ((Dem_u08_RequestCallerType)0x02U)
#define DEM_CALLER_SWC                      ((Dem_u08_RequestCallerType)0x03U)

/*  typedef uint8       Dem_OperationCycleType; */
#define DEM_OPCYC_IGNITION                      ((Dem_u08_OpCycleKindType)0x00U)        /*  used in Configurator        */
#define DEM_OPCYC_OTHER                         ((Dem_u08_OpCycleKindType)0x02U)        /*  used in Configurator        */
/*  DEM_OPCYC_OBD_DCY is not output.    */

/*  typedef uint8       Dem_u08_UpdateRecordType;   */
#define DEM_UPDATE_RECORD_NO                    ((Dem_u08_UpdateRecordType)0x00U)       /*  used in Configurator        */
#define DEM_UPDATE_RECORD_YES                   ((Dem_u08_UpdateRecordType)0x01U)       /*  used in Configurator        */

/*  typedef uint8       DemClearDTCBehaviorType;    */
#define DEM_CLRRESP_NONVOLATILE_FINISH          ((Dem_u08_ClearDTCBehaviorType)0x00U)       /*  used in Configurator        */
#define DEM_CLRRESP_NONVOLATILE_TRIGGER         ((Dem_u08_ClearDTCBehaviorType)0x01U)       /*  used in Configurator        */
#define DEM_CLRRESP_VOLATILE                    ((Dem_u08_ClearDTCBehaviorType)0x02U)       /*  used in Configurator        */

/*  typedef uint8       DemEventDisplacementStrategyType;   */
#define DEM_DISPLACEMENT_FULL                   ((Dem_u08_EventDisplacementStrategyType)0x00U)      /*  used in Configurator        */
#define DEM_DISPLACEMENT_NONE                   ((Dem_u08_EventDisplacementStrategyType)0x01U)      /*  used in Configurator        */
#define DEM_DISPLACEMENT_PRIO_OCC               ((Dem_u08_EventDisplacementStrategyType)0x02U)      /*  used in Configurator        */
#define DEM_DISPLACEMENT_PRIO                   ((Dem_u08_EventDisplacementStrategyType)0x03U)      /*  used in Configurator        */

/*  typedef uint8       DemOBDCompressionType  */
#define DEM_HD_OBD_TYPE                         ((Dem_u08_OBDCompressionType)0x00U)     /*  used in Configurator        */
#define DEM_WWH_OBD_TYPE                        ((Dem_u08_OBDCompressionType)0x01U)     /*  used in Configurator        */

/*  uint8       DemIUMPRDenGroup  */
#define DEM_IUMPR_DEN_500MILL                   ((Dem_u08_IUMPRDenGroupType)0x00U)      /*  used in Configurator        */
#define DEM_IUMPR_DEN_COLDSTART                 ((Dem_u08_IUMPRDenGroupType)0x01U)      /*  used in Configurator        */
#define DEM_IUMPR_DEN_EVAP                      ((Dem_u08_IUMPRDenGroupType)0x02U)      /*  used in Configurator        */
#define DEM_IUMPR_DEN_NONE                      ((Dem_u08_IUMPRDenGroupType)0x03U)      /*  used in Configurator        */
#define DEM_IUMPR_DEN_ONLY_PHYS_API             ((Dem_u08_IUMPRDenGroupType)0x04U)      /*  used in Configurator        */
#define DEM_IUMPR_DEN_PHYS_API                  ((Dem_u08_IUMPRDenGroupType)0x05U)      /*  used in Configurator        */

/*  uint8       DemRatioKind  */
#define DEM_RATIO_API                           ((Dem_u08_IUMPRRatioKindType)0x00U)     /*  used in Configurator        */
#define DEM_RATIO_OBSERVER                      ((Dem_u08_IUMPRRatioKindType)0x01U)     /*  used in Configurator        */

/* typedef uint8    type of PID30 update timing      */
#define DEM_WARMUPCYCLE_UPDATE                  ((Dem_u08_UpdateTimingOfPID30Type)0x00U)        /*  used in Configurator        */
#define DEM_WARMUPCONDITION_FULFILLED           ((Dem_u08_UpdateTimingOfPID30Type)0x01U)        /*  used in Configurator        */

/* uint8       DemOBDClearPFCCycleStartCycle definition */
#define DEM_CLEARPFCCYCLE_THISCYCLE             ((Dem_u08_ClearPFCCycleType)0x00U)              /*  used in Configurator        */
#define DEM_CLEARPFCCYCLE_NEXTIGCYCLE           ((Dem_u08_ClearPFCCycleType)0x01U)              /*  used in Configurator        */

/* uint8       DemMisfireSimilarConditionStoredTiming definition */
#define DEM_MF_SIMCOND_FIRSTEXCEEDANCE          ((Dem_u08_MisfSimCondStoredTimingType)0x00U)    /*  used in Configurator        */
#define DEM_MF_SIMCOND_PENDINGDTC               ((Dem_u08_MisfSimCondStoredTimingType)0x01U)    /*  used in Configurator        */

/* uint8       DemMisfireJudgeFreezeFrameCylinder definition */
#define DEM_MF_JUDGE_FFD_CYL_ACCUMULATED        ((Dem_u08_MisfJudgeFFCylinderType)0x00U)    /*  used in Configurator        */
#define DEM_MF_JUDGE_FFD_CYL_REQUESTED          ((Dem_u08_MisfJudgeFFCylinderType)0x01U)    /*  used in Configurator        */

/* uint8       DemMisfireFilteredEDRN92 definition */
#define DEM_MF_RM_CYL_NOT_OUTPUT                ((Dem_u08_MisfireFilteredEDRType)0x00U)     /*  used in Configurator        */
#define DEM_MF_RM_CYL_OUTPUT                    ((Dem_u08_MisfireFilteredEDRType)0x01U)     /*  used in Configurator        */

/* uint8       Dem_u08_EventPriorityType definition */
#define DEM_PRIORITY_INITIAL                    ((Dem_u08_EventPriorityType)0U)
#define DEM_PRIORITY_OBD_OBDFFD                 ((Dem_u08_EventPriorityType)10U)
#define DEM_PRIORITY_OBD_MIL                    ((Dem_u08_EventPriorityType)11U)
#define DEM_PRIORITY_OBD_DEFAULT                ((Dem_u08_EventPriorityType)20U)                /*  used in Configurator        */
#define DEM_PRIORITY_NONOBD_DEFAULT             ((Dem_u08_EventPriorityType)239U)               /*  used in Configurator        */
#define DEM_PRIORITY_EVT_AVL                    ((Dem_u08_EventPriorityType)255U)

#define DEM_PRIORITY_RESERVED_HI_MIN            ((Dem_u08_EventPriorityType)10U)
#define DEM_PRIORITY_RESERVED_HI_MAX            ((Dem_u08_EventPriorityType)19U)
#define DEM_PRIORITY_RESERVED_LO_MIN            ((Dem_u08_EventPriorityType)240U)
#define DEM_PRIORITY_RESERVED_LO_MAX            ((Dem_u08_EventPriorityType)255U)

/*  calibaration value                              */
#define     DEM_CALIB_FAILURECYCLECNT_THRESHOLD_MIN                 ((Dem_u08_FailureCounterType)1U)
#define     DEM_CALIB_HEALINGCYCLECNT_THRESHOLD_MIN                 ((Dem_u08_HealingCounterType)1U)
#define     DEM_CALIB_AGINGCYCLECNT_THRESHOLD_MIN                   ((Dem_u08_AgingCounterType)1U)
#define     DEM_CALIB_TIMEAGINGCNT_THRESHOLD_MIN                    ((Dem_u16_WWHOBDTimeAgingCounterType)1U)
#define     DEM_CALIB_B1CNT_THRESHOLD_MIN                           ((Dem_u32_B1CounterType)1U)
#define     DEM_CALIB_SIMPENDINGCLEARCYCLECNT_THRESHOLD_MIN         ((Dem_u08_SimilarPendingClearCounterType)1U)

/* uint8       Dem_u08_ReadinessGroupIdType definition */
/* defined at J1979DA.                  */
#define DEM_OBD_RDY_NONE                   ((Dem_u08_ReadinessGroupIdType)0x00U)           /*  used in Configurator        */
#define DEM_OBD_RDY_CAT                    ((Dem_u08_ReadinessGroupIdType)0x01U)           /*  used in Configurator        */
#define DEM_OBD_RDY_HTCAT                  ((Dem_u08_ReadinessGroupIdType)0x02U)           /*  used in Configurator        */
#define DEM_OBD_RDY_MISF                   ((Dem_u08_ReadinessGroupIdType)0x03U)           /*  used in Configurator        */
#define DEM_OBD_RDY_EVAP                   ((Dem_u08_ReadinessGroupIdType)0x04U)           /*  used in Configurator        */
#define DEM_OBD_RDY_SECAIR                 ((Dem_u08_ReadinessGroupIdType)0x05U)           /*  used in Configurator        */
#define DEM_OBD_RDY_FLSYS                  ((Dem_u08_ReadinessGroupIdType)0x06U)           /*  used in Configurator        */
#define DEM_OBD_RDY_EGSENS                 ((Dem_u08_ReadinessGroupIdType)0x07U)           /*  used in Configurator        */
#define DEM_OBD_RDY_EGR                    ((Dem_u08_ReadinessGroupIdType)0x08U)           /*  used in Configurator        */
#define DEM_OBD_RDY_PCV                    ((Dem_u08_ReadinessGroupIdType)0x09U)           /*  used in Configurator        */
#define DEM_OBD_RDY_ECS                    ((Dem_u08_ReadinessGroupIdType)0x0AU)           /*  used in Configurator        */
#define DEM_OBD_RDY_CSER                   ((Dem_u08_ReadinessGroupIdType)0x0BU)           /*  used in Configurator        */
#define DEM_OBD_RDY_VVT                    ((Dem_u08_ReadinessGroupIdType)0x0CU)           /*  used in Configurator        */
#define DEM_OBD_RDY_DOR                    ((Dem_u08_ReadinessGroupIdType)0x0DU)           /*  used in Configurator        */
#define DEM_OBD_RDY_CMPRCMPT               ((Dem_u08_ReadinessGroupIdType)0x0EU)           /*  used in Configurator        */
#define DEM_OBD_RDY_OTHER                  ((Dem_u08_ReadinessGroupIdType)0x0FU)           /*  used in Configurator        */
#define DEM_OBD_RDY_HCCAT                  ((Dem_u08_ReadinessGroupIdType)0x10U)           /*  used in Configurator        */
#define DEM_OBD_RDY_NOXCAT                 ((Dem_u08_ReadinessGroupIdType)0x11U)           /*  used in Configurator        */
#define DEM_OBD_RDY_BOOSTPR                ((Dem_u08_ReadinessGroupIdType)0x12U)           /*  used in Configurator        */
#define DEM_OBD_RDY_NOXADSORB              ((Dem_u08_ReadinessGroupIdType)0x13U)           /*  used in Configurator        */
#define DEM_OBD_RDY_PMFLT                  ((Dem_u08_ReadinessGroupIdType)0x14U)           /*  used in Configurator        */

/*  0x15-0xFF : Reserved                        */
/*  - definition value for configration.        */
/* only use calculate Readiness.        */
#define DEM_OBD_RDY_O2SENS                 ((Dem_u08_ReadinessGroupIdType)0x21U)           /*  used in Configurator        */
#define DEM_OBD_RDY_O2SENSHT               ((Dem_u08_ReadinessGroupIdType)0x22U)           /*  used in Configurator        */
/* only use calculate Readiness(mix).   */
#define DEM_OBD_RDY_EGR_VVT                ((Dem_u08_ReadinessGroupIdType)0x41U)           /*  used in Configurator        */
#define DEM_OBD_RDY_NOXCAT_NADS            ((Dem_u08_ReadinessGroupIdType)0x42U)           /*  used in Configurator        */

/* invalid ID value.                    */
#define DEM_OBD_RDY_INVALID                ((Dem_u08_ReadinessGroupIdType)0xFFU)           /*  used in Configurator        */

/* no use ReadinessGroupId.             */
/*       DEM_OBD_RDY_AC                 */
/*       DEM_OBD_RDY_FLSYS_NONCONT : setting to DEM_OBD_RDY_FLSYS table.  */

/* DTCOrigin : memory identifier mask.  */
#define DEM_DTC_ORIGIN_MEMORYIDENTIFIER_MASK        ((Dem_DTCOriginType)0x00FFU)

/*  for DemStatusBitHandlingTestFailedSinceLastClear / DemResetConfirmedBitOnOverflow       */
typedef uint8       Dem_u08_DTCStatusBitHandlingType;
#define DEM_STATUS_BIT_NORMAL                   ((Dem_u08_DTCStatusBitHandlingType)0x00U)       /*  used in Configurator        */
#define DEM_STATUS_BIT_DISPLACEMENT             ((Dem_u08_DTCStatusBitHandlingType)0x01U)       /*  used in Configurator        */
#define DEM_STATUS_BIT_AGING_AND_DISPLACEMENT   ((Dem_u08_DTCStatusBitHandlingType)0x02U)       /*  used in Configurator        */

typedef uint8       Dem_u08_ResetConfirmedBitOnOverflowType;
#define DEM_STATUS_BIT_NO_RESET                 ((Dem_u08_ResetConfirmedBitOnOverflowType)0x00U)        /*  used in Configurator        */
#define DEM_STATUS_BIT_RESET_CDTC_WITH_PDTC     ((Dem_u08_ResetConfirmedBitOnOverflowType)0x01U)        /*  used in Configurator        */

/*--------------------------------------*/
/* Interface output switching type      */
/*--------------------------------------*/
typedef uint8       Dem_u08_ClearDTCByDcmDuringInitializingType;
#define DEM_CLEARDTC_NOT_ACCEPT             ((Dem_u08_ClearDTCByDcmDuringInitializingType)0x00U)    /*  used in Configurator        */
#define DEM_CLEARDTC_ACCEPT                 ((Dem_u08_ClearDTCByDcmDuringInitializingType)0x01U)    /*  used in Configurator        */

typedef uint8       Dem_u08_NotConfiguredEDRBehaviorType;
#define DEM_EDRNUM_NOT_ACCEPT               ((Dem_u08_NotConfiguredEDRBehaviorType)0x00U)           /*  used in Configurator        */
#define DEM_EDRNUM_ACCEPT                   ((Dem_u08_NotConfiguredEDRBehaviorType)0x01U)           /*  used in Configurator        */

typedef uint8       Dem_u08_EDRBehaviorAt0xFEType;
#define DEM_EDRNUM_FE_ALWAYS_NOT_SUPPORT    ((Dem_u08_EDRBehaviorAt0xFEType)0x00U)                  /*  used in Configurator        */
#define DEM_EDRNUM_FE_SUPPORT_RANGE_90_9F   ((Dem_u08_EDRBehaviorAt0xFEType)0x01U)                  /*  used in Configurator        */
#define DEM_EDRNUM_FE_SUPPORT_RANGE_90_EF   ((Dem_u08_EDRBehaviorAt0xFEType)0x02U)                  /*  used in Configurator        */

typedef uint8       Dem_u08_TSFFStorePatternType;                                                   /*  DemTimeSeriesFreezeFrameStorePattern    */
#define DEM_TSFFD_STORE_PATTERN1                ((Dem_u08_TSFFStorePatternType)0x00U)               /*  used in Configurator        */
#define DEM_TSFFD_STORE_PATTERN2                ((Dem_u08_TSFFStorePatternType)0x11U)               /*  used in Configurator        */

/****************************************************************************/
/* AUBIST definition                                                        */
/****************************************************************************/
/*  typedef uint16     Dem_EventIdType[SWS_Dem_00925] range */
#define DEM_EVENT_ID_MIN                        ((Dem_EventIdType)1U)

/* typdedef uint8       OperationCycleIndex value */
#define DEM_OPERATION_CYCLE_INDEX_INVALID       ((Dem_u08_OpCycleIndexType)0xFFU)
#define DEM_OPERATION_CYCLE_INDEX_OBD_DCY       ((Dem_u08_OpCycleIndexType)0xFEU)

/*  typedef uint32      DemDtcValue[ECUC_Dem_00887] range */
#define DEM_DTC_VALUE_MIN                       ((Dem_u32_DTCValueType)0x00000001U)
#define DEM_DTC_VALUE_MAX                       ((Dem_u32_DTCValueType)0x00FFFFFEU)
#define DEM_DTC_VALUE_ALL                       ((Dem_u32_DTCValueType)0x00FFFFFFU)
#define DEM_DTC_VALUE_INVALID                   ((Dem_u32_DTCValueType)0xFFFFFFFFU)

/* typedef uint8        Dem_UdsStatusByteType definition */
#define DEM_DTCSTATUS_BYTE_DEFAULT              (DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TNCTOC)/* only bit4 and bit6 are True  */
#define DEM_DTCSTATUS_BYTE_ALL_OFF              ((Dem_UdsStatusByteType)0x00U)

/*------------------------------------------------------*/
/* typedef uint8        Dem_UdsStatusByteType           */
/*      #define                 bit pos     value       */
/*      DEM_UDS_STATUS_TF       bit0        0x01        */
/*      DEM_UDS_STATUS_TFTOC    bit1        0x02        */
/*      DEM_UDS_STATUS_PDTC     bit2        0x04        */
/*      DEM_UDS_STATUS_CDTC     bit3        0x08        */
/*      DEM_UDS_STATUS_TNCSLC   bit4        0x10        */
/*      DEM_UDS_STATUS_TFSLC    bit5        0x20        */
/*      DEM_UDS_STATUS_TNCTOC   bit6        0x40        */
/*      DEM_UDS_STATUS_WIR      bit7        0x80        */
/*------------------------------------------------------*/

/*------------------------------------------------------*/
/* typedef uint8        Extend DTC status definition */

/*      DEM_UDS_STATUS_HISTORY_PASSED                           0x01    */
/*      DEM_UDS_STATUS_HISTORY_CDTC                             0x02    */
#define DEM_DTCSTATUSEX_STATUS_INDICATOR                        ((Dem_u08_DTCStatusExType)0x04U)
#define DEM_DTCSTATUSEX_STATUS_PREDICTIVE_FAULT                 ((Dem_u08_DTCStatusExType)0x08U)
#define DEM_DTCSTATUSEX_STATUS_TFTOC_IN_HEALINGCYCLE            ((Dem_u08_DTCStatusExType)0x10U)       /*  bit1 in Healing cycle  */
#define DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE           ((Dem_u08_DTCStatusExType)0x20U)       /*  bit6 in Healing cycle  */
#define DEM_DTCSTATUSEX_STATUS_TFTOC_IN_AGINGCYCLE              ((Dem_u08_DTCStatusExType)0x40U)       /*  bit1 in Aging cycle  */
#define DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_AGINGCYCLE             ((Dem_u08_DTCStatusExType)0x80U)       /*  bit6 in Aging cycle  */

#define DEM_DTCSTATUSEX_BYTE_MASK_HISTORY                       ( DEM_UDS_STATUS_HISTORY_CDTC | DEM_UDS_STATUS_HISTORY_PASSED )
#define DEM_DTCSTATUSEX_BYTE_DEFAULT                            ( DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_HEALINGCYCLE | DEM_DTCSTATUSEX_STATUS_TNCTOC_IN_AGINGCYCLE )  /*  True : bit6 in Healing/Aging cycle   */
#define DEM_DTCSTATUSEX_BYTE_ALL_OFF                            ((Dem_u08_DTCStatusExType)0x00U)

/*------------------------------------------------------*/
/* typedef uint8        Extend DTC status2 definition   */
#define DEM_DTCSTATUSEX2_STATUS_TNCTOC_IN_PFCCLEARCONDCYCLE     ((Dem_u08_DTCStatusEx2Type)0x01U)           /*  bit6 in PFCClearCondition cycle  */
#define DEM_DTCSTATUSEX2_STATUS_TFTOC_IN_FAILURECYCLE           ((Dem_u08_DTCStatusEx2Type)0x02U)           /*  bit1 in Failure cycle            */
#define DEM_DTCSTATUSEX2_STATUS_AGING_HISTORY                   ((Dem_u08_DTCStatusEx2Type)0x04U)           /*  Aging history                    */
#define DEM_DTCSTATUSEX2_STATUS_INDICATOR_AT_CYCLESTART         ((Dem_u08_DTCStatusEx2Type)0x08U)           /*  ActiveFault at cycle start       */
#define DEM_DTCSTATUSEX2_STATUS_CONTINUOUS_MI_HISTORY           ((Dem_u08_DTCStatusEx2Type)0x10U)           /*  Continuous-MI History            */
#define DEM_DTCSTATUSEX2_STATUS_MISF_PENDINGOFEMISSION          ((Dem_u08_DTCStatusEx2Type)0x20U)           /*  Misfire PendingOfEmission        */
#define DEM_DTCSTATUSEX2_STATUS_EVENTDISABLE                    ((Dem_u08_DTCStatusEx2Type)0x80U)           /*  SetEventDisable                         */
#define DEM_DTCSTATUSEX2_BYTE_DEFAULT                           ( DEM_DTCSTATUSEX2_STATUS_TNCTOC_IN_PFCCLEARCONDCYCLE )     /*  True : bit6 in PFCClearCondition cycle  */
#define DEM_DTCSTATUSEX2_BYTE_ALL_OFF                           ((Dem_u08_DTCStatusEx2Type)0x00U)


#define DEM_DTCSEVERITY_BYTE_DEFAULT            (DEM_DTC_CLASS_0)
#define DEM_DTCSEVERITY_BYTE_ALL_OFF            ((Dem_DTCSeverityType)0x00U)

/* FailureCycle Counter      */
#define DEM_FAILURECYCLE_COUNT_INITIAL_VALUE    ((Dem_u08_FailureCounterType)0x00U)

/* EventOccurrence Counter   */
#define DEM_EVENT_OCCURRENCE_COUNT_INITIAL_VALUE    ((Dem_u08_EventOccurrenceCounterType)0x00U)
#define DEM_EVENT_OCCURRENCE_COUNT_MAX_VALUE        ((Dem_u08_EventOccurrenceCounterType)0x7EU)

/* Aging / Healing Counter   */
#define DEM_HEALING_COUNT_INITIAL_VALUE         ((Dem_u08_HealingCounterType)0x00U)
#define DEM_HEALING_COUNT_MAX_VALUE             ((Dem_u08_HealingCounterType)0xFFU)

#define DEM_AGING_COUNT_INITIAL_VALUE           ((Dem_u08_AgingCounterType)0x00U)
#define DEM_AGING_COUNT_MAX_VALUE               ((Dem_u08_AgingCounterType)0xFFU)

#define DEM_TIME_AGING_COUNT_INITIAL_VALUE      ((Dem_u16_WWHOBDTimeAgingCounterType)0x0000U)
#define DEM_TIME_AGING_COUNT_MAX_VALUE          ((Dem_u16_WWHOBDTimeAgingCounterType)0xFFFFU)

/*  OperationCycleState for Notice condition.       */
#define DEM_CYCLE_NOTIFY_START      ( (Dem_OperationCycleStateType)0x00U )
#define DEM_CYCLE_NOTIFY_END        ( (Dem_OperationCycleStateType)0x01U )

#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
#define DEM_CYCLE_NOTIFY_INITIAL    ( (Dem_OperationCycleStateType)0xFFU )
#endif  /*   ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )          */

/* typedef uint8        PID WarmUpCnt MAX */
#define DEM_PID_WUCCNT_MAX          ((uint8)0xFFU) /* PID30 value max       */

/* typedef uint8        Dem Freeze Frame Reocrd Number range */
#define DEM_FFRECNUM_FOR_OBD                    ((Dem_u08_FFRecordNumberType)0x00U)
#define DEM_FFRECNUM_FOR_OBD_FIRST              ((Dem_u08_FFRecordNumberType)0x00U)
#define DEM_FFRECNUM_FOR_OBD_LATEST             ((Dem_u08_FFRecordNumberType)0xF0U)
#define DEM_FFRECNUM_FOR_NONOBD_START           ((Dem_u08_FFRecordNumberType)0x01U)
#define DEM_FFRECNUM_ALL_RECORDS                ((Dem_u08_FFRecordNumberType)0xFFU)
#define DEM_FFRECNUM_INVALID                    ((Dem_u08_FFRecordNumberType)0xFFU)

/* typedef uint8        Dem Extended Data Reocrd Number */
#define DEM_EDR_NUMBER_INVALID                  ((uint8)0xFFU)

/* typedef uint8        Dem Data Element kind */
#define DEM_DATA_ELEMENT_KIND_CS_EXTERNAL       ((Dem_u08_DataElementKindType)0x00U)
#define DEM_DATA_ELEMENT_KIND_INTERNAL          ((Dem_u08_DataElementKindType)0x01U)
#define DEM_DATA_ELEMENT_KIND_INVALID           ((Dem_u08_DataElementKindType)0xFFU)

/*  uint8       Data element index                    */
#define DEM_PID_DATAELEMENT_INDEX_FIRST         ((Dem_u08_DtElNumPerDIDIndexType)0x00U)

/* typedef uint16   Mask of DID value to PID value.  */
#define DEM_DID_TO_PID_MASK                     ((Dem_u16_DIDNumberType)0x00FFU)

/* typedef uint16   IUMPR Counter initial value.     */
#define DEM_IUMPR_COUNTER_INITVALUE             ((Dem_u16_IUMPRCycleCounterType)0x0000U)

#define DEM_IUMPR_NODI_SIZE                     ((uint8)0x01U)

#define DEM_NVBLOCK_FACTORY_VALUE               ((uint8)0xFFU)

/* typedef uint16   Mask of EventIndex in UserDefinedMemory.  */
#define DEM_EVENT_INDEX_USERDEFMEM_MASK         ((Dem_u16_EventCtrlIndexType)0x8000U)

/* typedef uint8    DemUserDefinedMemoryType value.  */
#define DEM_MEMORYTYPE_SYNCEVENT                ((Dem_u08_UserDefinedMemoryType)0x00U)    /*  used in Configurator        */
#define DEM_MEMORYTYPE_ASYNCEVENT               ((Dem_u08_UserDefinedMemoryType)0x01U)    /*  used in Configurator        */
#define DEM_MEMORYTYPE_EXTERNAL                   ((Dem_u08_UserDefinedMemoryType)0x02U)    /*  used in Configurator        */
#define DEM_MEMORYTYPE_INVALID                  ((Dem_u08_UserDefinedMemoryType)0xFFU)

/* uint8       Dem_MisfireCylinderType definition */
#define DEM_MISFIRE_CYLINDER_INVALID            ((Dem_MisfireCylinderType)0xFFFFU)

/* uint8       Dem_MisfireCylinderNumberType definition :   cylinder number */
#define DEM_MISFIRE_CYL_NUM_RM                  ((Dem_MisfireCylinderNumberType)0x00U)
#define DEM_MISFIRE_CYL_NUM_INVALID             ((Dem_MisfireCylinderNumberType)0xFFU)

/* uint8       Dem_MisfireCylinderType definition       :   cylinder bit    */
#define DEM_MISFIRE_CYLINDER_NON                ((Dem_MisfireCylinderType)0x0000U)
#define DEM_MISFIRE_CYLINDER_RM                 ((Dem_MisfireCylinderType)0x0001U)
#define DEM_MISFIRE_CHECK_CYLINDER_BIT          ((Dem_MisfireCylinderType)0x0001U)

#define DEM_MISFIRE_CYLINDER_ALLBITOFF          ((Dem_MisfireCylinderType)0x0000U)
#define DEM_MISFIRE_CYLINDER_ALLBITON           ((Dem_MisfireCylinderType)0xFFFFU)

/* uint8       Dem_u08_SimilarExceedanceCounterType definition              */
#define DEM_SIMILAR_EXCESSCONTERTHRESHOLD              ((Dem_u08_SimilarExceedanceCounterType)0x04U)
#define DEM_SIMILAR_UNUSED_EXCESSCONTERTHRESHOLD       ((Dem_u08_SimilarExceedanceCounterType)0x01U)

/* uint8       Dem_u08_MisfExceedanceCounterType definition                 */
#define DEM_MISFIRE_CAT_EXCESSCONTERTHRESHOLD          ((Dem_u08_MisfExceedanceCounterType)0x03U)
#define DEM_MISFIRE_EMISSION_EXCESSCONTERTHRESHOLD     ((Dem_u08_MisfExceedanceCounterType)0x04U)
#define DEM_MISFIRE_UNUSED_EXCESSCONTERTHRESHOLD       ((Dem_u08_MisfExceedanceCounterType)0x01U)

/****************************************************************************/
/* Dem internal return type                                                 */
/****************************************************************************/
#define DEM_IRT_OK                              ((Dem_u08_InternalReturnType)0x00U)
#define DEM_IRT_NG                              ((Dem_u08_InternalReturnType)0x01U)
#define DEM_IRT_NO_MATCHING_ELEMENT             ((Dem_u08_InternalReturnType)0x02U)
#define DEM_IRT_PENDING                         ((Dem_u08_InternalReturnType)0x03U)
#define DEM_IRT_BUSY                            ((Dem_u08_InternalReturnType)0x04U)
#define DEM_IRT_MEMORY_ERROR                    ((Dem_u08_InternalReturnType)0x05U)
#define DEM_IRT_MEMORY_OVERFLOW                 ((Dem_u08_InternalReturnType)0x06U)
#define DEM_IRT_PARAM_DATA                      ((Dem_u08_InternalReturnType)0x12U)
#define DEM_IRT_UNINIT                          ((Dem_u08_InternalReturnType)0x20U)
#define DEM_IRT_NODATAAVAILABLE                 ((Dem_u08_InternalReturnType)0x30U)
#define DEM_IRT_WRONG_RECORDNUMBER              ((Dem_u08_InternalReturnType)0x31U)
#define DEM_IRT_WRONG_DIDNUMBER                 ((Dem_u08_InternalReturnType)0x32U)
#define DEM_IRT_WRONG_DTC                       ((Dem_u08_InternalReturnType)0x33U)
#define DEM_IRT_WRONG_DTCORIGIN                 ((Dem_u08_InternalReturnType)0x34U)
#define DEM_IRT_WRONG_DTCGROUP                  ((Dem_u08_InternalReturnType)0x35U)
#define DEM_IRT_WRONG_BUFFERSIZE                ((Dem_u08_InternalReturnType)0x36U)
#define DEM_IRT_EXTERNAL_MEMORY                 ((Dem_u08_InternalReturnType)0x37U)
#define DEM_IRT_WRONG_CONDITION                 ((Dem_u08_InternalReturnType)0x40U)
#define DEM_IRT_FAILED_ENQUEUE                  ((Dem_u08_InternalReturnType)0x50U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef P2FUNC( void, DEM_CODE, DemCallbackEventStatusChangedFncPTR )
(
    VAR( Dem_EventIdType,AUTOMATIC ) EventId,
    VAR( Dem_UdsStatusByteType,AUTOMATIC ) EventStatusByteOld,
    VAR( Dem_UdsStatusByteType,AUTOMATIC ) EventStatusByteNew
);

typedef P2FUNC( Std_ReturnType, DEM_CODE, DemCallbackInitMForEFncPTR )
(
    VAR( Dem_InitMonitorReasonType, AUTOMATIC ) InitMonitorReason
);

#if ( DEM_READFUNC_MONITORDATA_SUPPORT == STD_ON )
typedef P2FUNC( Std_ReturnType, DEM_CODE, DemDataElementReadFncPTR )
(
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) Buffer,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0
);
#endif /* (DEM_READFUNC_MONITORDATA_SUPPORT == STD_ON) */
#if ( DEM_READFUNC_MONITORDATA_SUPPORT == STD_OFF )
typedef P2FUNC( Std_ReturnType, DEM_CODE, DemDataElementReadFncPTR )
(
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) Buffer
);
#endif /* ( DEM_READFUNC_MONITORDATA_SUPPORT == STD_OFF ) */

typedef P2FUNC( Dem_u08_InternalReturnType, DEM_CODE, DemInternalDataElementReadFncPTR )
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_GetExtendDataModeType, AUTOMATIC ) GetExtendDataMode,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) BufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);

typedef P2FUNC( Std_ReturnType, DEM_CODE, DemFreezeFrameReadFncPTR )
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) BufferPtr,
    VAR( uint16, AUTOMATIC ) BufSize
);

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* DEM_COMMON_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

