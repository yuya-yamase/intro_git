/* Dem_Types_h(v5-8-0)                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Types/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DEM_TYPES_H
#define DEM_TYPES_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <Rte_Dem_Type.h>
#include <Dem/Dem_FuncSwitch.h>

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------*/
/*  for Interface.          */
/*--------------------------*/
typedef struct
{
    Std_ReturnType  Dummy;

}Dem_ConfigType;                                    /*  [SWS_Dem_00924] Dem_ConfigType : Structure */

typedef uint16       Dem_ModeType;                      /* (Extended)Return value of Dem_GetMode() : uint8 */

typedef uint8        Dem_MaxNumOfEventEntryType;        /* (Extended)MaxNumber Of EventEntry type   */
typedef uint16       Dem_DTRIdType;                     /* (Extended)DTR Id type                    */

#define DEM_BLOCKID_MULTIBLOCK                      ((Dem_BlockIdType)0x0000U)

#define DEM_RECORDKIND_INVALID                      ((Dem_RecordKindType)0xFFU)

/*--------------------------*/
/*  for PostBuild           */
/*--------------------------*/
typedef uint8        Dem_PB_EventAttributeType;              /*  event attribute type.               */
typedef uint8        Dem_FailureCycleCounterThresholdType;   /*  failure cycle threshold type.       */

/*--------------------------*/
/*  internal(required type.)*/
/*--------------------------*/
typedef uint32       Dem_u32_DTCValueType;                  /*  DTC value                           */
typedef uint32       Dem_u32_DTCGroupType;                  /*  DTC Group (equal to Dem_u32_DTCValueType.)                          */
typedef uint16       Dem_u16_ObdDTCValueType;               /*  OBD DTC value                          */

typedef uint16       Dem_u16_DIDNumberType;                 /*  DID Number type.         */
typedef uint8        Dem_u08_PIDNumberType;                 /*  PID Number type.         */
typedef uint8        Dem_u08_FFRecordNumberType;            /*  FreezeFrame RecordNumber type.         */
 /*  Dem_u16_FFDStoredIndexType : FreezeFrame RecorSize type.        */

typedef uint8        Dem_u08_StoredDataRecordNumberType;    /*  StoredData RecordNumber type.         */
typedef uint32       Dem_u32_StoredDataRecordSizeType;      /*  StoredData RecordSize type.         */
#define DEM_STOREDDATA_RECNUM_00    ((Dem_u08_StoredDataRecordNumberType)0x00U)
#define DEM_STOREDDATA_RECNUM_FF    ((Dem_u08_StoredDataRecordNumberType)0xFFU)

typedef uint8        Dem_u08_EDRRecordNumberType;           /*  ExtendedData RecordNumber type.        */
#define DEM_EDR_RECNUM_00   ((Dem_u08_EDRRecordNumberType)0x00U)        /*  DEM_GETSIZEBYDTC_WRONG_RECNUM                               */
#define DEM_EDR_RECNUM_01   ((Dem_u08_EDRRecordNumberType)0x01U)        /*  DEM_GETSIZEBYDTC_OK :   single target : range minimum       */
#define DEM_EDR_RECNUM_90   ((Dem_u08_EDRRecordNumberType)0x90U)        /*  DEM_GETSIZEBYDTC_OK :   single target : range minimum       */
#define DEM_EDR_RECNUM_92   ((Dem_u08_EDRRecordNumberType)0x92U)        /*  DTR RecordNumber    :   single target : DTR RecordNumber    */
#define DEM_EDR_RECNUM_9F   ((Dem_u08_EDRRecordNumberType)0x9FU)        /*  DEM_GETSIZEBYDTC_OK :   single target : range maximum       */
#define DEM_EDR_RECNUM_EF   ((Dem_u08_EDRRecordNumberType)0xEFU)        /*  DEM_GETSIZEBYDTC_OK :   single target : range minimum       */
#define DEM_EDR_RECNUM_FE   ((Dem_u08_EDRRecordNumberType)0xFEU)        /*  OBD RecordNumber    :   multiple target : OBD RecordNumber  */
#define DEM_EDR_RECNUM_FF   ((Dem_u08_EDRRecordNumberType)0xFFU)        /*  All RecordNumber    :   multiple target : All RecordNumber  */

