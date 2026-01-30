/* Dem_CommonTypes_h(v5-10-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CommonTypes/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DEM_COMMONTYPES_H
#define DEM_COMMONTYPES_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <SchM_Dem.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*-------------------*/
/* boolean type      */
/*-------------------*/
typedef uint8                 Dem_u08_DemBooleanType;
#define DEM_BOOLEAN_TRUE                        ((Dem_u08_DemBooleanType)0xA5)
#define DEM_BOOLEAN_FALSE                       ((Dem_u08_DemBooleanType)0x5A)


/*-------------------*/
/* index type        */
/*-------------------*/
typedef Dem_EventIdType       Dem_EventParameterConfigIdType;        /*  for Event Configure Id                  */
typedef Dem_EventIdType       Dem_u16_EventCtrlIndexType;                /*  for Event index                         */
typedef Dem_EventIdType       Dem_u16_EventStrgIndexType;                /*  for Event index                         */
typedef Dem_EventIdType       Dem_u16_UdmEventIndexType;                 /*  for UserDefinedMemory Event index      */
typedef Dem_EventIdType       Dem_u16_UdmEventStrgIndexType;             /*  for UserDefinedMemory Event index      */

typedef Dem_EventIdType       Dem_u16_SimilarStrgIndexType;         /*  for Event index(similar)                         */
typedef Dem_EventIdType       Dem_u16_MisfireStrgIndexType;              /*  for Event index(misfire)                         */

/*  typedef Dem_u16_EventXXXXIndexType      EventIndex range */
#define DEM_EVENTSTRGINDEX_MIN                 ((Dem_u16_EventStrgIndexType)0x0000U)
#define DEM_EVENTCTRLINDEX_INVALID             ((Dem_u16_EventCtrlIndexType)0xFFFFU)
#define DEM_EVENTSTRGINDEX_INVALID             ((Dem_u16_EventStrgIndexType)0xFFFFU)
#define DEM_UDMEVENTINDEX_INVALID              ((Dem_u16_UdmEventIndexType)0xFFFFU)

#define DEM_MISFIRE_STRGINDEX_INVALID          ((Dem_u16_MisfireStrgIndexType)0xFFFFU)

typedef Dem_EventIdType       Dem_u16_EventPosType;                  /*  for Event position in ALL(PrimaryMemory/UserDefineMemory) configured event. */
                                                            /*  PrimaryMemory    : Dem_u16_EventPosType == Dem_u16_EventCtrlIndexType.                                              */
                                                            /*  UserDefineMemory : Dem_u16_EventPosType == Dem_u16_EventCtrlIndexType & 0x8000 + Dem_PrimaryMemEventConfigureNum.*/
                                                            /*  Max value        : Dem_PrimaryMemEventConfigureNum + ALL UserDefinedMemory event configure number.              */
#define DEM_EVENTPOS_INVALID                    ((Dem_u16_EventPosType)0xFFFFU)
#define DEM_EVENTPOS_MIN                        ((Dem_u16_EventPosType)0x0000U)


typedef uint16       Dem_u16_DTCAttrIndexType;              /*  for DTCAttributeClass table index       */
typedef uint16       Dem_u16_FFClassIndexType;              /*  for FreezeFrameClass table index        */
#define DEM_FFCLASSINDEX_INVALID                ((Dem_u16_FFClassIndexType)0xFFFFU)

typedef uint16       Dem_u16_DIDClassPerFFIndexType;        /*  for DIDClass per freezeframe index      */
typedef uint32       Dem_u32_DIDClassIndexType;             /*  for DIDClass table index                */
#define DEM_DIDCLASSINDEX_INVALID               ((Dem_u32_DIDClassIndexType)0xFFFFFFFFU)

#define DEM_OUTPUT_DIDNUMVAL_MAX                ((Dem_u16_DIDClassPerFFIndexType)0x00FFU)
#define DEM_OUTPUT_DIDNUMVAL_OVRFLW             ((uint8)0x00U)

typedef uint8        Dem_u08_DtElNumPerDIDIndexType;        /*  for DataElement per DID index           */
typedef uint16       Dem_u16_DataElementClassIndexType;     /*  for DataElementClass index              */
#define DEM_DATAELEMENTCLASSINDEX_INVALID       ((Dem_u16_DataElementClassIndexType)0xFFFFU)

typedef uint16       Dem_u16_FFRecNumClassIndexType;        /*  for FreezeFrameRecNumClass table index  */
#define DEM_FFRECNUMCLASSINDEX_INVALID          ((Dem_u16_FFRecNumClassIndexType)0xFFFFU)

typedef uint8        Dem_u08_FFListIndexType;               /*  for FF List index                       */
typedef sint16       Dem_s16_FFListIndexType;               /*  for FF List index                       */

typedef uint8        Dem_u08_FFRecordClassIndexType;        /*  for FFRecordClass index                 */

typedef Dem_MaxNumOfEventEntryType        Dem_u08_FaultIndexType;                /*  for Fault index                         *//* [uint16->uint8]    */
#define DEM_FAULTINDEX_INVALID                  ((Dem_u08_FaultIndexType)0xFFU)
#define DEM_FAULTINDEX_INITIAL                           (DEM_FAULTINDEX_INVALID)

typedef uint8        Dem_u08_OrderIndexType;                /*  for OccurrenceOrder index               */
typedef uint16       Dem_u16_OrderSortIndexType;            /*  for OccurrenceOrder index. Index for heapsort shift operation. */
#define DEM_ORDERINDEX_INVALID                  ((Dem_u08_OrderIndexType)0xFFU)

typedef sint16       Dem_s16_OrderIndexType;                /*  for OccurrenceOrder index               */
typedef uint8        Dem_u08_FFDIndexType;                  /*  for FFD index : RecordNumberIndex       *//* [uint16->uint8]    */
#define DEM_FFDINDEX_INVALID                    ((Dem_u08_FFDIndexType)0xFFU)
#define DEM_FFRECINDEX_INITIAL                           (DEM_FFDINDEX_INVALID)

