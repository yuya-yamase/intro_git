/* NvM_BswM_Connector.c v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/BSWM/CONNECTOR/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "NvM_BswM_Connector.h"

/* [Manual configuration] Add the necessary description for the user below. */
/* #include <BswM_NvM.h> */
/* [Manual configuration] Add the necessary description for the user above. */

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_BswM_CurrentJobMode                                  */
/* Description   | Function for connection with BswM_NvM_CurrentJobMode.    */
/* Preconditions | None                                                     */
/* Parameters    | MultiBlockRequest : Indicates whether the callback       */
/*               |                  refers to multi block services          */
/*               |                  NvM_ReadAll or NvM_WriteAll.            */
/*               | CurrentJobMode : Current state of the multi block job    */
/*               |                  indicated by MultiBlockRequest.         */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
#if ( NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON )
FUNC( void, NVM_CODE )
NvM_BswM_CurrentJobMode(
    NvM_MultiBlockRequestType MultiBlockRequest,
    NvM_RequestResultType CurrentJobMode
){
    /* [Manual configuration] Add the necessary description for the user below. */
    /* BswM_NvM_CurrentJobMode( MultiBlockRequest, CurrentJobMode ); */
    /* [Manual configuration] Add the necessary description for the user above. */

    return;
}
#endif

/****************************************************************************/
/* Function Name | NvM_BswM_CurrentBlockMode                                */
/* Description   | Function for connection with BswM_NvM_CurrentBlockMode.  */
/* Preconditions | None                                                     */
/* Parameters    | Block            : The Block that the new NvM Mode       */
/*               |                    corresponds to.                       */
/*               | CurrentBlockMode : The current block mode of the NvM     */
/*               |                    block.                                */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_BswM_CurrentBlockMode(
    NvM_BlockIdType Block,
    NvM_RequestResultType CurrentBlockMode
){
    /* [Manual configuration] Add the necessary description for the user below. */
    /* BswM_NvM_CurrentBlockMode( Block, CurrentBlockMode ); */
    /* [Manual configuration] Add the necessary description for the user above. */

    return;
}

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2020/12/10                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
