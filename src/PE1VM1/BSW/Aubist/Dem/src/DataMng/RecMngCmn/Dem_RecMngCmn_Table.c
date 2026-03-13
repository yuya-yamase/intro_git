/* Dem_RecMngCmn_Table_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/RecMngCmn_Table/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_Rc_UdmEventRecordTable.h"
#include "../../../inc/Dem_Rc_UdmFaultRecordTable.h"
#include "../../../inc/Dem_Rc_UdmFFRecordTable.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


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

CONST( AB_83_ConstV Dem_RecordInitInfoType         ,DEM_CONFIG_DATA )  Dem_RecordInitFuncTable[DEM_RECMNGCMN_KIND_MAX] =
{
    {  &Dem_ClrInfoMng_Init,     &Dem_ClrInfoMng_InitSavedZone,     &Dem_ClrInfoMng_DataVerify      },
    {  &Dem_FFDMng_Init,         &Dem_FFDMng_InitSavedZone,         &Dem_FFDMng_DataVerify          },
    {  &Dem_FaultMng_Init,       &Dem_FaultMng_InitSavedZone,       &Dem_FaultMng_DataVerify        },
    {  &Dem_EventMng_Init,       &Dem_EventMng_InitSavedZone,       &Dem_EventMng_DataVerify        },
    {  &Dem_UdmFFDMng_Init,      &Dem_UdmFFDMng_InitSavedZone,      &Dem_UdmFFDMng_DataVerify       },
    {  &Dem_UdmFFDMng_Init,      &Dem_UdmFFDMng_InitSavedZone,      &Dem_UdmFFDMng_DataVerify       },
    {  &Dem_UdmFFDMng_Init,      &Dem_UdmFFDMng_InitSavedZone,      &Dem_UdmFFDMng_DataVerify       },
    {  &Dem_UdmFFDMng_Init,      &Dem_UdmFFDMng_InitSavedZone,      &Dem_UdmFFDMng_DataVerify       },
    {  &Dem_UdmFFDMng_Init,      &Dem_UdmFFDMng_InitSavedZone,      &Dem_UdmFFDMng_DataVerify       },
    {  &Dem_UdmFFDMng_Init,      &Dem_UdmFFDMng_InitSavedZone,      &Dem_UdmFFDMng_DataVerify       },
    {  &Dem_UdmFFDMng_Init,      &Dem_UdmFFDMng_InitSavedZone,      &Dem_UdmFFDMng_DataVerify       },
    {  &Dem_UdmFaultMng_Init,    &Dem_UdmFaultMng_InitSavedZone,    &Dem_UdmFaultMng_DataVerify     },
    {  &Dem_UdmFaultMng_Init,    &Dem_UdmFaultMng_InitSavedZone,    &Dem_UdmFaultMng_DataVerify     },
    {  &Dem_UdmFaultMng_Init,    &Dem_UdmFaultMng_InitSavedZone,    &Dem_UdmFaultMng_DataVerify     },
    {  &Dem_UdmFaultMng_Init,    &Dem_UdmFaultMng_InitSavedZone,    &Dem_UdmFaultMng_DataVerify     },
    {  &Dem_UdmFaultMng_Init,    &Dem_UdmFaultMng_InitSavedZone,    &Dem_UdmFaultMng_DataVerify     },
    {  &Dem_UdmFaultMng_Init,    &Dem_UdmFaultMng_InitSavedZone,    &Dem_UdmFaultMng_DataVerify     },
    {  &Dem_UdmFaultMng_Init,    &Dem_UdmFaultMng_InitSavedZone,    &Dem_UdmFaultMng_DataVerify     },
    {  &Dem_UdmEventMng_Init,    &Dem_UdmEventMng_InitSavedZone,    &Dem_UdmEventMng_DataVerify     },
    {  &Dem_UdmEventMng_Init,    &Dem_UdmEventMng_InitSavedZone,    &Dem_UdmEventMng_DataVerify     },
    {  &Dem_UdmEventMng_Init,    &Dem_UdmEventMng_InitSavedZone,    &Dem_UdmEventMng_DataVerify     },
    {  &Dem_UdmEventMng_Init,    &Dem_UdmEventMng_InitSavedZone,    &Dem_UdmEventMng_DataVerify     },
    {  &Dem_UdmEventMng_Init,    &Dem_UdmEventMng_InitSavedZone,    &Dem_UdmEventMng_DataVerify     },
    {  &Dem_UdmEventMng_Init,    &Dem_UdmEventMng_InitSavedZone,    &Dem_UdmEventMng_DataVerify     },
    {  &Dem_UdmEventMng_Init,    &Dem_UdmEventMng_InitSavedZone,    &Dem_UdmEventMng_DataVerify     }
};

/* Data type processing function table */
CONST( AB_83_ConstV Dem_NvMWriteInfoType           ,DEM_CONFIG_DATA )  Dem_NvMWriteInfo[DEM_RECMNGCMN_KIND_MAX] =
{
    {    &Dem_ClrInfoMng_SetRecordMirror,           &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_ClrInfoNvMStatus,       1U,                          DEM_CLRINFO_RECORD_NVBLOCK_SIZE,  1U,                                  DEM_MM_NVM_REC_KIND_CLRINFO     },
    {    &Dem_FFDMng_SetRecordMirror,               &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_FFDNvMStatus[0],        DEM_FFD_RECORD_LIST_NUM,     DEM_FFD_RECORD_NVBLOCK_SIZE,      DEM_FREEZE_FRAME_DATA_BLOCK_NUM,     DEM_MM_NVM_REC_KIND_FFD         },
    {    &Dem_FaultMng_SetRecordMirror,             &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_FaultNvMStatus[0],      DEM_FAIL_RECORD_LIST_NUM,    DEM_FAIL_RECORD_NVBLOCK_SIZE,     1U,                                  DEM_MM_NVM_REC_KIND_FLT         },
    {    &Dem_EventMng_SetRecordMirror,             &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_EventNvMStatus[0],      DEM_EVENT_RECORD_LIST_NUM,   DEM_EVENT_RECORD_NVBLOCK_SIZE,    1U,                                  DEM_MM_NVM_REC_KIND_EVT         },
    {    &Dem_UdmFFDMng_SetRecordMirror,            &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence1_FFDNvMStatus[0],   DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_RECORD_NUM,  DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_RECORD_NVBLOCK_SIZE,   DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_BLOCK_NUM,        DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE1_FFD    },
    {    &Dem_UdmFFDMng_SetRecordMirror,            &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence2_FFDNvMStatus[0],   DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_RECORD_NUM,  DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_RECORD_NVBLOCK_SIZE,   DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_BLOCK_NUM,        DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE2_FFD    },
    {    &Dem_UdmFFDMng_SetRecordMirror,            &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence2_NM_FFDNvMStatus[0],   DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_RECORD_NUM,  DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_RECORD_NVBLOCK_SIZE,   DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_BLOCK_NUM,        DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD    },
    {    &Dem_UdmFFDMng_SetRecordMirror,            &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence3_NM_FFDNvMStatus[0],   DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_RECORD_NUM,  DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_RECORD_NVBLOCK_SIZE,   DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_BLOCK_NUM,        DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD    },
    {    &Dem_UdmFFDMng_SetRecordMirror,            &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence7_NM_FFDNvMStatus[0],   DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_RECORD_NUM,  DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_RECORD_NVBLOCK_SIZE,   DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_BLOCK_NUM,        DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD    },
    {    &Dem_UdmFFDMng_SetRecordMirror,            &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Maintenance1_FFDNvMStatus[0],   DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_RECORD_NUM,  DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_RECORD_NVBLOCK_SIZE,   DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_BLOCK_NUM,        DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_MAINTENANCE1_FFD    },
    {    &Dem_UdmFFDMng_SetRecordMirror,            &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_SystemOperation2_FFDNvMStatus[0],   DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_RECORD_NUM,  DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_RECORD_NVBLOCK_SIZE,   DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_BLOCK_NUM,        DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD    },
    {    &Dem_UdmFaultMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence1_FaultNvMStatus[0], DEM_UDM_RKDEMUDM_OCCURRENCE1_FAULT_RECORD_NUM, DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE1_FLT    },
    {    &Dem_UdmFaultMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence2_FaultNvMStatus[0], DEM_UDM_RKDEMUDM_OCCURRENCE2_FAULT_RECORD_NUM, DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE2_FLT    },
    {    &Dem_UdmFaultMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence2_NM_FaultNvMStatus[0], DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FAULT_RECORD_NUM, DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE2_NM_FLT    },
    {    &Dem_UdmFaultMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence3_NM_FaultNvMStatus[0], DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FAULT_RECORD_NUM, DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE3_NM_FLT    },
    {    &Dem_UdmFaultMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence7_NM_FaultNvMStatus[0], DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FAULT_RECORD_NUM, DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE7_NM_FLT    },
    {    &Dem_UdmFaultMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Maintenance1_FaultNvMStatus[0], DEM_UDM_RKDEMUDM_MAINTENANCE1_FAULT_RECORD_NUM, DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_MAINTENANCE1_FLT    },
    {    &Dem_UdmFaultMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_SystemOperation2_FaultNvMStatus[0], DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FAULT_RECORD_NUM, DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_SYSTEMOPERATION2_FLT    },
    {    &Dem_UdmEventMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence1_EventNvMStatus[0], DEM_UDM_RKDEMUDM_OCCURRENCE1_EVENT_RECORD_NUM, DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE1_EVT    },
    {    &Dem_UdmEventMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence2_EventNvMStatus[0], DEM_UDM_RKDEMUDM_OCCURRENCE2_EVENT_RECORD_NUM, DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE2_EVT    },
    {    &Dem_UdmEventMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence2_NM_EventNvMStatus[0], DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_EVENT_RECORD_NUM, DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE2_NM_EVT    },
    {    &Dem_UdmEventMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence3_NM_EventNvMStatus[0], DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_EVENT_RECORD_NUM, DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE3_NM_EVT    },
    {    &Dem_UdmEventMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Occurrence7_NM_EventNvMStatus[0], DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_EVENT_RECORD_NUM, DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_OCCURRENCE7_NM_EVT    },
    {    &Dem_UdmEventMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_Maintenance1_EventNvMStatus[0], DEM_UDM_RKDEMUDM_MAINTENANCE1_EVENT_RECORD_NUM, DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_MAINTENANCE1_EVT    },
    {    &Dem_UdmEventMng_SetRecordMirror,          &Dem_RecMngCmn_ExclusiveDummy,       &Dem_RecMngCmn_ExclusiveDummy,      &Dem_Udm_RkDemUDM_SystemOperation2_EventNvMStatus[0], DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_EVENT_RECORD_NUM, DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,  1U,                             DEM_MM_NVM_REC_KIND_UDM_RKDEMUDM_SYSTEMOPERATION2_EVT    }
};

