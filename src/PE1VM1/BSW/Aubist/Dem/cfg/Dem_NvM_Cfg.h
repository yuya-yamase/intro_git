/* Dem_NvM_Cfg_h(v5-9-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/NvM_Cfg/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_NVM_CFG_H
#define DEM_NVM_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_FAIL_RECORD_NUM         ((Dem_u08_FaultIndexType)DEM_PRIMEM_EVENTENTRY_MAXNUM)        /* Number of FaultRecord */

/* NvM Block Size For DEM */
#define DEM_EVENT_RECORD_NVBLOCK_SIZE      ((Dem_u16_BlockSizeType)8U)     /* NvM block size of Event Record                     */
#define DEM_FAIL_RECORD_NVBLOCK_SIZE       ((Dem_u16_BlockSizeType)12U)     /* NvM block size of Fault Record                     */
#define DEM_FFD_RECORD_NVBLOCK_SIZE        ((Dem_u16_BlockSizeType)32U)    /* NvM block size of FreezeFrameData Record           */
#define DEM_CLRINFO_RECORD_NVBLOCK_SIZE    ((Dem_u16_BlockSizeType)8U)     /* ClearInformation Record */
#define DEM_UDMEVENT_RECORD_NVBLOCK_SIZE   ((Dem_u16_BlockSizeType)4U)     /* Event Record in UserDefinedMemory */
#define DEM_UDMFAULT_RECORD_NVBLOCK_SIZE   ((Dem_u16_BlockSizeType)8U)     /* Fault Record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_RECORD_NVBLOCK_SIZE  ((Dem_u16_BlockSizeType)32U)    /* FreezeFrameData Record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_RECORD_NVBLOCK_SIZE  ((Dem_u16_BlockSizeType)32U)    /* FreezeFrameData Record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_RECORD_NVBLOCK_SIZE  ((Dem_u16_BlockSizeType)32U)    /* FreezeFrameData Record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_RECORD_NVBLOCK_SIZE  ((Dem_u16_BlockSizeType)32U)    /* FreezeFrameData Record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_RECORD_NVBLOCK_SIZE  ((Dem_u16_BlockSizeType)32U)    /* FreezeFrameData Record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_RECORD_NVBLOCK_SIZE  ((Dem_u16_BlockSizeType)32U)    /* FreezeFrameData Record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_RECORD_NVBLOCK_SIZE  ((Dem_u16_BlockSizeType)32U)    /* FreezeFrameData Record in UserDefinedMemory */

/* Max Number of RecordNumberIndex for all DTC */
#define DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM         ((Dem_u08_FFListIndexType)1U)            /* FreezeFrameData Record in PrimaryMemory */

/* Number of blocks required by one record */
#define DEM_FREEZE_FRAME_DATA_BLOCK_NUM               ((Dem_u16_NvBlockPerRecordNumType)1U)    /* FreezeFrameData Record in PrimaryMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_BLOCK_NUM                       ((Dem_u16_NvBlockPerRecordNumType)1U)
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_BLOCK_NUM                       ((Dem_u16_NvBlockPerRecordNumType)2U)
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_BLOCK_NUM                       ((Dem_u16_NvBlockPerRecordNumType)2U)
#define DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_BLOCK_NUM                       ((Dem_u16_NvBlockPerRecordNumType)3U)
#define DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_BLOCK_NUM                       ((Dem_u16_NvBlockPerRecordNumType)7U)
#define DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_BLOCK_NUM                       ((Dem_u16_NvBlockPerRecordNumType)1U)
#define DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_BLOCK_NUM                       ((Dem_u16_NvBlockPerRecordNumType)2U)

