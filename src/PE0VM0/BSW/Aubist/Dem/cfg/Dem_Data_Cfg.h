/* Dem_Data_Cfg_h(v5-5-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/Data_Cfg/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_DATA_CFG_H
#define DEM_DATA_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "Dem_Cfg.h"
#include "Dem_EDR_Cfg.h"
#include "Dem_NvM_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_DTC_ATT_CONFIGURE_NUM           ((Dem_u16_DTCAttrIndexType)2U)             /* Number of DemDTCAttribute           */
#define DEM_DTC_FFR_CLASS_CONFIGURE_NUM     ((Dem_u16_FFClassIndexType)1U)             /* Number of DemFreezeFrameClass       */
#define DEM_DID_NUM                         ((Dem_u32_DIDClassIndexType)3U)            /* Number of Dem_DIDClassTable         */
#define DEM_DATAELEMENT_NUM                 ((Dem_u16_DataElementClassIndexType)3U)    /* Number of DemDataElementClass       */
#define DEM_FFR_REC_NUM_CLASS_CONFIGURE_NUM ((Dem_u16_FFRecNumClassIndexType)1U)        /* Number of DemFreezeFrameRecNumClass */
#define DEM_FFR_RECORD_CLASS_CONFIGURE_NUM  ((Dem_u08_FFRecordClassIndexType)1U)        /* Number of DemFreezeFrameRecordClass */

#define DEM_FF_RECORD_CLASS_REF_MAX_NUM     ((Dem_u08_FFListIndexType)1U)               /* Max Number of DemFreezeFrameRecordClassRef for all DemFreezeFrameRecNumClass */
#define DEM_DID_NUM_PER_FRAME_MAX_NUM       ((Dem_u08_DIDClassPerFFIndexType)3U)        /* Max Number of DemDidClass in DemFreezeFrameClass in all DemFreezeFrameClass  */
#define DEM_DATAELEMENT_NUM_PER_DID_MAX_NUM ((Dem_u08_DtElNumPerDIDIndexType)1U)        /* Max Number of DemDataElementClass in DemDidClass in all DemDidClass          */

#define DEM_OBD_EVENT_CONFIGURE_NUM         ((Dem_u16_EventStrgIndexType)0U)              /* Number of OBD DemEventParameter */

/* FreezeFrameData size definition */
#define DEM_OBD_FFD_SIZE                    ((Dem_u16_FFDStoredIndexType)0U)

#define DEM_FFR_MAX_LENGTH                  ((Dem_u16_FFDStoredIndexType)17U)

#define DEM_OBD_FFD_RECORD_NUM                 ((Dem_u08_FFDIndexType)0U)
#define DEM_NON_OBD_FFD_RECORD_NUM             ((Dem_u08_FFDIndexType)2U)

/* Total number of RecordNumber per DTC */
#define DEM_TOTAL_NUM_OF_RECNUM_PER_DTC        ((Dem_u16_FFRecNumStoredIndexType)2U)

#define DEM_TSFF_TOTAL_TIMESERIES_FF_RECORD_NUM                 (DEM_TSFFDINDEX_INVALID)               /* Total number of Time Series FreezeFrame records                    */

/* EventAttribute definition */
#define DEM_EVTATTR_MISFIRE_CAT                 ((Dem_u16_EventAttributeType)0x8000U)
#define DEM_EVTATTR_MISFIRE                     ((Dem_u16_EventAttributeType)0x4000U)
#define DEM_EVTATTR_SIMILAR                     ((Dem_u16_EventAttributeType)0x2000U)


#define DEM_EVTATTR_PFCCLRPTN_MINRATIO          ((Dem_u16_EventAttributeType)0x0400U)
#define DEM_EVTATTR_CLEARALLOWED                ((Dem_u16_EventAttributeType)0x0200U)
#define DEM_EVTATTR_PREFF_USE                   ((Dem_u16_EventAttributeType)0x0100U)