typedef uint16       Dem_u16_AllFFDIndexType;               /*  for  AllFFD index                       */

typedef uint16       Dem_u16_FFDStoredIndexType;            /*  for FFD stored index                    */
typedef uint32       Dem_u32_FFDStoredIndexType;            /*  for FFD stored index(for calculate FFD size)     */
#define DEM_FFDSTOREDINDEX_INVALID              ((Dem_u16_FFDStoredIndexType)0xFFFFU)
#define DEM_FFDSTOREDINDEX_SIZEMAX              ((Dem_u32_FFDStoredIndexType)0x0000FFFFU)

typedef uint16       Dem_u16_FFRecNumStoredIndexType;       /*  for FFRecNum stored index               */
typedef sint32       Dem_s32_FFRecNumStoredIndexType;       /*  for FFRecNum stored index. Signed index for heapsort. */
typedef uint32       Dem_u32_FFRecNumStoredSortIndexType;   /*  for FFRecNum stored index. Index for heapsort shift operation. */
typedef uint16       Dem_u16_PaddingIndexType;              /*  for PaddingArea index                   */

typedef uint32       Dem_u32_FFDOutputTotalSizeType;        /*  for FFD output total size.              */


typedef uint8        Dem_u08_OpCycleIndexType;              /*  for OpCycle index (CycleQualified id + RestartOperationCycle id)    */
typedef uint8        Dem_u08_OpCycleTableIndexType;         /*  for OpCycle table index                 */
typedef uint8        Dem_u08_CycleQualifiedIndexType;       /*  for CycleQualified index                */
typedef uint8        Dem_u08_PFCIndexType;                  /*  for PFC index                           */
#define DEM_PFCINDEX_INVALID                    ((Dem_u08_PFCIndexType)0xFFU)

typedef uint16       Dem_u16_EventQueueIndexType;           /*  for EventQueue index                    */

typedef uint16       Dem_u16_FilDTCSearchNumType;           /*  for FilteredDTC buffer index            */
typedef uint16       Dem_u16_FilFFDSearchNumType;           /*  for FilteredFFD buffer index            */
typedef uint16       Dem_u16_FilReadinessGroupSearchNumType;  /*  for FilteredDTCForReadiness index     */
typedef uint16       Dem_u16_RecordIndexType;               /*  for Record index                        *//* [uint32->uint16]   */
#define DEM_RECORDINDEX_INVALID                 ((Dem_u16_RecordIndexType)0xFFFFU)

typedef uint16       Dem_u16_NvBlockIndexType;              /*  for Nv Block index                      */

typedef uint8        Dem_u08_EventEntryOverwriteIndexType;  /*  for select nonOBD overwrite index       */


/*  for AsyncRequestQueue control       */
typedef uint8        Dem_u08_AsyncReqTableIndexType;        /*  for AsyncRequest table index            */
#define DEM_ASYNCREQ_EMPTY                      ((Dem_u08_AsyncDataQueTableIndexType)0xFFU)


typedef uint8        Dem_u08_AsyncDataQueTableIndexType;    /*  for AsyncDataQueue table index          */
#define DEM_ASYNCDATAQUETABLEINDEX_INVALID      ((Dem_u08_AsyncDataQueTableIndexType)0xFFU)



/* for TSFFD         */
typedef uint8        Dem_u08_TSFFListPerDTCIndexType;       /*  for TSFF List per DTC index             */
typedef uint16       Dem_u16_TSFFDIndexType;                /*  for TSFFD index                         *//* [uint32->uint16]   */
#define DEM_TSFFDINDEX_INVALID                  ((Dem_u16_TSFFDIndexType)0xFFFFU)

typedef uint16       Dem_u16_TSFFListIndexType;             /*  for TSFF List index                     *//* [uint32->uint16]   */
#define DEM_TSFFLISTINDEX_INVALID               ((Dem_u16_TSFFListIndexType)0xFFFFU)

typedef uint16       Dem_u16_TSFFRecClassIndexType;         /*  for TSFF RecordClass index              */
typedef uint16       Dem_u16_SmpTSFFRecClassIndexType;      /*  for TSFF(sampling) RecordClass index    */
typedef uint8        Dem_u08_TSFFClassIndexType;            /*  for TSFF class index                    */
typedef uint16       Dem_u16_SmpTSFFCPerTSFFIndexType;      /*  for TSFF(sampling) RecordClass per TSFF class index     */
typedef uint16       Dem_u16_SmpTSFFDIndexType;             /*  for TSFFD(sampling) index               *//* [uint32->uint16]   */
typedef uint16       Dem_u16_SmpRecMemIndexType;            /*  for SamplingFreezeFrame Record Memory index  */

typedef uint8        Dem_u08_NumOfTSFFType;                 /*  Number of TSFF                          */
#define DEM_NUMOFTSFF_INVALID                   ((Dem_u08_NumOfTSFFType)0xFFU)

typedef uint16       Dem_u16_RecordKindIndexType;           /*  for Record kind index                   */
typedef uint16       Dem_u16_RecordFieldIndexType;          /*  for Record field index                  */
typedef uint16       Dem_u16_MMBlockRecKindIndexType;       /*  for Record kind index(at MM)           */
#define DEM_MMBLKRECKINDINDEX_INVALID           ((Dem_u16_MMBlockRecKindIndexType)0xFFU)

typedef uint8   Dem_u08_UpdNvMType;
#define DEM_UPDNVM_UPD_RAMONLY                    ((Dem_u08_UpdNvMType)0x00U) /*  update RAM only(no update NvM). */
#define DEM_UPDNVM_UPD_NVM_RAMDIFF                ((Dem_u08_UpdNvMType)0x11U) /*  update NvM if RAM difference.   */
#define DEM_UPDNVM_UPD_NVM_FORCE                  ((Dem_u08_UpdNvMType)0x22U) /*  update NvM force.               */


