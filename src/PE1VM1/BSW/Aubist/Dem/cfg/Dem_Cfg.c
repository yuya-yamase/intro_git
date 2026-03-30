/* Dem_Cfg_c(v5-10-0)                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Cfg/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include "../cfg/Dem_Cfg.h"
#include "../cfg/Dem_NvM_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

CONST( AB_83_ConstV Dem_u16_EventStrgIndexType           ,DEM_CONFIG_DATA )  Dem_PrimaryMemEventStorageNum             = DEM_PRIMEM_EVENTSTORAGE_NUM;

/* Dem_Main */
CONST( AB_83_ConstV Dem_u08_NvMProcCycleCounterType      ,DEM_CONFIG_DATA )  Dem_MainSyncNvmDivideCycleCount           = DEM_MAIN_SYNC_NVM_DIVIDE_CYCLE_COUNT;
CONST( AB_83_ConstV Dem_u32_NvMProcIdleCycleCounterType  ,DEM_CONFIG_DATA )  Dem_MainSyncNvmDivideIdleCycleCount       = DEM_MAIN_SYNC_NVM_DIVIDE_IDLE_CYCLE_COUNT;
CONST( AB_83_ConstV Dem_u08_ControlProcCycleCounterType  ,DEM_CONFIG_DATA )  Dem_MainControlDivideCycleCount           = DEM_MAIN_CONTROL_DIVIDE_CYCLE_COUNT;

/* Dem_EventQueue */
CONST( AB_83_ConstV Dem_u16_EventQueueIndexType        ,DEM_CONFIG_DATA )  Dem_EventQueueSize                          = DEM_EVENT_QUEUE_SIZE;

/* Dem_Control */
CONST( AB_83_ConstV Dem_u16_EventQueueIndexType        ,DEM_CONFIG_DATA )  Dem_CtlSetEventNum                          = DEM_CTL_SET_EVENT_NUM;
CONST( AB_83_ConstV Dem_u16_AdjustCntByEventNumType    ,DEM_CONFIG_DATA )  Dem_ControlClearRamEventNumByCycle          = DEM_CTL_CLEAR_RAM_EVENT_NUM_BY_CYCLE;
CONST( AB_83_ConstV Dem_u16_AdjustCntByEventNumType    ,DEM_CONFIG_DATA )  Dem_CtlNotifyControlDTCSettingAtOnce        = DEM_CTL_NOTIFY_CONTROL_DTC_SETTING_AT_ONCE;
CONST( AB_83_ConstV Dem_u16_EventPosType               ,DEM_CONFIG_DATA )  Dem_CtlInitThisOpCycleBitByCycle            = DEM_CTL_INIT_THIS_OPCYCLE_BIT_BY_CYCLE;

/* Dem_DTC */
CONST( AB_83_ConstV Dem_u16_FilDTCSearchNumType        ,DEM_CONFIG_DATA )  Dem_FilDTCSearchLoopNumByCycle              = DEM_FILDTC_SEARCH_LOOP_NUM_BY_CYCLE;

/* Dem_FFD */
CONST( AB_83_ConstV Dem_u16_FilFFDSearchNumType        ,DEM_CONFIG_DATA )  Dem_FilFFDSearchLoopNumByCycle              = DEM_FILFFD_SEARCH_LOOP_NUM_BY_CYCLE;

/* DemAdjustEDRProcess */
CONST( AB_83_ConstV Dem_u16_EventStrgIndexType         ,DEM_CONFIG_DATA )  Dem_FilEDRSearchLoopNumByCycle              = DEM_FILEDR_SEARCH_LOOP_NUM_BY_CYCLE;

/* DemAdjustVerifyProcess */
CONST( AB_83_ConstV Dem_u16_EventStrgIndexType         ,DEM_CONFIG_DATA) Dem_EventNumForVerifyByCycle                  = DEM_EVENT_NUM_FOR_VERIFY_BY_CYCLE;
CONST( AB_83_ConstV Dem_u16_UdmEventIndexType          ,DEM_CONFIG_DATA) Dem_UdmEventNumForVerifyByCycle               = DEM_UDMEVENT_NUM_FOR_VERIFY_BY_CYCLE;

CONST( AB_83_ConstV Dem_u32_TotalRecordNumType         ,DEM_CONFIG_DATA) Dem_RecordNumForVerifyByCycle                 = DEM_RECORD_NUM_FOR_VERIFY_BY_CYCLE;


/* DemConfigSet */
CONST( AB_83_ConstV Dem_u16_EventCtrlIndexType                ,DEM_CONFIG_DATA )  Dem_PrimaryMemEventConfigureNum       = DEM_PRIMEM_EVENT_NUM;