#define DEM_EVTATTR_FCTHRESADAPT_ADAPTABLE      ((Dem_u16_EventAttributeType)0x0008U)
#define DEM_EVTATTR_MIL_USE                     ((Dem_u16_EventAttributeType)0x0004U)
#define DEM_EVTATTR_INDICATOR_USE               ((Dem_u16_EventAttributeType)0x0002U)
#define DEM_EVTATTR_HEALING_USE                 ((Dem_u16_EventAttributeType)0x0001U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/******************/
/* Event and DTC  */
/******************/
typedef struct {
    DemCallbackEventStatusChangedFncPTR    DemCallbackEventStatusChangedFnc;            /* DemCallbackEventUdsStatusChangedFnc         */
    DemCallbackInitMForEFncPTR             DemCallbackInitMForEFnc;                     /* DemCallbackInitMForEFnc                     */
    Dem_u16_EventAttributeType             DemEventAttribute;                           /* Attribute information of DemEventParameter  */
    Dem_u08_OpCycleIndexType               DemOperationCycleRef;                        /* DemOperationCycleRef                        */
    Dem_u08_OpCycleIndexType               DemHealingAgingCycleRef;                     /* DemHealingAgingCycleRef                     */
} Dem_EventParameterType;

typedef struct {
    Dem_u32_DTCValueType                   DemDtcValue;                                 /* DemDtcValue of DemDTC                       */
    Dem_u16_EventAttributeType             DemEventAttribute;                           /* Attribute information of DemEventParameter  */
    Dem_u16_DTCAttrIndexType               DemDTCAttributesRef;                         /* DemDTCAttributesRef                         */
    Dem_DTCSeverityType                    DemDTCClass;                                 /* DemDTCClass                                 */
    Dem_u08_HealingCounterType             DemIndicatorHealingCycleCounterThreshold;    /* DemIndicatorHealingCycleCounterThreshold    */
    Dem_u08_EventPriorityType              DemEventPriority;                            /* DemEventPriority                            */
} Dem_EventParameterStorageType;

/******************/
/* DTCAttribute   */
/******************/
typedef struct {
    Dem_u16_FFClassIndexType              DemFreezeFrameClassRef;             /* DemFreezeFrameClassRef               */
    Dem_u16_FFRecNumClassIndexType        DemFreezeFrameRecNumClassRef;       /* DemFreezeFrameRecNumClassRef         */
    Dem_u16_ExDataClassIndexType          DemExDataClassRef;                  /* DemExtendedDataClassRef              */
    Dem_u08_AgingCounterType              DemAgingCycleCounterThreshold;      /* DemAgingCycleCounterThreshold        */
    boolean                               DemAgingAllowed;                    /* DemAgingAllowed                      */
} Dem_DTCAttributeType;

/******************/
/* FreezeFrame    */
/******************/
typedef struct {
    Dem_u32_DIDClassIndexType           DemDidClassRef[ DEM_DID_NUM_PER_FRAME_MAX_NUM ];
    Dem_u08_DIDClassPerFFIndexType      DemDidClassNum;
    Dem_u16_FFDStoredIndexType          DemDidClassSize;
} Dem_FreezeFrameClassType;   /*  DID number and DID index by FreezeFrame - ROM -    */

/******************/
/* DID            */
/******************/
typedef struct {
    Dem_u16_DIDNumberType                DemDidIdentifier;
    Dem_u16_FFDStoredIndexType           DemDidDataSize;
    Dem_u16_FFDStoredIndexType           DemPidPos;
    Dem_u08_PIDNumberType                DemPidIdentifier;
    Dem_u08_DtElNumPerDIDIndexType       DemDataElementClassNum;
    Dem_u16_DataElementClassIndexType    DemDataElementClassRef[ DEM_DATAELEMENT_NUM_PER_DID_MAX_NUM ];
} Dem_DidClassType;

