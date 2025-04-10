/* NvM_Dem_Connector.h v1-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/DEM/CONNECTOR/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_DEM_CONNECTOR_H
#define     NVM_DEM_CONNECTOR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>

/* [Manual configuration] Add the necessary description for the user below. */
#include <Dem.h>
#define DemConf_DemEventParameter_NVM_E_INTEGRITY_FAILED    ( 0x0000U )
#define DemConf_DemEventParameter_NVM_E_REQ_FAILED          ( 0x0001U )
#define DemConf_DemEventParameter_NVM_E_WRONG_BLOCK_ID      ( 0x0002U )
#define DemConf_DemEventParameter_NVM_E_VERIFY_FAILED       ( 0x0003U )
#define DemConf_DemEventParameter_NVM_E_LOSS_OF_REDUNDANCY  ( 0x0004U )
#define DemConf_DemEventParameter_NVM_E_HARDWARE            ( 0xFFFFU )
/* [Manual configuration] Add the necessary description for the user above. */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* [Manual configuration] Add the necessary description for the user below. */
#define NVM_DEM_EVENT_STATUS_PASSED     ( DEM_EVENT_STATUS_PASSED )
#define NVM_DEM_EVENT_STATUS_FAILED     ( DEM_EVENT_STATUS_FAILED )
/* [Manual configuration] Add the necessary description for the user above. */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/* [Manual configuration] Add the necessary description for the user below. */
typedef Dem_EventIdType      NvM_Dem_EventIdType;
typedef Dem_EventStatusType  NvM_Dem_EventStatusType;
/* [Manual configuration] Add the necessary description for the user above. */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Dem_ReportErrorStatus(
    NvM_Dem_EventIdType EventId,
    NvM_Dem_EventStatusType EventStatus
);

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_DEM_CONNECTOR_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
