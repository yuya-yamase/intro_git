/* Dem_Rc_UdmEventRecordTable_h(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Rc_UdmEventRecordTable/HEADER                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_UDMEVENTRECORDTABLE_H
#define DEM_RC_UDMEVENTRECORDTABLE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../cfg/Dem_Data_Cfg.h"
#include "../cfg/Dem_NvM_Cfg.h"
#include "Dem_Rc_UdmMng_rc.h"

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
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

extern VAR( Dem_u08_RecMngMtxStsType                         ,DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_Occurrence1_EventNvMStatus[ DEM_UDM_RKDEMUDM_OCCURRENCE1_EVENT_RECORD_NUM ];
extern VAR( Dem_u08_RecMngMtxStsType                         ,DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_Occurrence2_EventNvMStatus[ DEM_UDM_RKDEMUDM_OCCURRENCE2_EVENT_RECORD_NUM ];
extern VAR( Dem_u08_RecMngMtxStsType                         ,DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_Occurrence2_NM_EventNvMStatus[ DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_EVENT_RECORD_NUM ];
extern VAR( Dem_u08_RecMngMtxStsType                         ,DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_Occurrence3_NM_EventNvMStatus[ DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_EVENT_RECORD_NUM ];
extern VAR( Dem_u08_RecMngMtxStsType                         ,DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_Occurrence7_NM_EventNvMStatus[ DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_EVENT_RECORD_NUM ];
extern VAR( Dem_u08_RecMngMtxStsType                         ,DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_Maintenance1_EventNvMStatus[ DEM_UDM_RKDEMUDM_MAINTENANCE1_EVENT_RECORD_NUM ];
extern VAR( Dem_u08_RecMngMtxStsType                         ,DEM_VAR_NO_INIT ) Dem_Udm_RkDemUDM_SystemOperation2_EventNvMStatus[ DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_EVENT_RECORD_NUM ];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

extern CONST( AB_83_ConstV Dem_UdmEventRecordAccessType      ,DEM_CONFIG_DATA ) Dem_UdmEventRecordTable[ DEM_USER_DEFINED_MEMORY_NUM ];
extern CONST( AB_83_ConstV Dem_UdmEventNvMStatusType         ,DEM_CONFIG_DATA ) Dem_UdmEventNvMStatus[ DEM_USER_DEFINED_MEMORY_NUM ];

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

#endif /* DEM_RC_UDMEVENTRECORDTABLE_H */

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
