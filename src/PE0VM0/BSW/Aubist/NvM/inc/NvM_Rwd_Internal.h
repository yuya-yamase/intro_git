/* NvM_Rwd_Internal.h v1-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/RWD/INTERNAL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_RWD_INTERNAL_H
#define     NVM_RWD_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define NVM_RWD_COUNTER_INIT            ( 0U )
#define NVM_RWD_RAMMIRROR_UINT32_LENGTH ((NVM_MAX_RAM_MIRROR_LENGTH + 3U) >> 2U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef union{
   uint32 Uint32StrangeForAlignment[NVM_RWD_RAMMIRROR_UINT32_LENGTH];
   uint8 Uint8Data[NVM_MAX_RAM_MIRROR_LENGTH];
} NvM_Rwd_RamMirrorAlignBufferType;

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

extern VAR( uint8, NVM_VAR_NO_INIT ) NvM_Rwd_RetryCounter;

extern P2VAR( uint8, NVM_VAR_NO_INIT, NVM_APPL_DATA ) NvM_Rwd_ReadDataNotifyDstPtr;
extern P2CONST( uint8, NVM_VAR_NO_INIT, TYPEDEF ) NvM_Rwd_WriteDataAcquireSrcPtr;

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>


#define NVM_START_SEC_VAR_SAVED_ZONE_32
#include <NvM_MemMap.h>

extern VAR( NvM_Rwd_RamMirrorAlignBufferType, NVM_VAR_NO_INIT ) NvM_Rwd_RamMirror;

#define NVM_STOP_SEC_VAR_SAVED_ZONE_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Rwd_ClearRetryCounter( void );

FUNC( NvM_Rwd_DataPassingResultType, NVM_CODE )
NvM_Rwd_CheckRetryCounter( void );

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_RWD_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