CONST( AB_83_ConstV Dem_u16_RecordFieldIndexType   ,DEM_CONFIG_DATA )  Dem_RecordFieldIndexTableForMemSyncFunc[ DEM_RECMNGCMN_KIND_MAX ] =
{
    DEM_RECORD_ONE_FIELD,
    DEM_RECORD_ONE_FIELD,
    DEM_RECORD_ONE_FIELD,
    DEM_RECORD_ONE_FIELD,
    DEM_UDM_RKDEMUDM_OCCURRENCE1_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE2_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_MAINTENANCE1_KIND_INDEX,
    DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE1_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE2_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_MAINTENANCE1_KIND_INDEX,
    DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE1_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE2_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_MAINTENANCE1_KIND_INDEX,
    DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_KIND_INDEX
};

CONST( AB_83_ConstV Dem_u16_RecordFieldIndexType   ,DEM_CONFIG_DATA )  Dem_RecordFieldIndexTableForUdmClrNotVerifiedRecordFunc[ DEM_UDMRECMNGCMN_CLRRECKIND_NUM ] =
{
    DEM_UDM_RKDEMUDM_OCCURRENCE1_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE2_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_MAINTENANCE1_KIND_INDEX,
    DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE1_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE2_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_MAINTENANCE1_KIND_INDEX,
    DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE1_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE2_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_KIND_INDEX,
    DEM_UDM_RKDEMUDM_MAINTENANCE1_KIND_INDEX,
    DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_KIND_INDEX
};

CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindClrInfo = DEM_RECMNGCMN_KIND_CLRINFO;
CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindFFD     = DEM_RECMNGCMN_KIND_FFD;
CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindFault   = DEM_RECMNGCMN_KIND_FAULT;
CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindEvent   = DEM_RECMNGCMN_KIND_EVENT;

CONST( AB_83_ConstV Dem_u16_RecordKindIndexType    ,DEM_CONFIG_DATA )  Dem_RecMngCmnKindMax     = DEM_RECMNGCMN_KIND_MAX;

CONST( AB_83_ConstV DemClrNotVerifiedRecordFuncPtr    ,DEM_CONFIG_DATA ) Dem_ClrNotVerifiedRecordFuncTable[ DEM_RECMNGCMN_CLRRECKIND_NUM ] =
{
    &Dem_FFDMng_ClearAllNotVerifiedRecord,
    &Dem_FaultMng_ClearAllNotVerifiedRecord,
    &Dem_EventMng_ClearAllNotVerifiedRecord
};

CONST( AB_83_ConstV DemUdmClrNotVerifiedRecordFuncPtr ,DEM_CONFIG_DATA ) Dem_UdmClrNotVerifiedRecordFuncTable[ DEM_UDMRECMNGCMN_CLRRECKIND_NUM ] =
{
    &Dem_UdmFFDMng_ClearAllNotVerifiedRecord,
    &Dem_UdmFFDMng_ClearAllNotVerifiedRecord,
    &Dem_UdmFFDMng_ClearAllNotVerifiedRecord,
    &Dem_UdmFFDMng_ClearAllNotVerifiedRecord,
    &Dem_UdmFFDMng_ClearAllNotVerifiedRecord,
    &Dem_UdmFFDMng_ClearAllNotVerifiedRecord,
    &Dem_UdmFFDMng_ClearAllNotVerifiedRecord,
    &Dem_UdmFaultMng_ClearAllNotVerifiedRecord,
    &Dem_UdmFaultMng_ClearAllNotVerifiedRecord,
    &Dem_UdmFaultMng_ClearAllNotVerifiedRecord,
    &Dem_UdmFaultMng_ClearAllNotVerifiedRecord,
    &Dem_UdmFaultMng_ClearAllNotVerifiedRecord,
    &Dem_UdmFaultMng_ClearAllNotVerifiedRecord,
    &Dem_UdmFaultMng_ClearAllNotVerifiedRecord,
    &Dem_UdmEventMng_ClearAllNotVerifiedRecord,
    &Dem_UdmEventMng_ClearAllNotVerifiedRecord,
    &Dem_UdmEventMng_ClearAllNotVerifiedRecord,
    &Dem_UdmEventMng_ClearAllNotVerifiedRecord,
    &Dem_UdmEventMng_ClearAllNotVerifiedRecord,
    &Dem_UdmEventMng_ClearAllNotVerifiedRecord,
    &Dem_UdmEventMng_ClearAllNotVerifiedRecord
};

