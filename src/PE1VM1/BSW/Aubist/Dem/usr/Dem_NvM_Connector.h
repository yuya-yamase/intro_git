/* Dem_NvM_Connector_h(v5-0-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/NvM_Connector/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_NVM_CONNECTOR_H
#define DEM_NVM_CONNECTOR_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_MM_Cfg.h"
#include <NvM.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_NVM_REQ_OK                   NVM_REQ_OK
#define DEM_NVM_REQ_NOT_OK               NVM_REQ_NOT_OK
#define DEM_NVM_REQ_PENDING              NVM_REQ_PENDING
#define DEM_NVM_REQ_INTEGRITY_FAILED     NVM_REQ_INTEGRITY_FAILED
#define DEM_NVM_REQ_BLOCK_SKIPPED        NVM_REQ_BLOCK_SKIPPED
#define DEM_NVM_REQ_NV_INVALIDATED       NVM_REQ_NV_INVALIDATED
#define DEM_NVM_REQ_CANCELED             NVM_REQ_CANCELED
#define DEM_NVM_REQ_RESTORED_FROM_ROM    NVM_REQ_RESTORED_FROM_ROM

#define DEM_NVM_MULTI_REQ_BLOCK_ID        ((uint16)0x0000U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef NvM_BlockIdType          Dem_NvM_BlockIdType;
typedef NvM_RequestResultType    Dem_NvM_RequestResultType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )

/* Dem_NvM_Connector */
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_GetErrorStatus
(
    VAR( Dem_NvM_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( Dem_NvM_RequestResultType, AUTOMATIC, AUTOMATIC ) RequestResultPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_WriteBlock
(
    VAR( Dem_NvM_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( void, AUTOMATIC, DEM_VAR_NO_INIT ) NvM_SrcPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_CancelJobs
(
    VAR( Dem_NvM_BlockIdType, AUTOMATIC ) BlockId
);

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>


#endif /* DEM_NVM_CONNECTOR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

