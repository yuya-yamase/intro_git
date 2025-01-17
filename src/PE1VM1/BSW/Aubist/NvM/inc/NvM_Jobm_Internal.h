/* NvM_Jobm_Internal.h v1-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/JOBM/INTERNAL/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_JOBM_INTERNAL_H
#define     NVM_JOBM_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include "NvM_Jobm.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define NVM_JOBM_TIMEOUT_VALUE_WAIT       (5U)
#define NVM_JOBM_TIMEOUT_VALUE_START      (65000U)

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

extern VAR( NvM_BlockIdType, NVM_VAR_NO_INIT )   NvM_Jobm_ExecBlockId;

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Jobm_SubMainfuncJobIdle( void );

FUNC( void, NVM_CODE )
NvM_Jobm_SubMainfuncJobBusyCxl(
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) CurrentJobInfo
);

FUNC( void, NVM_CODE )
NvM_Jobm_SubMainfuncJobBusy(
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) CurrentJobInfo
);

FUNC( boolean, NVM_CODE )
NvM_Jobm_ChkCancelForImmWrite(
    P2CONST( NvM_Jobm_stJobInfomationType, AUTOMATIC, TYPEDEF ) CurrentJobInfo
);

FUNC( NvM_RequestResultType, NVM_CODE )
NvM_Jobm_NvbResultToReqResult(
    uint8 JobResult
);

FUNC( boolean, NVM_CODE )
NvM_Jobm_IsReqBlockExecuting(
    NvM_BlockIdType ReqBlockId
);

#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( void, NVM_CODE )
NvM_Jobm_CancelPreExecWtAll( void );
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_JOBM_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