/* DTR               */
typedef uint16       Dem_u16_DtrRefObdEventCtrlIndexType;       /*  for DTR Ref OBD Event Index             */
#define DEM_DTRREFOBDEVENTINDEX_INVALID         ((Dem_u16_DtrRefObdEventCtrlIndexType)0xFFFFU)

typedef uint16       Dem_u16_DtrOutputEdrTableIndexType;        /*  for Dem_DtrOutputEdrTable Index         */
#define DEM_DTROUTPUTEDRTABLEINDEX_INVALID      ((Dem_u16_DtrOutputEdrTableIndexType)0xFFFFU)

typedef Dem_DTRIdType       Dem_u16_DTRIndexType;           /*  for DTR table index                     */
typedef uint8        Dem_u08_DTRMidIndexType;               /*  for DTR MID table index                 */
typedef uint8        Dem_u08_DTRSupportObdMidIndexType;     /*  for DTR Support OBDMID table index      */
typedef uint8        Dem_u08_DTRTidIndexType;               /*  for DTR TID index                       */

typedef uint8        Dem_u08_DTRObdMidType;                 /*  for DTR OBD MID  type                   */
typedef uint32       Dem_u32_DTRObdMidBmpType;              /*  DTR OBDMID bitmap type                  */
typedef uint8        Dem_u08_DTRObdMidBmpBitCountType;      /*  Dem_u32_DTRObdMidBmpType bit count.     */

#define DEM_DTRINDEX_INVALID            ((Dem_u16_DTRIndexType)0xFFFFU)
#define DEM_DTRMIDINDEX_INVALID         ((Dem_u08_DTRMidIndexType)0xFFU)
#define DEM_DTRTIDINDEX_INVALID         ((Dem_u08_DTRTidIndexType)0xFFU)

/* IUMPR             */
typedef uint16       Dem_u16_IUMPRIndexType;                /*  for IUMPR table index                   */
typedef uint16       Dem_u16_RatioIndexType;                /*  for Ratio table index                   */
typedef uint16       Dem_u16_RatioIdListAdrIndexType;       /*  for RatioID List address table index    */
#define DEM_RATIOIDLISTADRINDEX_INVALID          ((Dem_u16_RatioIdListAdrIndexType)0xFFFFU)
typedef uint8        Dem_u08_IUMPRGroupIndexType;           /*  for IUMPR Group table index             */

typedef uint8        Dem_u08_IUMPRGenDenCondType;           /*  IUMPR GeneralDenominator Condition type     */
typedef uint8        Dem_u08_IUMPRGenAddedCondType;         /*  IUMPR GeneralDenominator Add Condition type */
typedef uint8        Dem_u08_IUMPRRatioCondType;            /*  IUMPR RatioCondition type                   */

typedef uint8        Dem_u08_IUMPRNODIValueType;            /*  IUMPR Number Of Data Items Value type       */
typedef uint8        Dem_u08_IUMPRNODIOutputSizeType;       /*  IUMPR Number Of Data Items OutputSize type  */

/* Readiness         */
typedef uint8        Dem_u08_ReadinessGroupIndexType;           /*  for Readiness Group table index         */
#define DEM_READINESSGROUPINDEX_INVALID          ((Dem_u08_ReadinessGroupIndexType)0xFFU)
typedef uint8        Dem_u08_ReadinessDataPositionIndexType;    /*  for Readiness Data Position index       */
#define DEM_READINESSDATAPOSITIONINDEX_INVALID   ((Dem_u08_ReadinessDataPositionIndexType)0xFFU)

typedef uint8        Dem_u08_ReadinessGroupIdType;              /*  for Readiness Group Id                  */

/* for PreFFD         */
typedef uint8        Dem_u08_PreFFDIndexType;               /*  for PreFFD index                        */

/* Similar           */
typedef uint8        Dem_u08_SimilarConditionIndexType;     /*  for Similar Condition index             */

/* Misfire           */
typedef uint8        Dem_u08_MisfireObdFFDCylIndexType;     /* for Misfire OBD FFD Cylnder Index        */
#define DEM_MISFIRE_OBD_FFDCYL_INDEX_INVALID    ((Dem_u08_MisfireObdFFDCylIndexType)0xFFU)
typedef uint8        Dem_u08_MisfireFFDCylIndexType;        /* for Misfire FFD Cylnder Index            */
#define DEM_MISFIRE_FFDCYL_INDEX_INVALID        ((Dem_u08_MisfireFFDCylIndexType)0xFFU)


/* EDR */
typedef uint16       Dem_u16_ExDataClassIndexType;          /*  for ExDataClass table index             */
#define DEM_EXDATACLASSINDEX_INVALID             ((Dem_u16_ExDataClassIndexType)0xFFFFU)

typedef uint8        Dem_u08_EDRClassIndexType;             /*  for EDRClass table index                */
#define DEM_EDRCLASSINDEX_INVALID                ((Dem_u08_EDRClassIndexType)0xFFU)
typedef uint8        Dem_u08_EDRClassRefIndexType;          /*  for EDRClass reference table index      */
#define DEM_EDRCLASSREFINDEX_INVALID             ((Dem_u08_EDRClassRefIndexType)0xFFU)      /*  used in Configurator        */

typedef uint8        Dem_u08_EDRSupDTCBmpIndexType;         /* Dem_EDRNumberSupportBitmapTable.SupportBitmapTable Index */
typedef uint8        Dem_u08_EDRNumberSupBmpIndexType;      /* Dem_EDRNumberSupportBitmapTable Index */
typedef sint16       Dem_s16_EDRNumberSupBmpIndexType;      /* Dem_EDRNumberSupportBitmapTable Index( for search ) */
#define DEM_EDRNUMBERSUPBMPINDEX_INVALID         ((Dem_u08_EDRNumberSupBmpIndexType)0xFFU)

typedef uint16       Dem_u16_AltIUMPRIndexType;             /*  for AltIUMPR table index                */
#define DEM_ALTIUMPRINDEX_INVALID                ((Dem_u16_AltIUMPRIndexType)0xFFFFU)

