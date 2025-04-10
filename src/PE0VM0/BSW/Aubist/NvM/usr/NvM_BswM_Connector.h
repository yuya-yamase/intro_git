/* NvM_BswM_Connector.h v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/BSWM/CONNECTOR/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_BSWM_CONNECTOR_H
#define     NVM_BSWM_CONNECTOR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

#if ( NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON )
FUNC( void, NVM_CODE )
NvM_BswM_CurrentJobMode(
    NvM_MultiBlockRequestType MultiBlockRequest,
    NvM_RequestResultType CurrentJobMode
);
#endif

FUNC( void, NVM_CODE )
NvM_BswM_CurrentBlockMode(
    NvM_BlockIdType Block,
    NvM_RequestResultType CurrentBlockMode
);

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_BSWM_CONNECTOR_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2021/01/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