CONST( AB_83_ConstV Dem_u16_RecordKindIndexType       ,DEM_CONFIG_DATA ) Dem_RecMngCmnClrRecKindNum    = DEM_RECMNGCMN_CLRRECKIND_NUM;
CONST( AB_83_ConstV Dem_u16_RecordKindIndexType       ,DEM_CONFIG_DATA ) Dem_UdmRecMngCmnClrRecKindNum = DEM_UDMRECMNGCMN_CLRRECKIND_NUM;

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>


#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#ifndef JGXSTACK
#else /* JGXSTACK */
/****************************************************************************/
/* Function Name | Dem_RecMngCmnInitFnc_ForStack                            */
/* Description   | DemRecMngCmnInitFncForStack for measuring stack size.    */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordFieldIndex :                                 */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmnInitFnc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
)
{
    Dem_ClrInfoMng_Init( RecordFieldIndex );
    Dem_FFDMng_Init( RecordFieldIndex );
    Dem_FaultMng_Init( RecordFieldIndex );
    Dem_EventMng_Init( RecordFieldIndex );
    Dem_UdmFFDMng_Init( RecordFieldIndex );
    Dem_UdmFFDMng_Init( RecordFieldIndex );
    Dem_UdmFFDMng_Init( RecordFieldIndex );
    Dem_UdmFFDMng_Init( RecordFieldIndex );
    Dem_UdmFFDMng_Init( RecordFieldIndex );
    Dem_UdmFFDMng_Init( RecordFieldIndex );
    Dem_UdmFFDMng_Init( RecordFieldIndex );
    Dem_UdmFaultMng_Init( RecordFieldIndex );
    Dem_UdmFaultMng_Init( RecordFieldIndex );
    Dem_UdmFaultMng_Init( RecordFieldIndex );
    Dem_UdmFaultMng_Init( RecordFieldIndex );
    Dem_UdmFaultMng_Init( RecordFieldIndex );
    Dem_UdmFaultMng_Init( RecordFieldIndex );
    Dem_UdmFaultMng_Init( RecordFieldIndex );
    Dem_UdmEventMng_Init( RecordFieldIndex );
    Dem_UdmEventMng_Init( RecordFieldIndex );
    Dem_UdmEventMng_Init( RecordFieldIndex );
    Dem_UdmEventMng_Init( RecordFieldIndex );
    Dem_UdmEventMng_Init( RecordFieldIndex );
    Dem_UdmEventMng_Init( RecordFieldIndex );
    Dem_UdmEventMng_Init( RecordFieldIndex );

    return;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmnInitSavedZoneFnc_ForStack                   */
/* Description   | -                                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex                                    */
/*               | [in] InitType                                            */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmnInitSavedZoneFnc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( uint8, AUTOMATIC ) InitType
)
{
    Dem_ClrInfoMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_FFDMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_FaultMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_EventMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFFDMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFFDMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFFDMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFFDMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFFDMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFFDMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFFDMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFaultMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFaultMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFaultMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFaultMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFaultMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFaultMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmFaultMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmEventMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmEventMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmEventMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmEventMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmEventMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmEventMng_InitSavedZone( RecordFieldIndex, InitType );
    Dem_UdmEventMng_InitSavedZone( RecordFieldIndex, InitType );

    return;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmnDataVerifyFnc_ForStack                      */
/* Description   | DemRecMngCmnDataVerifyFncForStack for measuring stack    */
/*               | size.                                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex                                    */
/* Return Value  | DEM_IRT_OK                                               */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_RecMngCmnDataVerifyFnc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_ClrInfoMng_DataVerify( RecordFieldIndex );
    retVal = Dem_FFDMng_DataVerify( RecordFieldIndex );
    retVal = Dem_FaultMng_DataVerify( RecordFieldIndex );
    retVal = Dem_EventMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFFDMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFFDMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFFDMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFFDMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFFDMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFFDMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFFDMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFaultMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFaultMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFaultMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFaultMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFaultMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFaultMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmFaultMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmEventMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmEventMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmEventMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmEventMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmEventMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmEventMng_DataVerify( RecordFieldIndex );
    retVal = Dem_UdmEventMng_DataVerify( RecordFieldIndex );

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmnSetMirrorDataFnc_ForStack                   */
/* Description   | DemRecMngCmnSetMirrorDataFnc for measuring stack size.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmnSetMirrorDataFnc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    Dem_ClrInfoMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_FFDMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_FaultMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_EventMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFFDMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFFDMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFFDMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFFDMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFFDMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFFDMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFFDMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFaultMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFaultMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFaultMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFaultMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFaultMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFaultMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmFaultMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmEventMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmEventMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmEventMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmEventMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmEventMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmEventMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );
    Dem_UdmEventMng_SetRecordMirror( RecordFieldIndex, BlockMirrorPtr );

    return;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmnExcEnterFnc_ForStack                        */
/* Description   | DemRecMngCmnExcEnterFnc for measuring stack size.        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmnExcEnterFnc_ForStack
(
    void
)
{
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();

    return;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmnExcExitFnc_ForStack                         */
/* Description   | DemRecMngCmnExcExitFnc for measuring stack size.         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmnExcExitFnc_ForStack
(
    void
)
{
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();
    Dem_RecMngCmn_ExclusiveDummy();

    return;
}

/****************************************************************************/
/* Function Name | Dem_RecMngClrNotVerifiedRecordFunc_ForStack              */
/* Description   | -                                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] ClearRecordIndexPtr                                 */
/*               | [out] RestOfProcessableNumPtr                            */
/* Return Value  | DEM_IRT_OK                                               */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_RecMngClrNotVerifiedRecordFunc_ForStack
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_FFDMng_ClearAllNotVerifiedRecord( ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_FaultMng_ClearAllNotVerifiedRecord( ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_EventMng_ClearAllNotVerifiedRecord( ClearRecordIndexPtr, RestOfProcessableNumPtr );

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmRecMngClrNotVerifiedRecordFunc_ForStack           */
/* Description   | -                                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex                                    */
/*               | [in] ClearRecordIndexPtr                                 */
/*               | [out] RestOfProcessableNumPtr                            */
/* Return Value  | DEM_IRT_OK                                               */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmRecMngClrNotVerifiedRecordFunc_ForStack
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = Dem_UdmFFDMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmFFDMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmFFDMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmFFDMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmFFDMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmFFDMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmFFDMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmFaultMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmFaultMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmFaultMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmFaultMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmFaultMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmFaultMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmFaultMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmEventMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmEventMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmEventMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmEventMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmEventMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmEventMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );
    retVal = Dem_UdmEventMng_ClearAllNotVerifiedRecord( RecordFieldIndex, ClearRecordIndexPtr, RestOfProcessableNumPtr );

    return retVal;
}
#endif /* JGXSTACK */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
