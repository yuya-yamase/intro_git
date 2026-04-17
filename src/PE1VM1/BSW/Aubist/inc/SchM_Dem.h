/* SchM_Dem_h_v2-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | SchM_Dem/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef SCHM_DEM_H
#define SCHM_DEM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Std_Types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*----------------------------------*/
/* Entry Point Prototype            */
/*----------------------------------*/

#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC(void, DEM_CODE) Dem_MainFunction(void);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*----------------------------------*/
/* Bsw ExclusiveArea Api Prototype  */
/*----------------------------------*/

#define SCHM_START_SEC_CODE_CALLOUT
#include <SchM_MemMap.h>

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_EventQueueBufferAccess(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_EventQueueBufferAccess(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_EventMemory(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_EventMemory(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_CheckClearDTCStatus(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_CheckClearDTCStatus(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_ModeAccess(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_ModeAccess(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_CheckControlDTCSetting(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_CheckControlDTCSetting(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_WIRStatusAccess(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_WIRStatusAccess(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_NvMRecordAccess(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_NvMRecordAccess(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_Udm_RkDemUDM_Occurrence1_EventMemory(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_Udm_RkDemUDM_Occurrence1_EventMemory(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_Udm_RkDemUDM_Occurrence2_EventMemory(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_Udm_RkDemUDM_Occurrence2_EventMemory(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_Udm_RkDemUDM_Occurrence2_NM_EventMemory(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_Udm_RkDemUDM_Occurrence2_NM_EventMemory(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_Udm_RkDemUDM_Occurrence3_NM_EventMemory(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_Udm_RkDemUDM_Occurrence3_NM_EventMemory(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_Udm_RkDemUDM_Occurrence7_NM_EventMemory(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_Udm_RkDemUDM_Occurrence7_NM_EventMemory(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_Udm_RkDemUDM_Maintenance1_EventMemory(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_Udm_RkDemUDM_Maintenance1_EventMemory(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_Udm_RkDemUDM_SystemOperation2_EventMemory(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_Udm_RkDemUDM_SystemOperation2_EventMemory(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_SyncEventMemoryAccess(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_SyncEventMemoryAccess(void);

FUNC(void, SCHM_CODE_CALLOUT) SchM_Enter_Dem_UdmGetEventMemory(void);
FUNC(void, SCHM_CODE_CALLOUT) SchM_Exit_Dem_UdmGetEventMemory(void);
#define SCHM_STOP_SEC_CODE_CALLOUT
#include <SchM_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* SCHM_DEM_H */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
