/* Dem_NvM_Cfg_h(v5-5-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
#define DEM_CLRINFO_RECORD_NVBLOCK_SIZE    ((Dem_u16_BlockSizeType)4U)     /* ClearInformation Record */

/* Max Number of RecordNumberIndex for all DTC */
#define DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM         ((Dem_u08_FFListIndexType)1U)            /* FreezeFrameData Record in PrimaryMemory */

/* Number of blocks required by one record */
#define DEM_FREEZE_FRAME_DATA_BLOCK_NUM               ((Dem_u16_NvBlockPerRecordNumType)1U)    /* FreezeFrameData Record in PrimaryMemory */

/* Format size required for one record to store */
#define DEM_FREEZE_FRAME_DATA_STORED_FORMAT_SIZE      ((Dem_u16_FFDStoredIndexType)32U)    /* The Size of 1FreezeFrameRecord for store           */

/* Number of record list */
#define DEM_EVENT_RECORD_LIST_NUM                     ((Dem_u16_EventStrgIndexType)2U)    /* Number of record lists of EventRecord                 */
#define DEM_FAIL_RECORD_LIST_NUM                      ((Dem_u08_FaultIndexType)2U)    /* Number of record lists of FailRecord                  */
#define DEM_FFD_RECORD_LIST_NUM                       ((Dem_u08_FFDIndexType)2U)      /* Number of record lists of FreezeFrameDataRecord       */


/* OperationCycle Record */
#define DEM_OPERATION_CYCLE_RECORD_STATE_NUM          ((Dem_u08_OpCycleIndexType)0U)

/* Padding size for adjusting record size to block size */
#define DEM_CLRINFO_RECORD_PADDINGSIZE_TO_BLOCKSIZE   ((Dem_u16_PaddingIndexType)2U)

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
    uint8                   Reserve[ DEM_CLRINFO_RECORD_PADDINGSIZE_TO_BLOCKSIZE ];
} Dem_ClrInfoRecordType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data - permanent                                                         */
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
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
