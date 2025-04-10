/* Dem_Cfg_h(v5-5-0)                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/Cfg/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CFG_H
#define DEM_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../cfg/Dem_NvM_Cfg.h"
#include "oxdocan_aubif.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_PRIMEM_EVENTSTORAGE_NUM                     ((Dem_u16_EventStrgIndexType)2U)

/* Dem_Main */
#define DEM_MAIN_SYNC_NVM_DIVIDE_CYCLE_COUNT            ((Dem_u08_NvMProcCycleCounterType)1U)        /* DemNvMSyncTaskTime */
#define DEM_MAIN_SYNC_NVM_DIVIDE_IDLE_CYCLE_COUNT       ((Dem_u32_NvMProcIdleCycleCounterType)0U)   /* DemNvMSyncIdleTaskTime */
#define DEM_MAIN_CONTROL_DIVIDE_CYCLE_COUNT             ((Dem_u08_ControlProcCycleCounterType)1U)    /* DemControlTaskTime */

/* Dem_EventQueue */
#define DEM_EVENT_QUEUE_SIZE                            ((Dem_u16_EventQueueIndexType)2U)    /* DemEventQueueSize                  */

/* DemGeneral */
#define DEM_AGING_REQUIRES_NOT_FAILED_CYCLE             ((boolean)FALSE)                      /* DemAgingRequiresNotFailedCycle     */
#define DEM_RESET_TESTFAILED_AT_OPCYC_RESTART                  ((boolean)FALSE)               /* DemStatusBitResetTestFailed */
#define DEM_NOTIFY_DEM_MODE_MASK                        ((Dem_ModeType)0xFFFFU)               /* DemNotifyDemModeMask               */
#define DEM_CLEAR_DTC_BEHAVIOR                          ((Dem_u08_ClearDTCBehaviorType)DEM_CLRRESP_NONVOLATILE_FINISH)        /* DemClearDTCBehavior */
#define DEM_MAX_NUM_OF_DTC_TO_STORE_FREEZE_FRAME             ((Dem_u08_MaxNumberOfDTCToStoreFreezeFrameType)0xFFU)        /* DemMaxNumberOfDTCToStoreFreezeFrame */

/* Dem_Control */
#define DEM_CTL_SET_EVENT_NUM                           ((Dem_u16_EventQueueIndexType)2U)    /* DemEventNumForSet                  */
/* Dem_DTC */
#define DEM_FILDTC_SEARCH_LOOP_NUM_BY_CYCLE             ((Dem_u16_FilDTCSearchNumType)65535U)     /* DemFilteredDTCSearchLoopNumByCycle */

/* Dem_Control */
#define DEM_CTL_CLEAR_RAM_EVENT_NUM_BY_CYCLE            ((Dem_u16_AdjustCntByEventNumType)3U)    /* DemEventNumForClearRAMData */
/* Dem_FFD */
#define DEM_FILFFD_SEARCH_LOOP_NUM_BY_CYCLE             ((Dem_u16_FilFFDSearchNumType)65535U)     /* DemFilteredFFDSearchLoopNumByCycle */

/* DemAdjustEDRProcess */
#define DEM_FILEDR_SEARCH_LOOP_NUM_BY_CYCLE             ((Dem_u16_EventStrgIndexType)65535U)          /* DemFilteredEDRSearchLoopNumByCycle */

/* Dem_Control */
#define DEM_CTL_NOTIFY_CONTROL_DTC_SETTING_AT_ONCE      ((Dem_u16_AdjustCntByEventNumType)3U)    /* DemEventNumForNotification */
#define DEM_CTL_INIT_THIS_OPCYCLE_BIT_BY_CYCLE          ((Dem_u16_EventPosType)3U)    /* DemEventNumForOperationCycleStart */

/* DemAdjustVerifyProcess */
#define  DEM_EVENT_NUM_FOR_VERIFY_BY_CYCLE              ((Dem_u16_EventStrgIndexType)0xFFFFU)                /* DemEventNumForVerifyProcess */

#define  DEM_RECORD_NUM_FOR_VERIFY_BY_CYCLE             ((Dem_u32_TotalRecordNumType)0xFFFFFFFFU)        /* DemRecordNumForVerifyProcess */