/* Format size required for one record to store */
#define DEM_FREEZE_FRAME_DATA_STORED_FORMAT_SIZE      ((Dem_u16_FFDStoredIndexType)32U)    /* The Size of 1FreezeFrameRecord for store           */
#define DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_STORED_FORMAT_SIZE              ((Dem_u16_FFDStoredIndexType)32U)
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_STORED_FORMAT_SIZE              ((Dem_u16_FFDStoredIndexType)64U)
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_STORED_FORMAT_SIZE              ((Dem_u16_FFDStoredIndexType)64U)
#define DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_STORED_FORMAT_SIZE              ((Dem_u16_FFDStoredIndexType)96U)
#define DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_STORED_FORMAT_SIZE              ((Dem_u16_FFDStoredIndexType)224U)
#define DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_STORED_FORMAT_SIZE              ((Dem_u16_FFDStoredIndexType)32U)
#define DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_STORED_FORMAT_SIZE              ((Dem_u16_FFDStoredIndexType)64U)

/* Number of record list */
#define DEM_EVENT_RECORD_LIST_NUM                     ((Dem_u16_EventStrgIndexType)21U)    /* Number of record lists of EventRecord                 */
#define DEM_FAIL_RECORD_LIST_NUM                      ((Dem_u08_FaultIndexType)21U)    /* Number of record lists of FailRecord                  */
#define DEM_FFD_RECORD_LIST_NUM                       ((Dem_u08_FFDIndexType)21U)      /* Number of record lists of FreezeFrameDataRecord       */

#define DEM_UDM_RKDEMUDM_OCCURRENCE1_EVENT_RECORD_NUM           ((Dem_u16_UdmEventStrgIndexType)19U)                /* Number of Event record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_EVENT_RECORD_NUM           ((Dem_u16_UdmEventStrgIndexType)1U)                /* Number of Event record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_EVENT_RECORD_NUM           ((Dem_u16_UdmEventStrgIndexType)4U)                /* Number of Event record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_EVENT_RECORD_NUM           ((Dem_u16_UdmEventStrgIndexType)1U)                /* Number of Event record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_EVENT_RECORD_NUM           ((Dem_u16_UdmEventStrgIndexType)1U)                /* Number of Event record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_MAINTENANCE1_EVENT_RECORD_NUM           ((Dem_u16_UdmEventStrgIndexType)3U)                /* Number of Event record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_EVENT_RECORD_NUM           ((Dem_u16_UdmEventStrgIndexType)2U)                /* Number of Event record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE1_FAULT_RECORD_NUM           ((Dem_u08_UdmFaultIndexType)19U)                /* Number of Fault record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_FAULT_RECORD_NUM           ((Dem_u08_UdmFaultIndexType)1U)                /* Number of Fault record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FAULT_RECORD_NUM           ((Dem_u08_UdmFaultIndexType)4U)                /* Number of Fault record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FAULT_RECORD_NUM           ((Dem_u08_UdmFaultIndexType)1U)                /* Number of Fault record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FAULT_RECORD_NUM           ((Dem_u08_UdmFaultIndexType)1U)                /* Number of Fault record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_MAINTENANCE1_FAULT_RECORD_NUM           ((Dem_u08_UdmFaultIndexType)3U)                /* Number of Fault record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FAULT_RECORD_NUM           ((Dem_u08_UdmFaultIndexType)2U)                /* Number of Fault record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_RECORD_NUM             ((Dem_u16_UdmFFDIndexType)57U)                  /* Number of FreezeFrameData record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_RECORD_NUM             ((Dem_u16_UdmFFDIndexType)3U)                  /* Number of FreezeFrameData record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_RECORD_NUM             ((Dem_u16_UdmFFDIndexType)12U)                  /* Number of FreezeFrameData record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_RECORD_NUM             ((Dem_u16_UdmFFDIndexType)3U)                  /* Number of FreezeFrameData record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_RECORD_NUM             ((Dem_u16_UdmFFDIndexType)3U)                  /* Number of FreezeFrameData record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_RECORD_NUM             ((Dem_u16_UdmFFDIndexType)3U)                  /* Number of FreezeFrameData record in UserDefinedMemory */
#define DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_RECORD_NUM             ((Dem_u16_UdmFFDIndexType)2U)                  /* Number of FreezeFrameData record in UserDefinedMemory */

