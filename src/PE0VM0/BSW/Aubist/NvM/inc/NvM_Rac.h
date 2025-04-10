/* NvM_Rac.h v1-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/RAC/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_RAC_H
#define     NVM_RAC_H

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Rac_Init( void );

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqSetBlockProtection(
    NvM_BlockIdType BlockId,
    boolean ProtectionEnabled
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqGetErrorStatus(
    NvM_BlockIdType BlockId,
    P2CONST( NvM_RequestResultType, AUTOMATIC, NVM_APPL_DATA ) RequestResultPtr
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqGetVersionInfo(
    P2CONST( Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA ) VersionInfo
);

#if ( NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON )
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqSetRamBlockStatus(
    NvM_BlockIdType BlockId,
    boolean BlockChanged
);
#endif /* NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON */

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqCancelJobs(
    NvM_BlockIdType BlockId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqReadBlock(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, NVM_APPL_DATA ) DstPtr
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqWriteBlock(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) SrcPtr
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqRestoreBlockDefaults(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, NVM_APPL_DATA ) DstPtr
);

#if ( NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON )
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqCancelWriteAll( void );
#endif /* NVM_VALID_CANCEL_WRITE_ALL_API == STD_ON */

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqReadPRAMBlock(
    NvM_BlockIdType BlockId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqWritePRAMBlock(
    NvM_BlockIdType BlockId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqRestorePRAMBlockDefaults(
    NvM_BlockIdType BlockId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqReadAll( void );

#if ( NVM_VALID_WRITE_ALL_API == STD_ON )
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_IsPReqWriteAll( void );
#endif /* NVM_VALID_WRITE_ALL_API == STD_ON */

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_RAC_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
