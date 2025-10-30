/* MemAcc_SemCtl_Internal.h v2-0-0                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MEMACC/SEMCTL/INTERNAL/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef MEMACC_SEMCTL_INTERNAL_H
#define MEMACC_SEMCTL_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

FUNC( void, MEMACC_CODE )
MemAcc_SemCtl_CtlTbl_Init(
    uint16 targetAreaId
);

#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                    */
/*--------------------------------------------------------------------------*/
#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

/* Lock execution status management information */
extern VAR( uint8, MEMACC_VAR_NO_INIT ) MemAcc_Sem_CtlStatus;                                           /* Lock execution control status */

/* Fee lock status (for providing external modules) */
extern VAR( uint8, MEMACC_VAR_NO_INIT ) MemAcc_Sem_ExtFeeLockStatus;                                    /* Fee lock status */

#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

#endif /* MEMACC_SEMCTL_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
