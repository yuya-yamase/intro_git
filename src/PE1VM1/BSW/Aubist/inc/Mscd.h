/* Mscd.h v2-0-0                                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/HEADER                                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MSCD_H
#define MSCD_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd_Types.h>
#include "../Mscd/cfg/Mscd_Cfg.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#if( MSCD_ERRORINFO_USE == STD_ON )

/* ErrorInfo Macros */
/* ErrorInfo bit pattern */
#define MSCD_ERRINFO_NO_ERROR                (0x00000000U)

/* ErrorInfo (factor) bit pattern */
#define MSCD_ERRINFO_FACTOR_FATALERROR       (0x00000001U)
#define MSCD_ERRINFO_FACTOR_HSMERROR         (0x00000002U)
#define MSCD_ERRINFO_FACTOR_NVM_FATALERROR   (0x00000004U)

/* ErrorInfo (state) bit pattern */
#define MSCD_ERRINFO_STATE_READ_DISABLE      (0x00000001U)
#define MSCD_ERRINFO_STATE_WRITE_DISABLE     (0x00000002U)

/* ErrorInfo (result) bit pattern */
#define MSCD_ERRINFO_RESULT_NO_ERROR                  (0x00000000U)
#define MSCD_ERRINFO_RESULT_JOB_TIMEOUT               (0x00000001U)
#define MSCD_ERRINFO_RESULT_RESTORE                   (0x00000002U)
#define MSCD_ERRINFO_RESULT_VANISH_DATA               (0x00000004U)
#define MSCD_ERRINFO_RESULT_NODATA                    (0x00000008U)
#define MSCD_ERRINFO_RESULT_UNUSED                    (0x00000010U)
#define MSCD_ERRINFO_RESULT_WRITE_NG                  (0x00000020U)
#define MSCD_ERRINFO_RESULT_REBUILD_NG                (0x00000040U)
#define MSCD_ERRINFO_RESULT_DRV_TIMEOUT               (0x00000080U)
#define MSCD_ERRINFO_RESULT_HARD_NG                   (0x00000100U)
#define MSCD_ERRINFO_RESULT_INTERNAL_NG               (0x00000200U)
#define MSCD_ERRINFO_RESULT_SYNC_MECHANISM_NG         (0x00000400U)
#define MSCD_ERRINFO_RESULT_WRT_TO_PROT_SKIP          (0x00000800U)
#define MSCD_ERRINFO_RESULT_WRT_FRM_INVALID_RAM_SKIP  (0x00001000U)
#define MSCD_ERRINFO_RESULT_WRT_FRM_UNCHANGE_RAM_SKIP (0x00002000U)
#define MSCD_ERRINFO_RESULT_READ_TO_VALID_RAM_SKIP    (0x00004000U)
#define MSCD_ERRINFO_RESULT_ABORT                     (0x00008000U)
#define MSCD_ERRINFO_RESULT_CANCEL_WRT_ALL            (0x00010000U)
#define MSCD_ERRINFO_RESULT_PREEMPT_IMM_WRT           (0x00020000U)
#define MSCD_ERRINFO_RESULT_VANISH_AREA               (0x00040000U)
#define MSCD_ERRINFO_RESULT_IRBLD_CNFM_NOT_OK         (0x00080000U)
#define MSCD_ERRINFO_RESULT_LOSS_OF_REDUNDANCY        (0x00100000U)
#define MSCD_ERRINFO_RESULT_VOLT_CNFM_NOT_OK          (0x00200000U)
#define MSCD_ERRINFO_RESULT_UNDEFINED                 (0x80000000U)

#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/


#if( MSCD_DFAI_USE == STD_ON )

/* Dfai Macros */
/* status */
#define MSCD_DFAI_STATE_IDLE            (0x00U)
#define MSCD_DFAI_STATE_BUSY            (0x01U)
#define MSCD_DFAI_STATE_ERROR           (0x02U)

/* result */
#define MSCD_DFAI_JOB_OK                (0x00U)
#define MSCD_DFAI_JOB_BUSY              (0x01U)
#define MSCD_DFAI_JOB_BLANK             (0x02U)
#define MSCD_DFAI_JOB_NOT_BLANK         (0x03U)
#define MSCD_DFAI_JOB_ERROR             (0x04U)
#define MSCD_DFAI_JOB_CANCELED          (0x05U)
#define MSCD_DFAI_JOB_FATALERROR        (0x06U)
#define MSCD_DFAI_JOB_ACCEPT            (0x07U)
#define MSCD_DFAI_JOB_NOT_ACCEPT        (0x08U)
#define MSCD_DFAI_JOB_INOPERATIVE_HSM   (0x09U)
#define MSCD_DFAI_JOB_INTEGRITY_FAILED  (0x0AU)

#endif /*( MSCD_DFAI_USE == STD_ON )*/


#if( MSCD_FREESPACE_USE == STD_ON )

/* FreeSpace Macros */
/* return */
#define MSCD_E_FREESPACE_OK                     (0x00U)
#define MSCD_E_FREESPACE_PARAM_ERROR            (0x01U)
#define MSCD_E_FREESPACE_BUSY                   (0x02U)
#define MSCD_E_FREESPACE_AREA_FAULT             (0x03U)
#define MSCD_E_FREESPACE_INTERNAL_ERROR         (0x04U)
#define MSCD_E_FREESPACE_MS_SUSPEND             (0x05U)

