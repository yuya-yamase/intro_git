/* NvM_Adb.h v1-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/ADB/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_ADB_H
#define     NVM_ADB_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define NVM_ADB_PRAM_INVALID_UNCHANGED       ( 0x00U )
#define NVM_ADB_PRAM_VALID_UNCHANGED         ( 0x70U )
#define NVM_ADB_PRAM_VALID_CHANGED           ( 0x77U )

#define NVM_ADB_WRITE_PROT_ENABLED           ( 0x01U )
#define NVM_ADB_WRITE_PROT_DISABLED          ( 0x02U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef uint8               NvM_Adb_RamBlockStatusType;
typedef uint8               NvM_Adb_WriteProtectStatusType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Adb_Init ( void );

FUNC( void, NVM_CODE )
NvM_Adb_SetRamBlockStatus(
    NvM_BlockIdType BlockId,
    NvM_Adb_RamBlockStatusType Status
);

FUNC( void, NVM_CODE )
NvM_Adb_SetNvBlockProtection(
    NvM_BlockIdType BlockId,
    NvM_Adb_WriteProtectStatusType StateValue
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Adb_GetRamBlockStatus(
    NvM_BlockIdType BlockId,
    P2VAR( NvM_Adb_RamBlockStatusType, AUTOMATIC, TYPEDEF ) Status
);

FUNC( NvM_Adb_WriteProtectStatusType, NVM_CODE )
NvM_Adb_GetNvBlockProtection(
    NvM_BlockIdType BlockId
);

FUNC( void, NVM_CODE )
NvM_Adb_SetErrorStatus(
    NvM_BlockIdType BlockId,
    uint32 JobId,
    NvM_RequestResultType RequestResult
);

#if ( NVM_USE_CANCEL_NOTIFICATION == STD_OFF )
FUNC( void, NVM_CODE )
NvM_Adb_SetErrorStatusNonNotification(
    NvM_BlockIdType BlockId,
    NvM_RequestResultType RequestResult
);
#endif /* NVM_USE_CANCEL_NOTIFICATION == STD_OFF */

FUNC( Std_ReturnType, NVM_CODE )
NvM_Adb_GetErrorStatus(
    NvM_BlockIdType BlockId,
    P2VAR( NvM_RequestResultType, AUTOMATIC, TYPEDEF ) RequestResult
);

FUNC( void, NVM_CODE )
NvM_Adb_CheckRamError( void );

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_ADB_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