typedef struct {
    Dem_u16_DataElementSizeType DemDataElementSize;
    DemDataElementReadFncPTR    DemDataElementReadFnc;
} Dem_DataElementClassType;   /*   DataElement information - ROM -    */

typedef struct {
    Dem_u08_FFRecordClassIndexType       DemFreezeFrameRecordClassRef[ DEM_FF_RECORD_CLASS_REF_MAX_NUM ];
} Dem_FreezeFrameRecNumClassType;

typedef struct {
    Dem_u08_FFRecordNumberType       DemFreezeFrameRecordNumber;
    Dem_u08_StorageTriggerType       DemFreezeFrameRecordTrigger;
    Dem_u08_UpdateRecordType         DemFreezeFrameRecordUpdate;
} Dem_FreezeFrameRecordClassType;


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

extern CONST( AB_83_ConstV Dem_DidClassType                ,DEM_CONFIG_DATA )  Dem_DIDClassTable[ DEM_DID_NUM ];
extern CONST( AB_83_ConstV Dem_FreezeFrameClassType        ,DEM_CONFIG_DATA )  Dem_FreezeFrameClassTable[ DEM_DTC_FFR_CLASS_CONFIGURE_NUM ];
extern CONST( AB_83_ConstV Dem_DTCAttributeType            ,DEM_CONFIG_DATA )  Dem_DTCAttributeTable[DEM_DTC_ATT_CONFIGURE_NUM+(Dem_u16_DTCAttrIndexType)1U];
extern CONST( AB_83_ConstV Dem_EventParameterType          ,DEM_CONFIG_DATA )  Dem_EventParameterTable[ DEM_PRIMEM_EVENT_NUM ];
extern CONST( AB_83_ConstV Dem_EventParameterStorageType   ,DEM_CONFIG_DATA )  Dem_EventParameterStorageTable[ DEM_PRIMEM_EVENTSTORAGE_NUM ];
extern CONST( AB_83_ConstV Dem_DataElementClassType        ,DEM_CONFIG_DATA )  Dem_DataElementClassTable[ DEM_DATAELEMENT_NUM ];
extern CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType  ,DEM_CONFIG_DATA )  Dem_FreezeFrameRecNumClassTable[ DEM_FFR_REC_NUM_CLASS_CONFIGURE_NUM ];
extern CONST( AB_83_ConstV Dem_FreezeFrameRecordClassType  ,DEM_CONFIG_DATA )  Dem_FreezeFrameRecordClassTable[ DEM_FFR_RECORD_CLASS_CONFIGURE_NUM ];

extern CONST( AB_83_ConstV Dem_u08_FFRecordClassIndexType     ,DEM_CONFIG_DATA )  Dem_FFRRecordClassConfigureNum;

extern CONST( AB_83_ConstV Dem_u08_FFListIndexType            ,DEM_CONFIG_DATA )  Dem_FFRecordClassRefMaxNum;

extern CONST( AB_83_ConstV Dem_u16_EventStrgIndexType         ,DEM_CONFIG_DATA )  Dem_ObdEventNum;

extern CONST( AB_83_ConstV Dem_u16_FFDStoredIndexType         ,DEM_CONFIG_DATA )  Dem_FFRMaxLength;

extern CONST( AB_83_ConstV Dem_u08_FFDIndexType               ,DEM_CONFIG_DATA )  Dem_ObdFFDRecordNum;
extern CONST( AB_83_ConstV Dem_u08_FFDIndexType               ,DEM_CONFIG_DATA )  Dem_NonObdFFDRecordNum;

extern CONST( AB_83_ConstV Dem_u16_FFRecNumStoredIndexType    ,DEM_CONFIG_DATA )  Dem_TotalNumOfRecNumPerDTC;

extern CONST( AB_83_ConstV Dem_u16_TSFFDIndexType             ,DEM_CONFIG_DATA )  Dem_TSFFTotalTimeseriesFFRecordNum;

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

#endif /* DEM_DATA_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-07-27                                              */
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
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