typedef uint8        Dem_u08_AltIUMPRTestCompletedThisCycleType;             /*  for AltIUMPR : TestCompleteStatus type.        */
#define DEM_ALTIUMPR_TCTOC_TESTCOMPLETE          ((Dem_u08_AltIUMPRTestCompletedThisCycleType)0x00U)
#define DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE       ((Dem_u08_AltIUMPRTestCompletedThisCycleType)0xFFU)

/*-------------------*/
/* number type       */
/*-------------------*/
typedef uint32       Dem_u32_TotalRecordNumType;            /*  for Record Num All Record               */
typedef uint16       Dem_u16_NvBlockPerRecordNumType;       /*  for Block Num Of Per Record             */

typedef uint8        Dem_u08_MaxNumberOfDTCToStoreFreezeFrameType;  /* Max number of DTC to store FFR */
typedef uint8        Dem_u08_MaxNumberOfFreezeFrameTriggerType;     /* Max number of FFRs that can be stored for each trigger */


/*-------------------*/
/* size type         */
/*-------------------*/
typedef uint16       Dem_u16_BlockSizeType;                 /*  for BlockSize                           */

/*-------------------*/
/* data type         */
/*-------------------*/
typedef uint16       Dem_u16_OccrOrderType;                 /*  for Counter of OccurrenceOrder          */
#define DEM_FAIL_OCCURRENCE_NUM_INITIAL                  ((Dem_u16_OccrOrderType)0x0001U)
#define DEM_FAIL_OCCURRENCE_NUM_LIMIT                    ((Dem_u16_OccrOrderType)0xFFFEU)
#define DEM_FAIL_OCCURRENCE_NUM_INVALID                  ((Dem_u16_OccrOrderType)0xFFFFU)

typedef uint8        Dem_u08_ConsistencyIdType;             /*  for ID of Consistency                   */

#define DEM_CONSISTENCY_INITIAL                          ((Dem_u08_ConsistencyIdType)0xFFU)

typedef uint8        Dem_u08_GroupOfDTCIndexType;           /*  for DemGroupOfDTCTable                  */
typedef uint8        Dem_OperationCycleStateType;           /*  operation cycle state values            */

/*-------------------*/
/* Attribute type    */
/*-------------------*/
typedef uint16       Dem_u16_EventAttributeType;            /*  EventAttribute type                     */
typedef uint8        Dem_u08_EventPriorityType;             /*  EventPriority type                      */

/*--------------------*/
/* IndicatorInfo type */
/*--------------------*/
typedef uint8        Dem_u08_IndicatorInfoIndexType;        /*  for IndicatorInfoTable index            */

/*--------------------*/
/* UserDefinedMemory type */
/*--------------------*/
typedef uint16       Dem_u16_UdmDemMemKindIndexType;   /*  for UserDefinedMemory index            */
#define DEM_UDMTABLEINDEX_INVALID               ((Dem_u16_UdmDemMemKindIndexType)0xFFFFU)

typedef uint8        Dem_u08_UdmMemoryInfoTableIndexType;   /*  for UserDefinedMemory InfoTable index  */
#define DEM_UDMINFOTABLEINDEX_INVALID           ((Dem_u08_UdmMemoryInfoTableIndexType)0xFFU)

typedef uint8        Dem_u08_UserDefinedMemoryType;    /*  for UserDefinedMemory Type             */

#define DEM_UDMFFDINDEX_INVALID                 ((Dem_u16_UdmFFDIndexType)0xFFFFU)
#define DEM_UDMOCCURRENCEORDER_INITIAL          ((Dem_u32_UdmOccurrenceOrderType)0x00FFFFFFU)
#define DEM_UDM_OCCURRENCEORDER_MSB             ((Dem_u32_UdmOccurrenceOrderType)0x00800000U)

#define DEM_UDMFFRECINDEX_INITIAL                       (DEM_UDMFFDINDEX_INVALID)

typedef uint8        Dem_u08_UdmFaultIndexType;             /*  for UserDefinedMemory Fault index      */
#define DEM_UDMFAULTINDEX_INITIAL                       ((Dem_u08_UdmFaultIndexType)0xFFU)

typedef uint16       Dem_u16_UdmFFDIndexType;               /*  for UserDefinedMemory FFD index        */
typedef uint16       Dem_u16_UdmDTCAttrIndexType;              /*  Dem_UdmDTCAttributeTable index       */
typedef uint32       Dem_u32_UdmOccurrenceOrderType;        /*  for UserDefinedMemor occurrence order  */

/*--------------------------------------*/
/*  for AsyncRequestQueue type          */
/*--------------------------------------*/
typedef uint16       Dem_u16_AsyncReqItemAType;             /*  for EventQueue data : dataA(Index)    : Dem_u16_AsyncReqItemAType >= Dem_u16_EventCtrlIndexType          */
typedef uint8        Dem_u08_AsyncReqItemBType;             /*  for EventQueue data : dataB(Status)   : Dem_u08_AsyncReqItemBType >= Dem_EventStatusType, Dem_u08_AsyncDataQueIndexType   */

typedef uint8        Dem_u08_AsyncReqFuncAttrType;          /*  for EventQueue data : Function Attribute   */
typedef uint8        Dem_u08_AsyncExecReturnType;           /*  Async Execute Return type.             */

typedef uint8        Dem_u08_AsyncDataQueIndexType;         /*  for AsyncDataQueue index                */
typedef uint8        Dem_u08_AsyncDataQueItemSizeType;      /*  for AsyncDataQueue Item size            */
typedef uint16       Dem_u16_AsyncDataQueBuffIndexType;     /*  for AsyncDataQueue Buffer index : Dem_u08_AsyncDataQueIndexType * Dem_u08_AsyncDataQueItemSizeType        */

/*--------------------------------------*/
/*  Data type                           */
/*--------------------------------------*/
typedef uint8        Dem_u08_WIRStatusType;               /*  WIR Status type                     */
#define     DEM_WIRSTATUS_ON     ((Dem_u08_WIRStatusType)0x55U)
#define     DEM_WIRSTATUS_OFF    ((Dem_u08_WIRStatusType)0xAAU)

