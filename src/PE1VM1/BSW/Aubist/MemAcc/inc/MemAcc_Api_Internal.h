/* MemAcc_Api_Internal.h v2-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MEMACC/API/INTERNAL/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef MEMACC_API_INTERNAL_H
#define MEMACC_API_INTERNAL_H

#include "MemAcc.h"
#include "MemAcc_JobCtl.h"


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

FUNC( Std_ReturnType, MEMACC_CODE )
MemAcc_Api_RunningExecute( void );

FUNC( void, MEMACC_CODE )
MemAcc_Api_CancelExecute( void );

FUNC( void, MEMACC_CODE )
MemAcc_Api_RequestExecute( void );

FUNC( void, MEMACC_CODE )
MemAcc_Api_JobStart(
    MemAcc_AddressAreaIdType addressAreaId
);

FUNC( void, MEMACC_CODE )
MemAcc_Api_JobEnd(
    MemAcc_AddressAreaIdType addressAreaId,
    MemAcc_JobResultType jobResult
);

FUNC( Std_ReturnType, MEMACC_CODE )
MemAcc_Api_Write(
    uint8 u1_driverType
);

FUNC( Std_ReturnType, MEMACC_CODE )
MemAcc_Api_Read(
    uint8 u1_driverType
);

FUNC( Std_ReturnType, MEMACC_CODE )
MemAcc_Api_Erase(
    uint8 u1_driverType
);

FUNC( Std_ReturnType, MEMACC_CODE )
MemAcc_Api_BlankCheck(
    uint8 u1_driverType
);

FUNC( Std_ReturnType, MEMACC_CODE )
MemAcc_Api_HwSpecificService(
    uint8 u1_driverType
);

#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

/* Job request manage information */
extern VAR ( MemAcc_JobRequestManageType, MEMACC_VAR_NO_INIT )    MemAcc_ApiJobRequest;

#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

#endif /* MEMACC_API_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
