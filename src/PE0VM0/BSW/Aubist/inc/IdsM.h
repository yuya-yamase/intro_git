/* IdsM_h_v2-0-1                                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/HEADER                                                */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef IDSM_H
#define IDSM_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <IdsM_Types.h>
#include <IdsM_Filters_Types.h>
#include <IdsM_Cfg_Type.h>
#include "../IdsM/cfg/IdsM_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define IDSM_VENDOR_ID                       (0x0053U)
#define IDSM_MODULE_ID                       (108U)
#define IDSM_SW_MAJOR_VERSION                (1U)
#define IDSM_SW_MINOR_VERSION                (0U)
#define IDSM_SW_PATCH_VERSION                (0U)
#define IDSM_AR_RELEASE_MAJOR_VERSION        (4U)
#define IDSM_AR_RELEASE_MINOR_VERSION        (6U)
#define IDSM_AR_RELEASE_REVISION_VERSION     (0U)

#define IDSM_AB_E_NONE                       ((IdsM_Ab_ErrorStatusType)0x00U)
#define IDSM_AB_E_NOT_INITIALIZED            ((IdsM_Ab_ErrorStatusType)0x01U)
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
#define IDSM_AB_E_RAM_CHECK_FAIL             ((IdsM_Ab_ErrorStatusType)0x02U)
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
#define IDSM_AB_E_PARAM_INVALID              ((IdsM_Ab_ErrorStatusType)0x11U)
#define IDSM_AB_E_PARAM_POINTER              ((IdsM_Ab_ErrorStatusType)0x12U)
#define IDSM_AB_E_PARAM_LENGTH               ((IdsM_Ab_ErrorStatusType)0x13U)
#define IDSM_AB_E_QSEVBUFF_FULL              ((IdsM_Ab_ErrorStatusType)0x21U)
#if (IDSM_CFG_USE_IDSR == STD_ON)
#define IDSM_AB_E_PDUR_TX_REQUEST_ERROR      ((IdsM_Ab_ErrorStatusType)0x31U)
#define IDSM_AB_E_PDUR_TX_REQUEST_BUSY       ((IdsM_Ab_ErrorStatusType)0x32U)
#define IDSM_AB_E_PDUR_TX_CONFIRMATION_ERROR ((IdsM_Ab_ErrorStatusType)0x33U)
#define IDSM_AB_E_PDUR_TX_TIMEOUT            ((IdsM_Ab_ErrorStatusType)0x34U)
#endif  /* ( IDSM_CFG_USE_IDSR == STD_ON ) */
#if (IDSM_CFG_USE_DEM == STD_ON)
#define IDSM_AB_E_DEM_REQUEST_ERROR          ((IdsM_Ab_ErrorStatusType)0x41U)
#define IDSM_AB_E_DEM_ACCESS_PROCESSING      ((IdsM_Ab_ErrorStatusType)0x42U)
#define IDSM_AB_E_DEM_MEMORY_OVERFLOW        ((IdsM_Ab_ErrorStatusType)0x43U)
#define IDSM_AB_E_DEM_BUFFSIZE_ERROR         ((IdsM_Ab_ErrorStatusType)0x44U)
#define IDSM_AB_E_DEM_POINTER_ERROR          ((IdsM_Ab_ErrorStatusType)0x45U)
#endif  /* ( IDSM_CFG_USE_DEM == STD_ON ) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8 IdsM_ConfigType;
typedef uint8 IdsM_Ab_ErrorStatusType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>

FUNC(void, IDSM_CODE) IdsM_Init
(
    P2CONST(IdsM_ConfigType, AUTOMATIC, IDSM_APPL_CONST) configPtr
);

FUNC(void, IDSM_CODE) IdsM_Ab_DeInit
(
    void
);

FUNC(void, IDSM_CODE) IdsM_GetVersionInfo 
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, IDSM_APPL_DATA) versionInfo
);

FUNC(void, IDSM_CODE) IdsM_SetSecurityEventWithTimestampCountContextData
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) securityEventId,
    VAR(IdsM_TimestampType, AUTOMATIC) timestamp,
    VAR(uint16, AUTOMATIC) count,
    P2CONST(uint8, AUTOMATIC, IDSM_APPL_CONST) contextData,
    VAR(uint16, AUTOMATIC) contextDataSize
);

FUNC(void, IDSM_CODE) IdsM_SetSecurityEventWithTimestampCount
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) securityEventId,
    VAR(IdsM_TimestampType, AUTOMATIC) timestamp,
    VAR(uint16, AUTOMATIC) count
);

FUNC(void, IDSM_CODE) IdsM_SetSecurityEvent
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) securityEventId
);

FUNC(void, IDSM_CODE) IdsM_SetSecurityEventWithContextData
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) securityEventId,
    P2CONST(uint8, AUTOMATIC, IDSM_APPL_CONST) contextData,
    VAR(uint16, AUTOMATIC) contextDataSize
);

FUNC(void, IDSM_CODE) IdsM_SetSecurityEventWithCount
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) securityEventId,
    VAR(uint16, AUTOMATIC) count
);

FUNC(void, IDSM_CODE) IdsM_SetSecurityEventWithCountContextData
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) securityEventId,
    VAR(uint16, AUTOMATIC) count,
    P2CONST(uint8, AUTOMATIC, IDSM_APPL_CONST) contextData,
    VAR(uint16, AUTOMATIC) contextDataSize
);

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* IDSM_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2022/11/30                                                  */
/*  v2-0-1     :2023/02/24                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