typedef uint8        Dem_u08_DTCStatusExType;               /*  extend statusOfDTC                  */
typedef uint8        Dem_u08_DTCStatusEx2Type;              /*  extend statusOfDTC                  */
typedef uint8        Dem_u08_FFValidTriggerType;            /*  FreezeFrame Trigger type            */

typedef uint8        Dem_u08_PFCCycQuaInfoType;             /*  PFC Cycle Qualified Info type       */

typedef uint8        Dem_u08_RequestCallerType;            /*  Request Caller type                */
typedef uint8        Dem_u08_ClearDTCBehaviorType;          /*  ClearDTC Behavior type              */

typedef Dem_FailureCycleCounterThresholdType        Dem_u08_FailureCounterType;            /*  Failure counter type                */
typedef uint8        Dem_u08_EventOccurrenceCounterType;    /*  EventOccurrence counter type        */
typedef uint8        Dem_u08_AgingCounterType;              /*  Aging counter type                  */
typedef uint8        Dem_u08_HealingCounterType;            /*  Healing counter type                */
typedef uint16       Dem_u16_WWHOBDTimeAgingCounterType;    /*  Time aging counter type             */

typedef uint8   Dem_u08_FaultRecoveryIndexType;             /*  FaultRecord recovery mode.          */
#define     DEM_RECOVERYTYPE_PENDINGOFF                         ((Dem_u08_FaultRecoveryIndexType)0U)
#define     DEM_RECOVERYTYPE_AGING                              ((Dem_u08_FaultRecoveryIndexType)1U)
#define     DEM_RECOVERYTYPE_NORMALIZE                          ((Dem_u08_FaultRecoveryIndexType)2U)
#define     DEM_RECOVERYTYPE_MAX                                ((Dem_u08_FaultRecoveryIndexType)3U)

typedef uint8        Dem_u08_OpCycleKindType;               /*  OperationCycle kind type  */
typedef uint8        Dem_u08_OpCycleKindIndexType;          /*  OperationCycle kind index type  */
typedef uint8        Dem_u08_FreezeFrameDataType;           /*  FreezeFrame data type             */
#define DEM_FFD_TYPE_NONOBDFFD                          ((Dem_u08_FreezeFrameDataType)0x00U)    /*  nonOBD trigger freezeframe  */
#define DEM_FFD_TYPE_TSFFD                              ((Dem_u08_FreezeFrameDataType)0x01U)    /*  timeseries freezeframe      */
#define DEM_FFD_TYPE_OBDFFD                             ((Dem_u08_FreezeFrameDataType)0x02U)    /*  OBD trigger freezeframe     */
#define DEM_FFD_TYPE_INVALID                            ((Dem_u08_FreezeFrameDataType)0xFFU)

typedef uint8       Dem_u08_FFDGetInfoType;                 /*  get freezeframe info type       */
#define DEM_FFDGETTYPE_SIZE                             ((Dem_u08_FFDGetInfoType)0x00U)         /*  get size.       */
#define DEM_FFDGETTYPE_DATA                             ((Dem_u08_FFDGetInfoType)0xFFU)         /*  get data.       */

/*--------------------------------------*/
/*  FreezeFrame data type               */
/*--------------------------------------*/
typedef uint8        Dem_u08_FFStoredStatusType;            /*  FreezeFrame data stored status type             */
#define DEM_FFD_NOT_STORED                               ((Dem_u08_FFStoredStatusType)0x00U)
#define DEM_FFD_STORED                                   ((Dem_u08_FFStoredStatusType)0x11U)

typedef uint16       Dem_u16_FFCheckSumType;                /*  FreezeFrame data CheckSum type             */
typedef uint32       Dem_u32_FFCheckSumAddCarryType;        /*  FreezeFrame data CheckSum type             */

/*--------------------------------------*/
/*  ID type                             */
/*--------------------------------------*/
typedef uint8        Dem_u08_OperationCycleIdType;          /*  OperationCycle Id                   */
typedef uint8        Dem_u08_IndicatorIdType;               /*  Indicator Id                        */

/*--------------------------------------*/
/*  Control Status type                 */
/*--------------------------------------*/
typedef uint8        Dem_u08_InitStatusType;                /*  Initialize status                  */
typedef uint8        Dem_u08_DTCSettingStatusType;          /*  DTCSetting status                  */

typedef uint8        Dem_u08_DTCRecordUpdateStatusType;     /* DTC record update state */
#define DEM_CTL_STS_DTC_UPDATE_ENABLE                ((Dem_u08_DTCRecordUpdateStatusType)0x00U)
#define DEM_CTL_STS_DTC_UPDATE_DISABLE               ((Dem_u08_DTCRecordUpdateStatusType)0x11U)

typedef uint8        Dem_u08_DTCStoredDataStatusType;       /* DTC stored data state */
#define DEM_CTL_STS_DTC_STORED_DATA_END              ((Dem_u08_DTCStoredDataStatusType)0x00U)
#define DEM_CTL_STS_DTC_STORED_DATA_START            ((Dem_u08_DTCStoredDataStatusType)0x11U)

typedef uint8        Dem_u08_OpCycleProcType;               /*  OperationCycle update process type  */

typedef uint8        Dem_u08_PFCRecordUpdateStatusType;     /*  PFC record update status type       */
#define DEM_PFC_RECORD_UPDATE_DISABLE   ((Dem_u08_PFCRecordUpdateStatusType)0x00U)
#define DEM_PFC_RECORD_UPDATE_ENABLE    ((Dem_u08_PFCRecordUpdateStatusType)0x11U)

typedef uint8        Dem_u08_ClearPFCCycleType;             /*  clear PFC start cycle type          */