typedef uint16       Dem_u16_EDRRecordSizeType;             /*  ExtendedData RecordSize type.        */

typedef uint16       Dem_u16_DataElementSizeType;           /*  DataElement Size type.        */

typedef uint8        Dem_u08_DTRUasidType;                  /*  for DTR UasID  type                     */
typedef uint16       Dem_u16_DTRValueStoreType;             /*  for DTR value store type                */
typedef sint16       Dem_s16_DTRValueStoreType;             /*  for DTR value store type(signed)        */
typedef uint32       Dem_u32_DTRValueRawType;              /*  for DTR value raw type                 */
typedef sint32       Dem_s32_DTRValueRawType;              /*  for DTR value raw type                 */

typedef uint8       Dem_u08_ReadinessKindType;           /*  Readiness Kind type                */
typedef uint8       Dem_u08_ReadinessCondType;           /*  Readiness Data type                */

/*  typedef uint8       DemOBDEngineType(no cast in macro definition.)  */
#define DEM_IGNITION_COMPRESSION                (0x00U)      /*  used in Configurator        */
#define DEM_IGNITION_SPARK                      (0x01U)      /*  used in Configurator        */

/*--------------------------------------------------------------------------*/
/* Macros(AUTOSAR Version)                                                  */
/*--------------------------------------------------------------------------*/
/*                  Std_VersionInfoType                                     */
#define DEM_VENDOR_ID                               ((uint16)(0x0053u))
#define DEM_MODULE_ID                               ((uint16)(0x0036u))
#define DEM_AR_RELEASE_MAJOR_VERSION                ((uint8)(0x04u))
#define DEM_AR_RELEASE_MINOR_VERSION                ((uint8)(0x05u))
#define DEM_AR_RELEASE_REVISION_VERSION             ((uint8)(0x00u))


/*--------------------------------------------------------------------------*/
/* Macros(for PostBuild)                                                    */
/*--------------------------------------------------------------------------*/
/*  event attribute : OBD type.                 bit : 0x80      */
#define DEM_PB_EVTATTR_OBD_NONOBD               ((Dem_PB_EventAttributeType)0x00U)
#define DEM_PB_EVTATTR_OBD_OBD                  ((Dem_PB_EventAttributeType)0x80U)

/*  event attribute : event available type.     bit : 0x01      */
#define DEM_PB_EVTATTR_AVAILABLE_DISABLE        ((Dem_PB_EventAttributeType)0x00U)
#define DEM_PB_EVTATTR_AVAILABLE_ENABLE         ((Dem_PB_EventAttributeType)0x01U)

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*                  Std_ReturnType                              :   uint8   */
/*                      0x02-0x3F   :   Available to user specific errors   */
#define DEM_E_NO_DTC_AVAILABLE                      (0x0Au)
#define DEM_BUFFER_TOO_SMALL                        (0x15u)
#define DEM_NO_SUCH_ELEMENT                         (0x30u)

#define DEM_E_FAILED_FIM_REPORT                     (0x11u)     /*  extend return value */
#define DEM_E_ACCESS_PROCESSING                     (0x12u)     /*  extend return value */
#define DEM_E_MEMORY_OVERFLOW                       (0x13u)     /*  extend return value */
#define DEM_E_EXTERNAL_MEMORY                       (0x14u)     /*  extend return value */

/*                  Dem_ModeType                                :   uint16  */
#define DEM_MODE_BUSY                               ((Dem_ModeType)0x8000u)
#define DEM_MODE_UPDATE_ALL_MONITORSTATUS           ((Dem_ModeType)0x0100u)
#define DEM_MODE_INITIALIZING                       ((Dem_ModeType)0x0080u)
#define DEM_MODE_INITIALIZED                        ((Dem_ModeType)0x0040u)
#define DEM_MODE_WAIT_SETTING_EVENT                 ((Dem_ModeType)0x0020u)
#define DEM_MODE_SETTING_EVENT                      ((Dem_ModeType)0x0010u)
#define DEM_MODE_PROCESSING_CLEAR_DTC               ((Dem_ModeType)0x0008u)
#define DEM_MODE_SYNCING_NVRAM                      ((Dem_ModeType)0x0004u)

