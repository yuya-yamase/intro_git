/* NvM_Rac_Internal.h v1-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/RAC/INTERNAL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_RAC_INTERNAL_H
#define     NVM_RAC_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkBlockId(
    NvM_BlockIdType BlockId,
    uint8 ServiceId,
    boolean IsPermitMultiBlockId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkAdbJobStatus(
    NvM_BlockIdType BlockId,
    uint8 ServiceId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkConfWriteOnce(
    NvM_BlockIdType BlockId,
    uint8 ServiceId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkReqResultPtr(
    P2CONST( NvM_RequestResultType, AUTOMATIC, NVM_APPL_DATA ) RequestResultPtr,
    uint8 ServiceId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkVersionInfoPtr(
    P2CONST( Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA ) VersionInfo,
    uint8 ServiceId
);

#if ( NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON )
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkConfUseSetRamBlockStatus(
    NvM_BlockIdType BlockId
);
#endif /* NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON */

#if ( NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON )
FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkConfRamBlockType(
    NvM_BlockIdType BlockId,
    uint8 ServiceId
);
#endif /* NVM_VALID_SET_RAM_BLOCK_STATUS_API == STD_ON */

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkConfRamBlockTypeAndPtr(
    NvM_BlockIdType BlockId,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) RamPtr,
    uint8 ServiceId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkConfDefaultData(
    NvM_BlockIdType BlockId,
    uint8 ServiceId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkWriteProtected(
    NvM_BlockIdType BlockId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Rac_ChkBooleanValueRange(
    boolean Value
);

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_RAC_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
