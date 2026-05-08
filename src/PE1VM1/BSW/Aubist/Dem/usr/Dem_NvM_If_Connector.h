/* Dem_NvM_If_Connector_h(v5-3-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/NvM_If_Connector/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_NVM_IF_CONNECTOR_H
#define DEM_NVM_IF_CONNECTOR_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_NvM_Connector.h"
#include "../cfg/Dem_MM_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )

/* Dem_NvM_If */
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_If_GetReadAllStatus
(
    P2VAR( Dem_NvM_RequestResultType, AUTOMATIC, AUTOMATIC ) RequestResultPtr
);

FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_If_GetWriteBlockStatus
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( Dem_NvM_RequestResultType, AUTOMATIC, AUTOMATIC ) RequestResultPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_If_GetReadBlockStatus
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( Dem_NvM_RequestResultType, AUTOMATIC, AUTOMATIC ) RequestResultPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_If_WriteSingleBlock
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( void, AUTOMATIC, DEM_VAR_NO_INIT ) NvM_SrcPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_NvM_If_CancelWriteJob
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId
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


#endif /* DEM_NVM_IF_CONNECTOR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