/* OperationCycle Record */
#define DEM_OPERATION_CYCLE_RECORD_STATE_NUM          ((Dem_u08_OpCycleIndexType)0U)

/* ClrInfo Record */
#define DEM_USER_DEFINED_MEMORY_NUM                   ((Dem_u16_UdmDemMemKindIndexType)7U)        /* Number of UserDefinedMemory Except External Memory */
#define DEM_USER_DEFINED_MEMORY_INFO_NUM              ((Dem_u08_UdmMemoryInfoTableIndexType)3U)        /* Number of DTC Origin */
#define DEM_USER_DEFINED_MEMORY_INTERNAL_INFO_NUM     ((Dem_u08_UdmMemoryInfoTableIndexType)3U)        /* Number of DTC Origin Except External Memory */

/* Padding size for adjusting record size to block size */
#define DEM_CLRINFO_RECORD_PADDINGSIZE_TO_BLOCKSIZE   ((Dem_u16_PaddingIndexType)3U)
#define DEM_UDMFAULT_RECORD_PADDINGSIZE_TO_BLOCKSIZE  ((Dem_u16_PaddingIndexType)1U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    Dem_u08_FaultIndexType       FaultIndex;
    Dem_UdsStatusByteType        StatusOfDTC;
    Dem_u08_FailureCounterType   FailureCounter;
    Dem_u08_EventOccurrenceCounterType    OccurrenceCounter;
    Dem_u08_ConsistencyIdType    ConsistencyCounterForFault;
    Dem_u08_ClearIdType          ClearID;
    Dem_u08_DTCStatusExType      ExtendStatusOfDTC;
    Dem_u08_DTCStatusEx2Type     ExtendStatusOfDTC2;
} Dem_EventRecordType;

typedef struct
{
    Dem_u16_EventStrgIndexType       EventStrgIndex;
    Dem_u16_OccrOrderType        OccurrenceOrder;
    Dem_u16_OccrOrderType        ConfirmedOccurrenceOrder;
    Dem_u16_OccrOrderType        MILOccurrenceOrder;
    Dem_u08_AgingCounterType     AgingCounter;
    Dem_u08_HealingCounterType   HealingCounter;
    Dem_u08_ConsistencyIdType    ConsistencyCounterForFault;
    Dem_u08_FFDIndexType         RecordNumberIndex[ DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM ];
} Dem_FaultRecordType;

typedef struct
{
    uint8     Data[DEM_FREEZE_FRAME_DATA_STORED_FORMAT_SIZE];
} Dem_FreezeFrameRecordType;


typedef struct
{
    Dem_u08_ClearIdType     ClearID;
    Dem_u08_ClearIdType     ObdClearID;
    Dem_u08_ClearIdType     UdmClearID[ DEM_USER_DEFINED_MEMORY_INTERNAL_INFO_NUM ];
    uint8                   Reserve[ DEM_CLRINFO_RECORD_PADDINGSIZE_TO_BLOCKSIZE ];
} Dem_ClrInfoRecordType;

typedef struct
{
    Dem_u08_UdmFaultIndexType    UdmFaultIndex;
    Dem_UdsStatusByteType        StatusOfDTC;
    Dem_u08_ConsistencyIdType    ConsistencyIdForFault;
    Dem_u08_ClearIdType          UdmClearID;
} Dem_UdmEventRecordType;

typedef struct
{
    Dem_u16_OccrOrderType                  UdmFaultOccurrenceOrder;
    Dem_u16_UdmFFDIndexType                RecordNumberIndex;
    Dem_u16_UdmEventIndexType              UdmEventIndex;
    Dem_u08_ConsistencyIdType              ConsistencyIdForFault;
    uint8                                  Reserve[ DEM_UDMFAULT_RECORD_PADDINGSIZE_TO_BLOCKSIZE ];
} Dem_UdmFaultRecordType;

typedef struct
{
    uint8     Data[ DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_STORED_FORMAT_SIZE ];
} Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordType;

