/* MemAcc_JobCtl_Internal.h v2-0-0                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MEMACC/JOBCTL/INTERNAL/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef MEMACC_JOBCTL_INTERNAL_H
#define MEMACC_JOBCTL_INTERNAL_H

#include "MemAcc_JobCtl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

FUNC( void, MEMACC_CODE )
MemAcc_JobCtl_JobRequestTbl_Init(
    MemAcc_AddressAreaIdType targetAreaId
);

FUNC( void, MEMACC_CODE )
MemAcc_JobCtl_JobCtlExtInfoTbl_Init(
    MemAcc_AddressAreaIdType targetAreaId
);

FUNC( uint8, MEMACC_CODE )
MemAcc_JobCtl_ChangePriority(
    uint8 targetJobStatus
);

FUNC( uint8, MEMACC_CODE )
MemAcc_JobCtl_ChkJobSuspend( void );

FUNC( Std_ReturnType, MEMACC_CODE )
MemAcc_JobCtl_ChkCodeFlashArea(
    MemAcc_JobType jobStatus,
    MemAcc_AddressType addressStart,
    MemAcc_LengthType length
);

FUNC( Std_ReturnType, MEMACC_CODE )
MemAcc_JobCtl_ChkDataFlashArea(
    MemAcc_JobType jobStatus,
    MemAcc_AddressType addressStart,
    MemAcc_LengthType length
);

FUNC( Std_ReturnType, MEMACC_CODE )
MemAcc_JobCtl_ChkAddress(
    MemAcc_AddressType addressStart,
    MemAcc_LengthType length,
    MemAcc_AddressType startAddress,
    MemAcc_AddressType endAddress
);

FUNC( Std_ReturnType, MEMACC_CODE )
MemAcc_JobCtl_ChkLength(
    MemAcc_JobType jobStatus,
    MemAcc_AddressType addressStart,
    MemAcc_LengthType length,
    MemAcc_LengthType writeSize,
    MemAcc_LengthType readSize,
    MemAcc_LengthType blankSize,
    MemAcc_LengthType eraseSize
);

FUNC( Std_ReturnType, MEMACC_CODE )
MemAcc_JobCtl_ImmediateAccessPossible(
    MemAcc_AddressAreaIdType addressAreaId
);

#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#endif /* MEMACC_JOBCTL_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
