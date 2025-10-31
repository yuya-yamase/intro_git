/* MemAcc_SemCtl.h v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MemAcc SemCtl HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef MEMACC_SEMCTL_H
#define MEMACC_SEMCTL_H


#include "MemAcc.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Lock status (for Lock infomation managemant table) */
#define MEMACC_SEMCTL_ST_UNLOCK     ((uint8)0x00U)        /* Unlock                            */
#define MEMACC_SEMCTL_ST_LOCK       ((uint8)0x01U)        /* Lock                              */
#define MEMACC_SEMCTL_ST_LOCKEVENT  ((uint8)0x02U)        /* Lock (Wait notification)          */
#define MEMACC_SEMCTL_ST_LOCKWAIT   ((uint8)0x03U)        /* Wait lock control                 */

/* Lock execution control status */
#define MEMACC_SEMCTL_JOB_NONE      ((uint8)0x00U)        /* No request                        */
#define MEMACC_SEMCTL_JOB_REQ       ((uint8)0x01U)        /* Has lock request                  */

/* Lock status (public) */
#define MEMACC_SEMCTL_ST_EXT_UNLOCK ((uint8)0x00U)        /* Unlock */
#define MEMACC_SEMCTL_ST_EXT_LOCK   ((uint8)0x01U)        /* Lock   */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

FUNC( void, MEMACC_CODE ) MemAcc_SemCtl_Init( void );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_SemCtl_RequestLock( MemAcc_AddressAreaIdType targetAreaId, MemAcc_AddressType targetAddress, MemAcc_LengthType targetLength, MemAcc_LockNotificationType pt_notificationPtr );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_SemCtl_ReleaseLock( MemAcc_AddressAreaIdType targetAreaId, MemAcc_AddressType targetAddress, MemAcc_LengthType targetLength );
FUNC( uint8, MEMACC_CODE ) MemAcc_SemCtl_CheckAreaLockStatus( MemAcc_AddressAreaIdType targetAreaId );
FUNC( void, MEMACC_CODE ) MemAcc_SemCtl_Execute( void );
FUNC( uint8, MEMACC_CODE ) MemAcc_SemCtl_GetExtLockStatus( void );

#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* MEMACC_SEMCTL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
