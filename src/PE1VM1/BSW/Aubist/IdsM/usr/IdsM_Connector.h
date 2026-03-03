/* IdsM_Connector_h_v2-0-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/Usr/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/****************************************************************************/

#ifndef IDSM_CONNECTOR_H
#define IDSM_CONNECTOR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>

#if (IDSM_CFG_USE_IDSR == STD_ON)
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Connector_PduRTransmit
(
    VAR(PduIdType, AUTOMATIC) udPduId,
    P2CONST(PduInfoType, AUTOMATIC, IDSM_VAR_NO_INIT) ptPduInfo
);

FUNC(Std_ReturnType, IDSM_CODE) IdsM_Connector_PduRCancelTransmit
(
    VAR(PduIdType, AUTOMATIC) udPduId
);
#endif  /* IDSM_CFG_USE_IDSR == STD_ON */

#if (IDSM_CFG_USE_DEM == STD_ON)
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Connector_DemTransmit
(
    VAR(Dem_EventIdType, AUTOMATIC) udDemEventId
);
#endif  /* IDSM_CFG_USE_DEM == STD_ON */

#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Connector_StbMGetCurrentTime
(
    P2VAR(StbM_TimeStampType, AUTOMATIC, IDSM_APPL_DATA) ptStbMTimestamp
);
#elif ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_CUSTOM )
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Connector_GetCurrentTime
(
    P2VAR(IdsM_TimestampType, AUTOMATIC, IDSM_APPL_DATA) ptTimestamp
);
#else    /* IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR */
#endif   /* IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR */

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* IDSM_CONNECTOR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2022/11/30                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