typedef uint8        Dem_u08_PFCClearCondCheckStatusType;    /*  PFC clear condition check status type      */
#define DEM_PFC_CLEARCONDCHKSTATUS_DISABLE   ((Dem_u08_PFCClearCondCheckStatusType)0x5AU)
#define DEM_PFC_CLEARCONDCHKSTATUS_ENABLE    ((Dem_u08_PFCClearCondCheckStatusType)0xA5U)

typedef uint8        Dem_u08_EventMemoryUpdateStatusType;     /* Event Memory update status type */
#define DEM_EVENT_MEMORY_NOT_UPDATING    ((Dem_u08_EventMemoryUpdateStatusType)0x5AU)
#define DEM_EVENT_MEMORY_UPDATING        ((Dem_u08_EventMemoryUpdateStatusType)0xA5U)


/*--------------------------------------*/
/*  Control Data type                   */
/*--------------------------------------*/
typedef uint16       Dem_u16_EventNumType;                  /*  Event(DTC) Number type  */
typedef uint8        Dem_u08_UserDTCNumType;                /*  UserDTC Number type     */


typedef uint8        Dem_u08_PIDByteValueType;              /*  PID Byte value type  */
typedef uint16       Dem_u16_PIDCalcValueType;              /*  PID Calc value type  */
typedef uint32       Dem_u32_PIDCalcValueType;              /*  PID Calc value type  */


typedef uint8        Dem_u08_EventQualificationType;             /*  EventQualification type  */

#define DEM_EVENT_QUALIFICATION_NOTQUALIFIED                    ((Dem_u08_EventQualificationType)0x00U) /* Not Qualified */
#define DEM_EVENT_QUALIFICATION_PASSED                          ((Dem_u08_EventQualificationType)0x01U) /* Passed */
#define DEM_EVENT_QUALIFICATION_FAILED                          ((Dem_u08_EventQualificationType)0x02U) /* Failed */

typedef uint8        Dem_u08_MonStsKindType;                /*  MonitorStatus Kind type     */

typedef uint8        Dem_u08_MonStsReCalcType;              /*  MonitorStatus ReCalc type   */
#define DEM_MONSTS_RECALC_TYPE_INIT             ((Dem_u08_MonStsReCalcType)0x00)
#define DEM_MONSTS_RECALC_TYPE_OPERATIONCYCLE   ((Dem_u08_MonStsReCalcType)0x01)
#define DEM_MONSTS_RECALC_TYPE_DTC_CLEAR        ((Dem_u08_MonStsReCalcType)0x02)

/*--------------------------------------*/
/*  Cycle counter type                  */
/*--------------------------------------*/
typedef uint8        Dem_u08_ControlProcCycleCounterType;       /*  ControlProcess Cycle counter type  */
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
typedef uint32       Dem_u32_NvMProcIdleCycleCounterType;       /*  MM Process Idle Cycle counter type  */
typedef uint8        Dem_u08_NvMProcCycleCounterType;           /*  MM Process Cycle counter type       */
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )            */
typedef uint16       Dem_u16_TSFFDSamplingCycleCounterType;     /*  TSFFD Sampling Cycle counter type  */
typedef uint16       Dem_u16_IUMPRCycleCounterType;             /*  IUMPR Cycle counter type  */
typedef uint32       Dem_u32_IUMPRCycleCounterType;             /*  IUMPR Cycle counter type(forCalc)  */
typedef uint16       Dem_u16_PIDCalcCycleCounterType;           /*  PID Cycle counter type  */
typedef uint32       Dem_u32_B1CounterCalcCycleCounterType;     /*  B1Counter Cycle counter type(forCalc)  */

/*--------------------------------------*/
/*  Record Data type                    */
/*--------------------------------------*/
typedef uint8        Dem_u08_ClearIdType;                   /*  Clear ID type                       */
typedef uint8        Dem_u08_RecMngMtxStsType;              /*  RecMngCmn Matrix Status type        */

typedef uint16       Dem_u16_RecordDataSizeType;            /*  RecordDataSize type                 */

/*--------------------------------------*/
/*  MM Data type                        */
/*--------------------------------------*/
typedef uint32      Dem_u32_MMTimeOutCountType;     /*  ReadAll Timeout count type      */
typedef uint8       Dem_u08_MMRetryCountType;       /*  Function call Retry Count type  */

/*--------------------------------------*/
/*  Specific Data type                  */
/*--------------------------------------*/
typedef uint8       Dem_u08_ExceedanceCounterType;                  /*  ExceedanceCounter  */

/*--------------------------------------*/
/*  Similar Data type                   */
/*--------------------------------------*/
typedef uint8       Dem_u08_SimilarPendingClearCounterType;       /*  SimilarPendingClearCounter  */
typedef uint8       Dem_u08_SimilarExceedanceCounterType;         /*  DemExceedanceUsed           */

/*--------------------------------------*/
/*  Misfire Data type                   */
/*--------------------------------------*/
typedef uint8        Dem_u08_MisfireKindType;                   /*  MisfireKind type                */
typedef uint8        Dem_u08_MisfireIndStatusType;              /*  MisfireIndicator status type  */
#define DEM_MISFIRE_IND_OFF                                 ((Dem_u08_MisfireIndStatusType)0x00U)
#define DEM_MISFIRE_IND_CONTINUOUS                          ((Dem_u08_MisfireIndStatusType)0x01U)
#define DEM_MISFIRE_IND_BLINKING                            ((Dem_u08_MisfireIndStatusType)0x02U)

typedef uint8        Dem_u08_MisfJudgeFFCylinderType;           /*  MisfireJudgeFreezeFrameCylinder type    */
typedef uint8        Dem_u08_MisfireFilteredEDRType;            /*  Misfire Filtered EDR type               */

typedef uint8        Dem_u08_MisfSimCondStoredTimingType;       /*  MisfireSimilarConditionStoredTiming type      */
typedef uint8        Dem_u08_MisfExceedanceCounterType;         /*  Misfire ExceedanceCounter type                */

