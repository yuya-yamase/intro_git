/* Dem_UserDefMem_Cfg_h(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/UserDefMem_Cfg/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_USERDEFMEM_CFG_H
#define DEM_USERDEFMEM_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "Dem_Data_Cfg.h"
#include "Dem_NvM_Cfg.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_UDMEVENT_CONFIGURE_NUM           ((Dem_u16_UdmEventIndexType)DEM_USRDEFMEM_TOTAL_EVENT_NUM)    /* Number of DemEventParameter in UserDefinedMemory */
#define DEM_UDM_DTC_ATT_CONFIGURE_NUM        ((Dem_u16_UdmDTCAttrIndexType)31U)              /* Number of DemDTCAttribute in UserDefinedMemory */

#define DEM_UDM_RKDEMUDM_OCCURRENCE1_KIND_INDEX                 ((Dem_u16_UdmDemMemKindIndexType)0U)
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_KIND_INDEX                 ((Dem_u16_UdmDemMemKindIndexType)1U)
#define DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_KIND_INDEX                 ((Dem_u16_UdmDemMemKindIndexType)2U)
#define DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_KIND_INDEX                 ((Dem_u16_UdmDemMemKindIndexType)3U)
#define DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_KIND_INDEX                 ((Dem_u16_UdmDemMemKindIndexType)4U)
#define DEM_UDM_RKDEMUDM_MAINTENANCE1_KIND_INDEX                 ((Dem_u16_UdmDemMemKindIndexType)5U)
#define DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_KIND_INDEX                 ((Dem_u16_UdmDemMemKindIndexType)6U)

#define DEM_UDM_MAX_NUMBER_FF_PER_DTC        ((Dem_u16_FFRecNumStoredIndexType)3U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    DemCallbackEventStatusChangedFncPTR    DemCallbackEventStatusChangedFnc;        /* DemCallbackEventUdsStatusChangedFnc        */
    DemCallbackInitMForEFncPTR             DemCallbackInitMForEFnc;                 /* DemCallbackInitMForEFnc                    */
    Dem_u32_DTCValueType                   DemDtcValue;                             /* DemDtcValue of DemDTC                      */
    Dem_u16_EventAttributeType             DemEventAttribute;                       /* Attribute information of DemEventParameter */
    Dem_u16_UdmDTCAttrIndexType            DemDTCAttributesRef;                     /* DemDTCAttributesRef                        */
    Dem_u08_OpCycleIndexType               DemOperationCycleRef;                    /* DemOperationCycleRef                       */
    Dem_u08_EventPriorityType              DemEventPriority;                        /* DemEventPriority                           */
} Dem_UdmEventParameterType;

typedef struct {
    Dem_u16_FFClassIndexType              DemFreezeFrameClassRef;               /* DemFreezeFrameClassRef        */
    Dem_u16_UdmFFDIndexType               DemMaxNumberFreezeFrameRecords;       /* DemMaxNumberFreezeFrameRecords */
    Dem_u16_ExDataClassIndexType          DemExDataClassRef;                    /* DemExtendedDataClassRef       */
    Dem_u16_UdmDemMemKindIndexType        DemMemoryDestinationRef;              /* DemMemoryDestinationRef       */
} Dem_UdmDTCAttributeType;

typedef struct {
    Dem_u16_UdmEventIndexType                DemSearchStartIndexOfEventParameterTable;  /* Search start index of EventParameterTable */
    Dem_u16_UdmEventIndexType                DemConfigureEventNumOfMemorySelection;     /* Event num of MemorySelection              */
    Dem_u16_UdmFFDIndexType                  DemMaxNumberFreezeFrameUserDefinedPerDTC;  /* Max Number of FreezeFrame per DTC         */
    Dem_u08_UdmFaultIndexType                DemMaxNumberEventEntryUserDefined;         /* DemMaxNumberEventEntryUserDefined         */
    Dem_u08_EventDisplacementStrategyType    DemEventDisplacementStrategy;              /* DemEventDisplacementStrategy              */
    Dem_u08_UdmMemoryInfoTableIndexType      DemUserDefinedMemoryInfoTableIndex;        /* Memory Info Table Index                   */
} Dem_UserDefinedMemoryGroupType;

typedef struct {
    Dem_u16_UdmDemMemKindIndexType           DemUserDefinedMemoryKindIndexStart;        /* Kind Index Start                          */
    Dem_u16_UdmDemMemKindIndexType           DemUserDefinedMemoryKindIndexNum;          /* Kind Index Num                            */
    Dem_DTCOriginType                        DemUserDefinedMemoryIdentifier;            /* DemUserDefinedMemoryIdentifier            */
    Dem_UdsStatusByteType                    DemDtcStatusAvailabilityMask;              /* DemDtcStatusAvailabilityMask              */
    Dem_u08_UserDefinedMemoryType            DemMemoryType;                             /* DemUserDefinedMemoryType                  */
} Dem_UserDefinedMemoryInfoTableType;


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

extern CONST( AB_83_ConstV Dem_UdmEventParameterType        ,DEM_CONFIG_DATA ) Dem_UdmEventParameterTable[ DEM_UDMEVENT_CONFIGURE_NUM ];
extern CONST( AB_83_ConstV Dem_UdmDTCAttributeType          ,DEM_CONFIG_DATA ) Dem_UdmDTCAttributeTable[ DEM_UDM_DTC_ATT_CONFIGURE_NUM ];
extern CONST( AB_83_ConstV Dem_UserDefinedMemoryGroupType            ,DEM_CONFIG_DATA ) Dem_UserDefinedMemoryGroupTable[ DEM_USER_DEFINED_MEMORY_NUM ];
extern CONST( AB_83_ConstV Dem_UserDefinedMemoryInfoTableType        ,DEM_CONFIG_DATA ) Dem_UserDefinedMemoryInfoTable[ DEM_USER_DEFINED_MEMORY_INFO_NUM ];

extern CONST( AB_83_ConstV Dem_u16_UdmEventIndexType        ,DEM_CONFIG_DATA ) Dem_UdmEventConfigureNum;
extern CONST( AB_83_ConstV Dem_u16_FFRecNumStoredIndexType  ,DEM_CONFIG_DATA ) Dem_UdmMaxNumberFFPerDTC;


#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

#endif /* DEM_USERDEFMEM_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