/* result (bit pattern) */
#define MSCD_FREESPACE_RESULT_OK                        (0x00U)
#define MSCD_FREESPACE_RESULT_MNG_OVER_LIMIT            (0x01U)
#define MSCD_FREESPACE_RESULT_DATA_OVER_LIMIT           (0x02U)
#define MSCD_FREESPACE_RESULT_PENDING_REBUILD           (0x04U)
#define MSCD_FREESPACE_RESULT_BLANK                     (0x08U)
#define MSCD_FREESPACE_RESULT_AREAINFO_INCONSISTENT     (0x10U)

#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

#if( MSCD_SUSPEND_USE == STD_ON )

/* Suspend */
FUNC(void, MSCD_CODE) Mscd_Suspend_ReqUpdateOpeState( uint8 u1MemoryIdentifier );
FUNC(Std_ReturnType, MSCD_CODE) Mscd_Suspend_ReqAbort( uint8 u1MemoryIdentifier );

#endif /*( MSCD_SUSPEND_USE == STD_ON )*/


#if( MSCD_ERRORINFO_USE == STD_ON )

/* ErrorInfo */
FUNC(Std_ReturnType, MSCD_CODE) Mscd_ErrorInfo_GetErrorFactor( P2VAR(Mscd_ErrorInfo_ErrorFactorInfoType, AUTOMATIC, MSCD_APPL_DATA) ptrResult );
FUNC(Std_ReturnType, MSCD_CODE) Mscd_ErrorInfo_GetSingleBlockJobErrorResult( NvM_BlockRequestType u1BlockRequest, P2VAR(Mscd_ErrorInfo_ErrorResultInfoType, AUTOMATIC, MSCD_APPL_DATA) ptrResult );
FUNC(Std_ReturnType, MSCD_CODE) Mscd_ErrorInfo_GetMultiBlockJobErrorResult( NvM_MultiBlockRequestType u1MultiBlockRequest, P2VAR(Mscd_ErrorInfo_ErrorResultInfoType, AUTOMATIC, MSCD_APPL_DATA) ptrResult );

#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/


#if( MSCD_SPEEDUP_USE == STD_ON )

/* SpeedUp */
FUNC(void, MSCD_CODE) Mscd_SpeedUp_MainFunction( void );

#endif /*( MSCD_SPEEDUP_USE == STD_ON )*/


#if( MSCD_DFAI_USE == STD_ON )

/* Dfai */
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE) Mscd_Dfai_Write          ( uint8 u1MemoryIdentifier, uint32 u4Address, P2CONST(uint8, AUTOMATIC, MSCD_APPL_CONST) ptSrcPtr, uint32 u4Length );
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE) Mscd_Dfai_Erase          ( uint8 u1MemoryIdentifier, uint32 u4Address, uint32 u4Length );
FUNC(void, MSCD_CODE) Mscd_Dfai_MainFunction( uint8 u1MemoryIdentifier );
FUNC(Mscd_Dfai_StatusType, MSCD_CODE) Mscd_Dfai_GetStatus      ( uint8 u1MemoryIdentifier );
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE) Mscd_Dfai_GetJobResult( uint8 u1MemoryIdentifier );
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE) Mscd_Dfai_Read           ( uint8 u1MemoryIdentifier, uint32 u4Address, P2VAR(uint8, AUTOMATIC, MSCD_APPL_DATA) ptSrcPtr, uint32 u4Length );
FUNC(Mscd_Dfai_ReturnType, MSCD_CODE) Mscd_Dfai_BlankCheck     ( uint8 u1MemoryIdentifier, uint32 u4Address, uint32 u4Length );

#endif /*( MSCD_DFAI_USE == STD_ON )*/


#if( MSCD_FREESPACE_USE == STD_ON )

/* FreeSpace */
FUNC(Mscd_FreeSpaceReturnType, MSCD_CODE)
Mscd_GetFreeSpace(
    uint8 AreaNo,
    uint16 LimitSearchMngArea,
    uint32 LimitDataAreaByte,
    P2VAR(Mscd_FreeSpaceInfoType, AUTOMATIC, MSCD_APPL_DATA) FreeSpaceInfoPtr
);

#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

/* Msif */
FUNC(void, MSCD_CODE) Mscd_Init( void );
FUNC(Std_ReturnType, MSCD_CODE) Mscd_Msif_GetStatus( P2VAR(Mscd_MsStatusType, AUTOMATIC, MSCD_APPL_DATA) MsStatusPtr );
FUNC(uint8, MSCD_CODE) Mscd_Msif_GetNvMMainFunctionProcessResult      ( void );
FUNC(uint8, MSCD_CODE) Mscd_Msif_GetSpeedUpMainFunctionProcessResult  ( void );
FUNC(uint8, MSCD_CODE) Mscd_Msif_GetDfaiMainFunctionProcessResult     ( void );

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

#endif /* MSCD_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/01/31                                              */
/*  2-0-0          :2020/03/31                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