#define DEM_MODE_INITIALIZE_MODE_MASK               ((Dem_ModeType)( DEM_MODE_INITIALIZING | DEM_MODE_INITIALIZED ))
#define DEM_MODE_BUSY_DETAIL                        ((Dem_ModeType)( DEM_MODE_SETTING_EVENT | DEM_MODE_PROCESSING_CLEAR_DTC | DEM_MODE_SYNCING_NVRAM ))

/*                  DTCGroup definitions                        :   uint32  */
#define DEM_DTC_GROUP_ALL_DTCS                      ((Dem_u32_DTCGroupType)0x00FFFFFFu)
#define DEM_DTC_GROUP_EMISSION_REL_DTCS             ((Dem_u32_DTCGroupType)0x00FFFF33u)

/*                  Cancel ClearDTC                             :   uint32  */
#define DEM_DTC_CANCEL_CLEAR_DTC                    ((Dem_u32_DTCGroupType)0xFEFEFEFEu)

/*                  Type of RecordNumber                        :   uint8   */
#define DEM_RECORDNUMBER_NEXT_NONE                  ((uint8)(0xFFu))

/*  index of SimilarConditionArray[]    */
#define DEM_SIMILARTYPE_ENGINERPM                   ((uint8)0u)
#define DEM_SIMILARTYPE_LOADCONDITION               ((uint8)1u)
#define DEM_SIMILARTYPE_WARMUPSTATE                 ((uint8)2u)
#define DEM_SIMILARTYPE_ADDCONDITION_START          ((uint8)3u)

/* typedef uint32       MonitorData Unique Status  definition */
#define DEM_MONITORDATA_SPECIFICEVENTSTATUS         ((Dem_MonitorDataType)0x10000000U)
#define DEM_MONITORDATA_SETEVENTSTATUS              ((Dem_MonitorDataType)0x20000000U)
#define DEM_MONITORDATA_EXTENDEDDATA                ((Dem_MonitorDataType)0x30000000U)

#define DEM_MONITORDATA_TSFFD                       ((Dem_MonitorDataType)0x40000000U)
#define DEM_MONITORDATA_PREFFD                      ((Dem_MonitorDataType)0x50000000U)
#define DEM_MONITORDATA_PID                         ((Dem_MonitorDataType)0x60000000U)
#define DEM_MONITORDATA_SETEVENTFAILED_WITHSYNCFFD  ((Dem_MonitorDataType)0x70000000U)

#define DEM_MONITORDATA_OTHER                       ((Dem_MonitorDataType)0xF0000000U)

#define DEM_MONITORDATA_FUNC_MASK                   ((Dem_MonitorDataType)0xF0000000U)
#define DEM_MONITORDATA_VALUE_MASK                  ((Dem_MonitorDataType)0x00FFFFFFU)
#define DEM_MONITORDATA_VALUETYPE_MASK              ((Dem_MonitorDataType)0x0F000000U)
#define DEM_MONITORDATA_VALUEDATA_MASK              ((Dem_MonitorDataType)0x00FFFFFFU)

#define DEM_MONITORDATA_VALUETYPE_EVENTID           ((Dem_MonitorDataType)0x00000000U)
#define DEM_MONITORDATA_VALUETYPE_MISFIRECYLINDER   ((Dem_MonitorDataType)0x08000000U)


/*  DTR             */
#define DEM_DTR_UASID_SIGNED        ((Dem_u08_DTRUasidType) 0x80U)


/*  Invalid ID Value        */
#define DEM_EVENTID_INVALID                 ((Dem_EventIdType) 0xFFFFU)

/*  Readiness : CallFrom    */
#define DEM_READINESS_CALLBY_DCM            ((Dem_u08_ReadinessKindType)0x00U)
#define DEM_READINESS_CALLBY_SWC            ((Dem_u08_ReadinessKindType)0x80U)


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* DEM_TYPES_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

