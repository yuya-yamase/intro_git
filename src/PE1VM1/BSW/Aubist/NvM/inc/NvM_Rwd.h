/* NvM_Rwd.h v1-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/RWD/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_RWD_H
#define     NVM_RWD_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include "../cfg/NvM_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define NVM_RWD_REQ_OK                       ( 0x00U )
#define NVM_RWD_REQ_NOT_OK                   ( 0x01U )
#define NVM_RWD_REQ_PENDING                  ( 0x02U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef uint8               NvM_Rwd_DataPassingResultType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Rwd_Init( void );

FUNC( void, NVM_CODE )
NvM_Rwd_ReadDataNotificationInit(
    NvM_BlockIdType BlockId,
    P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) DstPtr
);

FUNC_P2VAR( uint8, TYPEDEF, NVM_CODE )
NvM_Rwd_GetReadDataBuffer(
    NvM_BlockIdType BlockId
);

FUNC( NvM_Rwd_DataPassingResultType, NVM_CODE )
NvM_Rwd_ReadDataNotification(
    NvM_BlockIdType BlockId
);

FUNC( void, NVM_CODE )
NvM_Rwd_WriteDataAcquisitionInit(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) SrcPtr
);

FUNC_P2CONST( uint8, TYPEDEF, NVM_CODE )
NvM_Rwd_GetWriteData(
    NvM_BlockIdType BlockId
);

FUNC( NvM_Rwd_DataPassingResultType, NVM_CODE )
NvM_Rwd_WriteDataAcquisition(
    NvM_BlockIdType BlockId
);

FUNC( boolean, NVM_CODE )
NvM_Rwd_NvM_IsDstRamTemporary( void );

FUNC( boolean, NVM_CODE )
NvM_Rwd_NvM_IsSrcRamTemporary( void );

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_RWD_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