typedef struct
{
    uint8     Data[ DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_STORED_FORMAT_SIZE ];
} Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordType;

typedef struct
{
    uint8     Data[ DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_STORED_FORMAT_SIZE ];
} Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordType;

typedef struct
{
    uint8     Data[ DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_STORED_FORMAT_SIZE ];
} Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordType;

typedef struct
{
    uint8     Data[ DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_STORED_FORMAT_SIZE ];
} Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordType;

typedef struct
{
    uint8     Data[ DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_STORED_FORMAT_SIZE ];
} Dem_Udm_RkDemUDM_Maintenance1_FreezeFrameRecordType;

typedef struct
{
    uint8     Data[ DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_STORED_FORMAT_SIZE ];
} Dem_Udm_RkDemUDM_SystemOperation2_FreezeFrameRecordType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

extern VAR( Dem_EventRecordType,            DEM_VAR_SAVED_ZONE ) Dem_EventRecordList[ DEM_EVENT_RECORD_LIST_NUM ];
extern VAR( Dem_FaultRecordType,            DEM_VAR_SAVED_ZONE ) Dem_FaultRecordList[ DEM_FAIL_RECORD_LIST_NUM ];
extern VAR( Dem_FreezeFrameRecordType,      DEM_VAR_SAVED_ZONE ) Dem_FreezeFrameRecordList[ DEM_FFD_RECORD_LIST_NUM ];
extern VAR( Dem_ClrInfoRecordType,          DEM_VAR_SAVED_ZONE ) Dem_ClrInfoRecord;
extern VAR( Dem_UdmEventRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE1_EVENT_RECORD_NUM ];
extern VAR( Dem_UdmEventRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence2_EventRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE2_EVENT_RECORD_NUM ];
extern VAR( Dem_UdmEventRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence2_NM_EventRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_EVENT_RECORD_NUM ];
extern VAR( Dem_UdmEventRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence3_NM_EventRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_EVENT_RECORD_NUM ];
extern VAR( Dem_UdmEventRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence7_NM_EventRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_EVENT_RECORD_NUM ];
extern VAR( Dem_UdmEventRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Maintenance1_EventRecordList[ DEM_UDM_RKDEMUDM_MAINTENANCE1_EVENT_RECORD_NUM ];
extern VAR( Dem_UdmEventRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_SystemOperation2_EventRecordList[ DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_EVENT_RECORD_NUM ];
extern VAR( Dem_UdmFaultRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE1_FAULT_RECORD_NUM ];
extern VAR( Dem_UdmFaultRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence2_FaultRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE2_FAULT_RECORD_NUM ];
extern VAR( Dem_UdmFaultRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence2_NM_FaultRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FAULT_RECORD_NUM ];
extern VAR( Dem_UdmFaultRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence3_NM_FaultRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FAULT_RECORD_NUM ];
extern VAR( Dem_UdmFaultRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence7_NM_FaultRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FAULT_RECORD_NUM ];
extern VAR( Dem_UdmFaultRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Maintenance1_FaultRecordList[ DEM_UDM_RKDEMUDM_MAINTENANCE1_FAULT_RECORD_NUM ];
extern VAR( Dem_UdmFaultRecordType,         DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_SystemOperation2_FaultRecordList[ DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FAULT_RECORD_NUM ];
extern VAR( Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordType, DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_RECORD_NUM ];
extern VAR( Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordType, DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_RECORD_NUM ];
extern VAR( Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordType, DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_RECORD_NUM ];
extern VAR( Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordType, DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_RECORD_NUM ];
extern VAR( Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordType, DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_RECORD_NUM ];
extern VAR( Dem_Udm_RkDemUDM_Maintenance1_FreezeFrameRecordType, DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Maintenance1_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_RECORD_NUM ];
extern VAR( Dem_Udm_RkDemUDM_SystemOperation2_FreezeFrameRecordType, DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_SystemOperation2_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_RECORD_NUM ];

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* DEM_NVM_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-09-26                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