/* DemGeneral */
CONST( AB_83_ConstV boolean                                   ,DEM_CONFIG_DATA )  Dem_AgingRequiresNotFailedCycle       = DEM_AGING_REQUIRES_NOT_FAILED_CYCLE;     /* DemAgingRequiresNotFailedCycle            */
CONST( AB_83_ConstV Dem_UdsStatusByteType                     ,DEM_CONFIG_DATA )  Dem_DtcStatusAvailabilityMask         = DEM_DTCSTATUS_AVAILABILITY_MASK;         /* DemDtcStatusAvailabilityMask              */
CONST( AB_83_ConstV Dem_DTCSeverityType                       ,DEM_CONFIG_DATA )  Dem_DtcSeverityAvailabilityMask       = DEM_DTCSEVERITY_AVAILABILITY_MASK;       /* DemDtcSeverityAvailabilityMask            */
CONST( AB_83_ConstV uint8                                     ,DEM_CONFIG_DATA )  Dem_TypeOfDTCSupported                = DEM_DTC_TRANSLATION_ISO14229_1;          /* DemTypeOfDTCSupported                     */
CONST( AB_83_ConstV boolean                                   ,DEM_CONFIG_DATA )  Dem_ResetTestFailedAtOpCycRestart     = DEM_RESET_TESTFAILED_AT_OPCYC_RESTART;
CONST( AB_83_ConstV Dem_u08_ResetConfirmedBitOnOverflowType   ,DEM_CONFIG_DATA )  Dem_ResetConfirmedBitOnOverflow       = DEM_STATUS_BIT_NO_RESET;    /* DemResetConfirmedBitOnOverflow            */
CONST( AB_83_ConstV Dem_u08_DTCStatusBitHandlingType          ,DEM_CONFIG_DATA )  Dem_StatusBitHandlingTestFailedSinceLastClear = DEM_STATUS_BIT_NORMAL;               /* DemStatusBitHandlingTestFailedSinceLastClear */
CONST( AB_83_ConstV Dem_u08_FaultIndexType                    ,DEM_CONFIG_DATA )  Dem_FailRecordNum                     = DEM_FAIL_RECORD_NUM;
CONST( AB_83_ConstV Dem_UdsStatusByteType                     ,DEM_CONFIG_DATA )  Dem_DTCStatusProductSupportBit        = DEM_DTCSTATUS_PRODUCT_SUPPORT_BIT;
CONST( AB_83_ConstV Dem_u08_ClearDTCBehaviorType              ,DEM_CONFIG_DATA )  Dem_ClearDTCBehavior                  = DEM_CLEAR_DTC_BEHAVIOR;
CONST( AB_83_ConstV boolean                                   ,DEM_CONFIG_DATA )  Dem_AgingRequiresTestedCycle          = (boolean)FALSE;
CONST( AB_83_ConstV Dem_u08_EDRBehaviorAt0xFEType             ,DEM_CONFIG_DATA )  Dem_DTCExtDataRecordsBehaviorAt0xFE             =   DEM_EDRNUM_FE_ALWAYS_NOT_SUPPORT;
CONST( AB_83_ConstV Dem_u08_NotConfiguredEDRBehaviorType      ,DEM_CONFIG_DATA )  Dem_NotConfiguredDTCExtDataRecordNumberBehavior =   DEM_EDRNUM_NOT_ACCEPT;
CONST( AB_83_ConstV Dem_u08_ClearDTCByDcmDuringInitializingType ,DEM_CONFIG_DATA )  Dem_ClearDTCByDcmDuringInitializing           =   DEM_CLEARDTC_NOT_ACCEPT;
CONST( AB_83_ConstV Dem_u08_MaxNumberOfDTCToStoreFreezeFrameType    ,DEM_CONFIG_DATA )  Dem_MaxNumberOfDTCToStoreFreezeFrame          = DEM_MAX_NUM_OF_DTC_TO_STORE_FREEZE_FRAME;

/* DemGeneralOBD */

/* DemGroupOfDTC */
CONST( AB_83_ConstV Dem_u08_GroupOfDTCIndexType        ,DEM_CONFIG_DATA )  Dem_GroupDTCNum                           = DEM_GROUP_OF_DTC_NUM;
CONST( AB_83_ConstV Dem_GroupOfDTCType                 ,DEM_CONFIG_DATA )  Dem_GroupOfDTCTable[DEM_GROUP_OF_DTC_NUM] =
{
    /*  DemGroupDTCs  */
    {  DEM_DTC_GROUP_ALL_DTCS  }
};

