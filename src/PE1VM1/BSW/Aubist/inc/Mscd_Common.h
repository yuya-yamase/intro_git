/* Mscd_Common.h v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/COMMON/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MSCD_COMMON_H
#define MSCD_COMMON_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd_Types.h>

#include <NvM_Mscd.h>

#include "../Mscd/cfg/Mscd_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define MSCD_SUSPEND_MS_RUN                     ((uint8)0x00U)
#define MSCD_SUSPEND_MS_SUSPEND                 ((uint8)0x55U)

#define MSCD_ERRINFO_ERRORFACTOR_FATALERROR     ((uint8)0x00U)
#define MSCD_ERRINFO_ERRORFACTOR_HSMERROR       ((uint8)0x01U)
#define MSCD_ERRINFO_ERRORFACTOR_NVM_FATALERROR ((uint8)0x02U)

#define MSCD_ERRINFO_FEE_KIND_RECOVER                  (0x00000001U)
#define MSCD_ERRINFO_FEE_KIND_RESTORE                  (0x00000002U)
#define MSCD_ERRINFO_FEE_ERR_NG_DTF_CTRL               (0x00000004U)
#define MSCD_ERRINFO_FEE_ERR_NG_INTERNAL               (0x00000008U)
#define MSCD_ERRINFO_FEE_ERR_TIMEOUT                   (0x00000010U)
#define MSCD_ERRINFO_FEE_ERR_NG_WRITE                  (0x00000020U)
#define MSCD_ERRINFO_FEE_ERR_NODATA                    (0x00000040U)
#define MSCD_ERRINFO_FEE_ERR_UNUSED                    (0x00000080U)
#define MSCD_ERRINFO_FEE_ERR_VANISH_AREA               (0x00000100U)
#define MSCD_ERRINFO_FEE_ERR_IRBLD_CNFM_NOT_OK         (0x00000200U)
#define MSCD_ERRINFO_FEE_ERR_VOLT_CNFM_NOT_OK          (0x00000400U)
#define MSCD_ERRINFO_FEE_ERR_UNDEFINED                 (0x00008000U)
#define MSCD_ERRINFO_NVM_ERR_JOB_TIMEOUT               (0x00010000U)
#define MSCD_ERRINFO_NVM_ERR_SYNC_MECHANISM_NG         (0x00020000U)
#define MSCD_ERRINFO_NVM_ERR_WRT_TO_PROT_SKIP          (0x00040000U)
#define MSCD_ERRINFO_NVM_ERR_WRT_FRM_INVALID_RAM_SKIP  (0x00080000U)
#define MSCD_ERRINFO_NVM_ERR_WRT_FRM_UNCHANGE_RAM_SKIP (0x00100000U)
#define MSCD_ERRINFO_NVM_ERR_READ_TO_VALID_RAM_SKIP    (0x00200000U)
#define MSCD_ERRINFO_NVM_ERR_ABORT                     (0x00400000U)
#define MSCD_ERRINFO_NVM_ERR_CANCEL_WRT_ALL            (0x00800000U)
#define MSCD_ERRINFO_NVM_ERR_PREEMPT_IMM_WRT           (0x01000000U)
#define MSCD_ERRINFO_NVM_ERR_NODATA                    (0x02000000U)
#define MSCD_ERRINFO_NVM_KIND_RESTORE                  (0x04000000U)
#define MSCD_ERRINFO_NVM_ERR_LOSS_OF_REDUNDANCY        (0x08000000U)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

FUNC(uint8, MSCD_CODE) Mscd_Suspend_UpdateOpeState( void );

FUNC(void, MSCD_CODE) Mscd_ErrorInfo_DetectErrorFactor( uint8 u1ErrorFactor );
FUNC(void, MSCD_CODE) Mscd_ErrorInfo_UpdateErrorResult( uint32 u4ErrorResult );

FUNC(Std_ReturnType, MSCD_CODE) Mscd_Cnfm_CheckJobExecHook( void );
FUNC(Std_ReturnType, MSCD_CODE) Mscd_Cnfm_CheckWcWriteHook( void );
#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
FUNC(Std_ReturnType, MSCD_CODE) Mscd_Cnfm_CheckRestoreHook( void );
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */
FUNC(Std_ReturnType, MSCD_CODE) Mscd_Cnfm_CheckIntentRbld(uint8 AreaNo);

FUNC(void,  MSCD_CODE) Mscd_Msif_SingleBlockJobStartHook(NvM_BlockIdType BlockId, NvM_BlockRequestType BlockRequest);
FUNC(void,  MSCD_CODE) Mscd_Msif_MultiBlockJobStartHook(NvM_MultiBlockRequestType MultiBlockRequest);
FUNC(void,  MSCD_CODE) Mscd_Msif_SingleBlockJobEndHook(NvM_BlockIdType BlockId, NvM_BlockRequestType BlockRequest);
FUNC(void,  MSCD_CODE) Mscd_Msif_MultiBlockJobEndHook(NvM_MultiBlockRequestType MultiBlockRequest);
FUNC(void,  MSCD_CODE) Mscd_Msif_NvMMFProcessResultNotification     ( uint8 ProcessResult );
FUNC(void,  MSCD_CODE) Mscd_Msif_SpeedUpMFProcessResultNotification ( uint8 ProcessResult );
FUNC(void,  MSCD_CODE) Mscd_Msif_DfaiMFProcessResultNotification    ( uint8 ProcessResult );

FUNC( void, MSCD_CODE ) Mscd_Frm_NvMExclusiveLockBegin( void );
FUNC( void, MSCD_CODE ) Mscd_Frm_NvMExclusiveLockEnd( void );

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

#endif /* MSCD_COMMON_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/01/31                                              */
/*  1-2-0          :2019/09/06                                              */
/*  2-0-0          :2022/07/15                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