typedef uint8       Dem_u08_MisfireKindBitType;
#define DEM_MISFIRE_KINDBIT_EMISSION  ((Dem_u08_MisfireKindBitType)0x01U)   /*  bitpos of emission : Dem_u16_MisfireStrgIndexType   */
#define DEM_MISFIRE_KINDBIT_CAT       ((Dem_u08_MisfireKindBitType)0x02U)   /*  bitpos of cat      : Dem_u16_MisfireStrgIndexType   */
#define DEM_MISFIRE_KINDBIT_BOTH      ( DEM_MISFIRE_KINDBIT_EMISSION | DEM_MISFIRE_KINDBIT_CAT )
#define DEM_MISFIRE_KINDBIT_NONE      ((Dem_u08_MisfireKindBitType)0x00U)

#define DEM_MISFIRE_KINDBIT_FIRST     ( DEM_MISFIRE_KINDBIT_EMISSION )      /*  bitstart        */

/*--------------------------------------*/
/*  Config Data type                    */
/*--------------------------------------*/
typedef uint8        Dem_u08_EventDisplacementStrategyType;     /*  EventDisplacementStrategy type.      */
typedef uint8        Dem_u08_DataElementKindType;               /*  DataElement Kind type.      */

typedef uint16       Dem_u16_AdjustCntByEventNumType;       /*  Adjust Count by Event count.      */
typedef uint8        Dem_u08_UpdateRecordType;              /*  FreezeFrame update type.        */
typedef uint8        Dem_u08_StorageTriggerType;            /*  FreezeFrame Capture trigger type.   */

typedef uint8        Dem_u08_UpdateTimingOfPID30Type;       /*  UpdateTimingof PID30 type       */

typedef uint8        Dem_u08_IUMPRDenGroupType;             /*  IUMPR DenGroup type     */
typedef uint8        Dem_u08_IUMPRRatioKindType;            /*  IUMPR RatioKind type        */

typedef uint8        Dem_u08_OBDEngineType;                 /*  Engine type     */
typedef uint8        Dem_u08_OBDCompressionType;            /*  Compression type     */

/*--------------------------------------*/
/*  Memory type                         */
/*--------------------------------------*/
typedef uint8        Dem_u08_MemoryKindType;               /*  Memory Kind type.      */
#define DEM_MEMKIND_PRIMARY         ((Dem_u08_MemoryKindType)0x00U)
#define DEM_MEMKIND_USERDEFMEM      ((Dem_u08_MemoryKindType)0x10U)

/*--------------------------------------*/
/*  EventList create mode               */
/*--------------------------------------*/
typedef uint8   Dem_u08_EventListModeType;
#define DEM_EVTLSTMODE_PDTC         ((Dem_u08_EventListModeType)0x00)
#define DEM_EVTLSTMODE_ACTIVEFAULT  ((Dem_u08_EventListModeType)0x01)

/*--------------------------------------*/
/* OperationCycle update type           */
/*--------------------------------------*/
typedef uint8       Dem_u08_OpcycUpdateFailureCycleType;            /*  operation cycle update type.    */
#define DEM_OPCYCUPD_FLCYC_UPDATE_FCCYC                         ((Dem_u08_OpcycUpdateFailureCycleType)0x80U)    /*  this cycle is update target cycle.      */
#define DEM_OPCYCUPD_FLCYC_UPDSTATUS_TF                         ((Dem_u08_OpcycUpdateFailureCycleType)0x01U)    /*  update target : bit0 of statusOfDTC.    */
#define DEM_OPCYCUPD_FLCYC_UPDSTATUS_TFTOC                      ((Dem_u08_OpcycUpdateFailureCycleType)0x02U)    /*  update target : bit1 of statusOfDTC.    */
#define DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC                     ((Dem_u08_OpcycUpdateFailureCycleType)0x04U)    /*  update target : bit6 of statusOfDTC.    */

#define DEM_OPCYCUPD_FLCYC_UPDATE_ALL                           ( DEM_OPCYCUPD_FLCYC_UPDATE_FCCYC | DEM_OPCYCUPD_FLCYC_UPDSTATUS_TF | DEM_OPCYCUPD_FLCYC_UPDSTATUS_TFTOC | DEM_OPCYCUPD_FLCYC_UPDSTATUS_TNCTOC )    /*  set all value.      */
#define DEM_OPCYCUPD_FLCYC_INITIALVALUE                         ((Dem_u08_OpcycUpdateFailureCycleType)0x00U)    /*  initial value.      */

typedef uint8       Dem_u08_OpcycUpdateHealingAgingCycleType;       /*  operation cycle update type.    */
#define DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC                    ((Dem_u08_OpcycUpdateHealingAgingCycleType)0x80U)   /*  this cycle is update target healing cycle.  */
#define DEM_OPCYCUPD_HACYC_UPDATE_AGINGCYC                      ((Dem_u08_OpcycUpdateHealingAgingCycleType)0x40U)   /*  this cycle is update target aging cycle.    */
#define DEM_OPCYCUPD_HACYC_EXEC_AGING                           ((Dem_u08_OpcycUpdateHealingAgingCycleType)0x20U)   /*  execute aging available.                    */
#define DEM_OPCYCUPD_HACYC_UPDATE_TIME_AGINGCYC                 ((Dem_u08_OpcycUpdateHealingAgingCycleType)0x10U)   /*  this cycle is update target time-aging cycle.    */
#define DEM_OPCYCUPD_HACYC_EXEC_WWHOBD_AGING                    ((Dem_u08_OpcycUpdateHealingAgingCycleType)0x08U)   /*  execute aging available for WWH-OBD.        */

#define DEM_OPCYCUPD_HACYC_UPDATE_ALL                           ( DEM_OPCYCUPD_HACYC_UPDATE_HEALINGCYC | DEM_OPCYCUPD_HACYC_UPDATE_AGINGCYC | DEM_OPCYCUPD_HACYC_EXEC_AGING )                   /*  set all value.      */
#define DEM_OPCYCUPD_HACYC_INITIALVALUE                         ((Dem_u08_OpcycUpdateHealingAgingCycleType)0x00U)   /*  initial value.      */