#define DEM_MAX_NUMBER_EVENT_ENTRY_PERMANENT            ((Dem_u08_PFCIndexType)0U)            /* DemMaxNumberEventEntryPermanent    */
/* DemGroupOfDTC  */
#define DEM_GROUP_OF_DTC_NUM                            ((Dem_u08_GroupOfDTCIndexType)1U)     /* Number of DemGroupOfDTC */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* DemGroupOfDTC  */
typedef struct {
    Dem_u32_DTCGroupType     DemGroupDTCs;        /* DemGroupDTCs */
} Dem_GroupOfDTCType;

typedef struct {
    Dem_u16_FFDStoredIndexType  FirstCID;
    Dem_u16_FFDStoredIndexType  FirstEventStrgIndexUpper;
    Dem_u16_FFDStoredIndexType  FirstEventStrgIndexLower;
    Dem_u16_FFDStoredIndexType  RecordStatus;
    Dem_u16_FFDStoredIndexType  DataStart;
    Dem_u16_FFDStoredIndexType  LastCID;
    Dem_u16_FFDStoredIndexType  LastEventStrgIndexUpper;
    Dem_u16_FFDStoredIndexType  LastEventStrgIndexLower;
} Dem_FreezeFrameDataPosType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

extern CONST( AB_83_ConstV Dem_u16_EventStrgIndexType           ,DEM_CONFIG_DATA )  Dem_PrimaryMemEventStorageNum;

/* Dem_Main */
extern CONST( AB_83_ConstV Dem_u08_NvMProcCycleCounterType      ,DEM_CONFIG_DATA )  Dem_MainSyncNvmDivideCycleCount;
extern CONST( AB_83_ConstV Dem_u32_NvMProcIdleCycleCounterType  ,DEM_CONFIG_DATA )  Dem_MainSyncNvmDivideIdleCycleCount;
extern CONST( AB_83_ConstV Dem_u08_ControlProcCycleCounterType  ,DEM_CONFIG_DATA )  Dem_MainControlDivideCycleCount;

/* Dem_EventQueue */
extern CONST( AB_83_ConstV Dem_u16_EventQueueIndexType        ,DEM_CONFIG_DATA )  Dem_EventQueueSize;

/* Dem_Control */
extern CONST( AB_83_ConstV Dem_u16_EventQueueIndexType        ,DEM_CONFIG_DATA )  Dem_CtlSetEventNum;
extern CONST( AB_83_ConstV Dem_u16_AdjustCntByEventNumType    ,DEM_CONFIG_DATA )  Dem_ControlClearRamEventNumByCycle;
extern CONST( AB_83_ConstV Dem_u16_AdjustCntByEventNumType    ,DEM_CONFIG_DATA )  Dem_CtlNotifyControlDTCSettingAtOnce;
extern CONST( AB_83_ConstV Dem_u16_EventPosType               ,DEM_CONFIG_DATA )  Dem_CtlInitThisOpCycleBitByCycle;

/* Dem_DTC */
extern CONST( AB_83_ConstV Dem_u16_FilDTCSearchNumType        ,DEM_CONFIG_DATA )  Dem_FilDTCSearchLoopNumByCycle;

/* Dem_FFD */
extern CONST( AB_83_ConstV Dem_u16_FilFFDSearchNumType        ,DEM_CONFIG_DATA )  Dem_FilFFDSearchLoopNumByCycle;

/* DemAdjustEDRProcess */
extern CONST( AB_83_ConstV Dem_u16_EventStrgIndexType         ,DEM_CONFIG_DATA )  Dem_FilEDRSearchLoopNumByCycle;

/* DemAdjustVerifyProcess */
extern CONST( AB_83_ConstV Dem_u16_EventStrgIndexType         ,DEM_CONFIG_DATA) Dem_EventNumForVerifyByCycle;

extern CONST( AB_83_ConstV Dem_u32_TotalRecordNumType         ,DEM_CONFIG_DATA) Dem_RecordNumForVerifyByCycle;


/* DemConfigSet */
extern CONST( AB_83_ConstV Dem_u16_EventCtrlIndexType         ,DEM_CONFIG_DATA )  Dem_PrimaryMemEventConfigureNum;

