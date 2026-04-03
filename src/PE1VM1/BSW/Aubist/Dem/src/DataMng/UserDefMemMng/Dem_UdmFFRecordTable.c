/* Dem_UdmFFRecordTable_c(v5-5-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmFFRecordTable/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
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
#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR( Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordType                     ,DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_RECORD_NUM ];
VAR( Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordType                     ,DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_RECORD_NUM ];
VAR( Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordType                     ,DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_RECORD_NUM ];
VAR( Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordType                     ,DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_RECORD_NUM ];
VAR( Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordType                     ,DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_RECORD_NUM ];
VAR( Dem_Udm_RkDemUDM_Maintenance1_FreezeFrameRecordType                     ,DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_Maintenance1_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_RECORD_NUM ];
VAR( Dem_Udm_RkDemUDM_SystemOperation2_FreezeFrameRecordType                     ,DEM_VAR_SAVED_ZONE ) Dem_Udm_RkDemUDM_SystemOperation2_FreezeFrameRecordList[ DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_RECORD_NUM ];

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_Occurrence1_FFDNvMStatus[ DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_RECORD_NUM ];
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_Occurrence2_FFDNvMStatus[ DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_RECORD_NUM ];
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_Occurrence2_NM_FFDNvMStatus[ DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_RECORD_NUM ];
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_Occurrence3_NM_FFDNvMStatus[ DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_RECORD_NUM ];
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_Occurrence7_NM_FFDNvMStatus[ DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_RECORD_NUM ];
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_Maintenance1_FFDNvMStatus[ DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_RECORD_NUM ];
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_SystemOperation2_FFDNvMStatus[ DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_RECORD_NUM ];

VAR( Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordType, DEM_VAR_NO_INIT ) Dem_TmpUdm_RkDemUDM_Occurrence1_FFDMirror;
VAR( Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordType, DEM_VAR_NO_INIT ) Dem_TmpUdm_RkDemUDM_Occurrence2_FFDMirror;
VAR( Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordType, DEM_VAR_NO_INIT ) Dem_TmpUdm_RkDemUDM_Occurrence2_NM_FFDMirror;
VAR( Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordType, DEM_VAR_NO_INIT ) Dem_TmpUdm_RkDemUDM_Occurrence3_NM_FFDMirror;
VAR( Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordType, DEM_VAR_NO_INIT ) Dem_TmpUdm_RkDemUDM_Occurrence7_NM_FFDMirror;
VAR( Dem_Udm_RkDemUDM_Maintenance1_FreezeFrameRecordType, DEM_VAR_NO_INIT ) Dem_TmpUdm_RkDemUDM_Maintenance1_FFDMirror;
VAR( Dem_Udm_RkDemUDM_SystemOperation2_FreezeFrameRecordType, DEM_VAR_NO_INIT ) Dem_TmpUdm_RkDemUDM_SystemOperation2_FFDMirror;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

CONST( AB_83_ConstV Dem_UdmFreezeFrameRecordAccessType        ,DEM_CONFIG_DATA ) Dem_UdmFreezeFrameRecordTable[ DEM_USER_DEFINED_MEMORY_NUM ] =
{
    /*  DemFreezeFrameRecordListStartDataPtr DemFFDMaxLength DemFFDStoredFormatSize DemFFDRecordNum  */
    {   &Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[0].Data[0], DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_MAX_LENGTH, DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_STORED_FORMAT_SIZE, DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_RECORD_NUM    },
    {   &Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordList[0].Data[0], DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_MAX_LENGTH, DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_STORED_FORMAT_SIZE, DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_RECORD_NUM    },
    {   &Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[0].Data[0], DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_MAX_LENGTH, DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_STORED_FORMAT_SIZE, DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_RECORD_NUM    },
    {   &Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordList[0].Data[0], DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_MAX_LENGTH, DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_STORED_FORMAT_SIZE, DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_RECORD_NUM    },
    {   &Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[0].Data[0], DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_MAX_LENGTH, DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_STORED_FORMAT_SIZE, DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_RECORD_NUM    },
    {   &Dem_Udm_RkDemUDM_Maintenance1_FreezeFrameRecordList[0].Data[0], DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_MAX_LENGTH, DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_STORED_FORMAT_SIZE, DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_RECORD_NUM    },
    {   &Dem_Udm_RkDemUDM_SystemOperation2_FreezeFrameRecordList[0].Data[0], DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_MAX_LENGTH, DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_STORED_FORMAT_SIZE, DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_RECORD_NUM    }
};

CONST( AB_83_ConstV Dem_UdmFFDNvMStatusType                   ,DEM_CONFIG_DATA ) Dem_UdmFFDNvMStatus[ DEM_USER_DEFINED_MEMORY_NUM ] =
{
    /*  DemUdmFFDNvMStatusPtr DemRecMngCmnKindUdmFFD  */
    {   &Dem_Udm_RkDemUDM_Occurrence1_FFDNvMStatus[0], DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE1_FFD    },
    {   &Dem_Udm_RkDemUDM_Occurrence2_FFDNvMStatus[0], DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE2_FFD    },
    {   &Dem_Udm_RkDemUDM_Occurrence2_NM_FFDNvMStatus[0], DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD    },
    {   &Dem_Udm_RkDemUDM_Occurrence3_NM_FFDNvMStatus[0], DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD    },
    {   &Dem_Udm_RkDemUDM_Occurrence7_NM_FFDNvMStatus[0], DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD    },
    {   &Dem_Udm_RkDemUDM_Maintenance1_FFDNvMStatus[0], DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_MAINTENANCE1_FFD    },
    {   &Dem_Udm_RkDemUDM_SystemOperation2_FFDNvMStatus[0], DEM_RECMNGCMN_KIND_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD    }
};

CONST( AB_83_ConstV Dem_UdmFreezeFrameRecordNvMAccessType     ,DEM_CONFIG_DATA ) Dem_UdmFreezeFrameRecordNvMTable[ DEM_USER_DEFINED_MEMORY_NUM ] =
{
    /*  Dem_TmpUdmFFDMirrorDataPtr DemUdmFFDRecordNvBlockSize  */
    {   &Dem_TmpUdm_RkDemUDM_Occurrence1_FFDMirror.Data[0], DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_RECORD_NVBLOCK_SIZE    },
    {   &Dem_TmpUdm_RkDemUDM_Occurrence2_FFDMirror.Data[0], DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_RECORD_NVBLOCK_SIZE    },
    {   &Dem_TmpUdm_RkDemUDM_Occurrence2_NM_FFDMirror.Data[0], DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_RECORD_NVBLOCK_SIZE    },
    {   &Dem_TmpUdm_RkDemUDM_Occurrence3_NM_FFDMirror.Data[0], DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_RECORD_NVBLOCK_SIZE    },
    {   &Dem_TmpUdm_RkDemUDM_Occurrence7_NM_FFDMirror.Data[0], DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_RECORD_NVBLOCK_SIZE    },
    {   &Dem_TmpUdm_RkDemUDM_Maintenance1_FFDMirror.Data[0], DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_RECORD_NVBLOCK_SIZE    },
    {   &Dem_TmpUdm_RkDemUDM_SystemOperation2_FFDMirror.Data[0], DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_RECORD_NVBLOCK_SIZE    }
};

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