/*--------------------------------------*/
/* Internal function mode               */
/*--------------------------------------*/
typedef uint8       Dem_u08_GetExtendDataModeType;
#define DEM_EDR_GETEDRMODE_EVENT        ((Dem_u08_GetExtendDataModeType)0x00U)
#define DEM_EDR_GETEDRMODE_DTC          ((Dem_u08_GetExtendDataModeType)0x01U)


typedef uint8   Dem_u08_ClearCompleteType;
#define     DEM_CLEARCOMPLETE_OK                ((Dem_u08_ClearCompleteType)0x00U)
#define     DEM_CLEARCOMPLETE_NVMERROR          ((Dem_u08_ClearCompleteType)0x11U)
#define     DEM_CLEARCOMPLETE_SWCERROR          ((Dem_u08_ClearCompleteType)0x22U)

typedef uint8   Dem_u08_MonStsAsyncUpdModeType;
#define     DEM_MONSTS_ASYNCUPD_NORMAL          ((Dem_u08_MonStsAsyncUpdModeType)0x00U)
#define     DEM_MONSTS_ASYNCUPD_OVERFLOW        ((Dem_u08_MonStsAsyncUpdModeType)0x11U)
#define     DEM_MONSTS_ASYNCUPD_AGING           ((Dem_u08_MonStsAsyncUpdModeType)0x22U)


/*--------------------------------------*/
/* WWH-OBD                              */
/*--------------------------------------*/
typedef uint32   Dem_u32_B1CounterType;
typedef uint16   Dem_u16_B1CounterOutputType;
typedef uint16   Dem_u16_IndMIIndexType;
#define DEM_INDMIINDEX_INVALID          ((Dem_u16_IndMIIndexType)0xFFFFU)
typedef uint8    Dem_u08_B1ClearCycleCounterType;

typedef uint16   Dem_u16_DTCGrpTableIndexType;

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
/*------------------------------------------*/
/* Priority for CombinedEventOnRetrieval    */
/*------------------------------------------*/
typedef uint8   Dem_u08_EventClassPriorityType;     /*  Priority for EventClass type    */
#define DEM_EVENTCLASS_PRIORITY_CLASS_NONE      ((Dem_u08_EventClassPriorityType)0xFFU)
#define DEM_EVENTCLASS_PRIORITY_CLASS_A         ((Dem_u08_EventClassPriorityType)0x01U)
#define DEM_EVENTCLASS_PRIORITY_CLASS_B1        ((Dem_u08_EventClassPriorityType)0x02U)
#define DEM_EVENTCLASS_PRIORITY_CLASS_B2        ((Dem_u08_EventClassPriorityType)0x03U)
#define DEM_EVENTCLASS_PRIORITY_CLASS_C         ((Dem_u08_EventClassPriorityType)0x04U)

typedef uint8   Dem_u08_EventStatusPriorityType;    /*  Priority for EventStatus type   */
#define DEM_EVENTSTATUS_PRIORITY_NO_FAULT       ((Dem_u08_EventStatusPriorityType)0xFFU)
#define DEM_EVENTSTATUS_PRIORITY_CONFIRMED      ((Dem_u08_EventStatusPriorityType)0x01U)
#define DEM_EVENTSTATUS_PRIORITY_POTENTIAL      ((Dem_u08_EventStatusPriorityType)0x02U)
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

/*----------------------------------------------*/
/*  EventStrgBitmap at CombinedEventOnStorage   */
/*----------------------------------------------*/
typedef uint8   Dem_u08_EventCtrlBitmapIndexType;       /*  EventStrg BitmapBuffer Index type   */
typedef uint8   Dem_u08_EventCtrlBitmapWidthType;       /*  EventStrg Bitmap bit width type     */
typedef uint8   Dem_u08_EventCtrlBitmapType;            /*  EventStrg Bitmap type               */
#define DEM_EVENTCTRLBITMAP_BITWIDTH        ((Dem_u08_EventCtrlBitmapWidthType)8U)    /*  bit width of [Dem_u08_EventCtrlBitmapType]. */
#define DEM_EVENTCTRLBITMAP_ALL_OFF         ((Dem_u08_EventCtrlBitmapType)0x00U)

/*-------------------*/
/* Return type       */
/*-------------------*/
typedef uint8        Dem_u08_InternalReturnType;            /*  Internal Return type                    */



/*==========================================*/
/*  Dem Internal type                       */
/*==========================================*/
/*-------------------*/
/* Struct type       */
/*-------------------*/
typedef struct {

    Dem_UdsStatusByteType              DTCStatus;
    Dem_u08_DTCStatusExType            ExtendDTCStatus;
    Dem_u08_DTCStatusEx2Type           ExtendDTCStatus2;

} Dem_DTCStatusStType;

typedef struct {
    Dem_UdsStatusByteType              DTCStatusMask;
    Dem_DTCKindType                    DTCKind;
    Dem_DTCFormatType                  DTCFormat;
    Dem_DTCOriginType                  DTCOrigin;
    boolean                            FilterWithSeverity;
    Dem_DTCSeverityType                DTCSeverityMask;
    boolean                            FilterForFaultDetectionCounter;
} Dem_SetDTCFilterType;

#if ( DEM_DTR_SUPPORT == STD_ON )
typedef struct {
    Dem_s32_DTRValueRawType         RawTestResult;
    Dem_s32_DTRValueRawType         RawLowerLimit;
    Dem_s32_DTRValueRawType         RawUpperLimit;

    Dem_u16_DTRValueStoreType       TestResult;
    Dem_u16_DTRValueStoreType       LowerLimit;
    Dem_u16_DTRValueStoreType       UpperLimit;

    Dem_u08_DTRTidIndexType         TIDValue;
    Dem_u08_DTRUasidType            UaSID;
    Dem_DTRControlType              CtrlVal;

} Dem_DtrDataType;

#endif  /* ( DEM_DTR_SUPPORT == STD_ON ) */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* DEM_COMMONTYPES_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
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

