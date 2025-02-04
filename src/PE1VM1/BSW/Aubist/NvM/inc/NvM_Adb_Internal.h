/* NvM_Adb_Internal.h v1-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/ADB/INTERNAL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_ADB_INTERNAL_H
#define     NVM_ADB_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include "../cfg/NvM_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define NVM_ADB_RAM_GARBLED_CHECK_NUM (5U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef struct {
    NvM_RequestResultType AdbReqResult;
#if ( NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON )
    NvM_Adb_RamBlockStatusType RamBlockStatus;
#endif /* NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON */
    NvM_Adb_WriteProtectStatusType WriteProtectStatus;
} NvM_Adb_AdminBlockInfoType;

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

extern VAR( NvM_Adb_AdminBlockInfoType, NVM_VAR_NO_INIT ) NvM_Adb_AdminBlockInfo[NVM_NUM_OF_NVRAMBLOCKS];
extern VAR( NvM_BlockIdType,            NVM_VAR_NO_INIT ) NvM_Adb_CheckTargetBlockId;

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

#endif  /* NVM_ADB_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
