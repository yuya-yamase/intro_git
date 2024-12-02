/* NvM_Jobm_Hook.c v1-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/JOBM/HOOK/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_Jobm.h"
#include "../inc/NvM_Jobm_Hook.h"
#include "../inc/NvM_WdtExt.h"

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_Jobm_Hook_NvMTimeoutPeiodic                          */
/* Description   | Service to notify timeout from WdtExt to Jobm.           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Jobm_Hook_TimeoutNotification(
    NvM_WdtExt_WdtIdType Id
){
    NvM_Jobm_DestructiveCancelJobs( NVM_JOBM_DSTRCTV_CXL_TIMEOUT );
    return ;
}

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