CONST( AB_83_ConstV Dem_FreezeFrameDataPosType           ,DEM_CONFIG_DATA )  Dem_NonObdFreezeFrameDataPosTable =
{
    0U,        /* FirstCID */
    1U,        /* FirstEventStrgIndexUpper */
    2U,        /* FirstEventStrgIndexLower */
    3U,        /* RecordStatus */
    4U,        /* DataStart */
    29U,       /* LastCID */
    30U,       /* LastEventStrgIndexUpper */
    31U        /* LastEventStrgIndexLower */
};

CONST( AB_83_ConstV Dem_UdmFreezeFrameDataPosType        ,DEM_CONFIG_DATA )  Dem_UdmFreezeFrameDataPosTable[ DEM_USER_DEFINED_MEMORY_NUM ] =
{
    /*  FirstCID FirstUdmEventIndexUpper FirstUdmEventIndexLower CidUdmFreezeFrameRecords OccurrenceOrderUpper OccurrenceOrderMiddle OccurrenceOrderLower OffsetOfTSFFListIndex RecordStatus DataStart  */
        /*  LastCID LastUdmEventIndexUpper LastUdmEventIndexLower  */
    {        0U,       1U,       2U,       3U,       4U,       5U,       6U,       7U,       8U,       9U,    29U,    30U,    31U   },
    {        0U,       1U,       2U,       3U,       4U,       5U,       6U,       7U,       8U,       9U,    61U,    62U,    63U   },
    {        0U,       1U,       2U,       3U,       4U,       5U,       6U,       7U,       8U,       9U,    61U,    62U,    63U   },
    {        0U,       1U,       2U,       3U,       4U,       5U,       6U,       7U,       8U,       9U,    93U,    94U,    95U   },
    {        0U,       1U,       2U,       3U,       4U,       5U,       6U,       7U,       8U,       9U,   221U,   222U,   223U   },
    {        0U,       1U,       2U,       3U,       4U,       5U,       6U,       7U,       8U,       9U,    29U,    30U,    31U   },
    {        0U,       1U,       2U,       3U,       4U,       5U,       6U,       7U,       8U,       9U,    61U,    62U,    63U   }
};


/* OperationCycle Record */
CONST( AB_83_ConstV Dem_u08_OpCycleIndexType           ,DEM_CONFIG_DATA )  Dem_OperationCycleRecordStateNum     = DEM_OPERATION_CYCLE_RECORD_STATE_NUM;

/* ClrInfo Record */
CONST( AB_83_ConstV Dem_u16_UdmDemMemKindIndexType           ,DEM_CONFIG_DATA )  Dem_UserDefinedMemoryNum              = DEM_USER_DEFINED_MEMORY_NUM;
CONST( AB_83_ConstV Dem_u08_UdmMemoryInfoTableIndexType      ,DEM_CONFIG_DATA )  Dem_UserDefinedMemoryInfoNum          = DEM_USER_DEFINED_MEMORY_INFO_NUM;
CONST( AB_83_ConstV Dem_u08_UdmMemoryInfoTableIndexType      ,DEM_CONFIG_DATA )  Dem_UserDefinedMemoryInternalInfoNum  = DEM_USER_DEFINED_MEMORY_INTERNAL_INFO_NUM;

CONST( AB_83_ConstV Dem_u16_PaddingIndexType           ,DEM_CONFIG_DATA )  Dem_EventRecordBlockPaddingSize        = DEM_EVENT_RECORD_PADDINGSIZE_TO_BLOCKSIZE;
CONST( AB_83_ConstV Dem_u16_PaddingIndexType           ,DEM_CONFIG_DATA )  Dem_ClrInfoRecordBlockPaddingSize      = DEM_CLRINFO_RECORD_PADDINGSIZE_TO_BLOCKSIZE;
CONST( AB_83_ConstV Dem_u16_PaddingIndexType           ,DEM_CONFIG_DATA )  Dem_UdmFaultRecordBlockPaddingSize     = DEM_UDMFAULT_RECORD_PADDINGSIZE_TO_BLOCKSIZE;

CONST( AB_83_ConstV Dem_u16_BlockSizeType              ,DEM_CONFIG_DATA )  Dem_FFDRecordNvBlockSize               = DEM_FFD_RECORD_NVBLOCK_SIZE;

CONST( AB_83_ConstV Dem_u08_FFListIndexType            ,DEM_CONFIG_DATA )  Dem_NonOBDFFRClassPerDTCMaxNum         = DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM;

CONST( AB_83_ConstV Dem_u16_FFDStoredIndexType         ,DEM_CONFIG_DATA )  Dem_FreezeFrameDataStoredFormatSize    = DEM_FREEZE_FRAME_DATA_STORED_FORMAT_SIZE;


#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File *************************************************************/