/* DemGeneral */
extern CONST( AB_83_ConstV boolean                            ,DEM_CONFIG_DATA )  Dem_AgingRequiresNotFailedCycle;      /*  DemAgingRequiresNotFailedCycle           */
extern CONST( AB_83_ConstV Dem_UdsStatusByteType              ,DEM_CONFIG_DATA )  Dem_DtcStatusAvailabilityMask;        /*  DemDtcStatusAvailabilityMask             */
extern CONST( AB_83_ConstV Dem_DTCSeverityType                ,DEM_CONFIG_DATA )  Dem_DtcSeverityAvailabilityMask;      /*  DemDtcSeverityAvailabilityMask           */
extern CONST( AB_83_ConstV uint8                              ,DEM_CONFIG_DATA )  Dem_TypeOfDTCSupported;               /*  DemTypeOfDTCSupported                    */
extern CONST( AB_83_ConstV boolean                            ,DEM_CONFIG_DATA )  Dem_ResetTestFailedAtOpCycRestart;
extern CONST( AB_83_ConstV Dem_u08_ResetConfirmedBitOnOverflowType   ,DEM_CONFIG_DATA )  Dem_ResetConfirmedBitOnOverflow;      /*  DemResetConfirmedBitOnOverflow           */
extern CONST( AB_83_ConstV Dem_u08_DTCStatusBitHandlingType   ,DEM_CONFIG_DATA )  Dem_StatusBitHandlingTestFailedSinceLastClear;
extern CONST( AB_83_ConstV Dem_u08_FaultIndexType             ,DEM_CONFIG_DATA )  Dem_FailRecordNum;
extern CONST( AB_83_ConstV Dem_UdsStatusByteType              ,DEM_CONFIG_DATA )  Dem_DTCStatusProductSupportBit;       /*  DemDTCStatusProductSupportBit            */
extern CONST( AB_83_ConstV Dem_ModeType                       ,DEM_CONFIG_DATA )  Dem_NotifyDemModeMask;
extern CONST( AB_83_ConstV Dem_u08_ClearDTCBehaviorType       ,DEM_CONFIG_DATA )  Dem_ClearDTCBehavior;
extern CONST( AB_83_ConstV boolean                            ,DEM_CONFIG_DATA )  Dem_AgingRequiresTestedCycle;
extern CONST( AB_83_ConstV Dem_u08_EDRBehaviorAt0xFEType                ,DEM_CONFIG_DATA )  Dem_DTCExtDataRecordsBehaviorAt0xFE;
extern CONST( AB_83_ConstV Dem_u08_NotConfiguredEDRBehaviorType         ,DEM_CONFIG_DATA )  Dem_NotConfiguredDTCExtDataRecordNumberBehavior;
extern CONST( AB_83_ConstV Dem_u08_ClearDTCByDcmDuringInitializingType  ,DEM_CONFIG_DATA )  Dem_ClearDTCByDcmDuringInitializing;
extern CONST( AB_83_ConstV Dem_u08_MaxNumberOfDTCToStoreFreezeFrameType ,DEM_CONFIG_DATA )  Dem_MaxNumberOfDTCToStoreFreezeFrame;

/* DemGeneralOBD */

/* DemGroupOfDTC */
extern CONST( AB_83_ConstV Dem_u08_GroupOfDTCIndexType        ,DEM_CONFIG_DATA )  Dem_GroupDTCNum;
extern CONST( AB_83_ConstV Dem_GroupOfDTCType                 ,DEM_CONFIG_DATA )  Dem_GroupOfDTCTable[DEM_GROUP_OF_DTC_NUM];

extern CONST( AB_83_ConstV Dem_FreezeFrameDataPosType           ,DEM_CONFIG_DATA )  Dem_NonObdFreezeFrameDataPosTable;


/* OperationCycle Record */
extern CONST( AB_83_ConstV Dem_u08_OpCycleIndexType           ,DEM_CONFIG_DATA )  Dem_OperationCycleRecordStateNum;

extern CONST( AB_83_ConstV Dem_u16_PaddingIndexType           ,DEM_CONFIG_DATA )  Dem_ClrInfoRecordBlockPaddingSize;

extern CONST( AB_83_ConstV Dem_u16_BlockSizeType              ,DEM_CONFIG_DATA )  Dem_FFDRecordNvBlockSize;

extern CONST( AB_83_ConstV Dem_u08_FFListIndexType            ,DEM_CONFIG_DATA )  Dem_NonOBDFFRClassPerDTCMaxNum;

extern CONST( AB_83_ConstV Dem_u16_FFDStoredIndexType         ,DEM_CONFIG_DATA )  Dem_FreezeFrameDataStoredFormatSize;


#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>


#endif /* DEM_CFG_H */

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
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v5-5-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
