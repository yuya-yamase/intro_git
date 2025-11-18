/* Fee_FreeSpace_Internal.h v1-1-0                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/FREESPACE/INTERNAL/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_FREESPACE_INTERNAL_H
#define FEE_FREESPACE_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_FREESPACE_MNGRCRD_NOSPACE       (0U)
#define FEE_FREESPACE_DATBYTE_NOSPACE       (0U)

#define FEE_FREESPACE_ROUNDUP_VAL_ECC_FIX_SIZE  ( (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE - (uint32)1U )
#define FEE_FREESPACE_MAX_NUM_OF_BC_DATAAREA    ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE / (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_FreeSpace_CheckBS(
    uint8  AreaNo,
    P2VAR( Fee_LwpInfType,           AUTOMATIC, TYPEDEF ) LastWritePosInfo,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
);

FUNC( uint32, FEE_CODE )
Fee_FreeSpace_CheckBSOnFlash(
    uint8  AreaNo,
    P2VAR( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) LastWritePosInfo,
    P2VAR( boolean,        AUTOMATIC, TYPEDEF ) NeedsToFixBS
);

FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_FreeSpace_GetFreeSpaceMngArea(
    uint8  AreaNo,
    uint16 LimitSearchMngArea,
    P2VAR( Fee_LwpInfType,           AUTOMATIC, TYPEDEF ) LastWritePosInfo,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
);

FUNC( uint32, FEE_CODE )
Fee_FreeSpace_SrchMngAreaOnFlash(
    uint8  AreaNo,
    uint32 SearchNum,
    P2VAR( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) LastWritePosInfo
);

FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_FreeSpace_GetFreeSpaceDatArea(
    uint8  AreaNo,
    uint32 LimitSearchDataArea,
    P2VAR( Fee_LwpInfType,           AUTOMATIC, TYPEDEF ) LastWritePosInfo,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
);

FUNC( uint32, FEE_CODE )
Fee_FreeSpace_SrchDatAreaOnFlash(
    uint8  AreaNo,
    uint32 SearchNum,
    P2VAR( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) LastWritePosInfo
);

FUNC( void, FEE_CODE )
Fee_FreeSpace_ClearLastWritePos(
    P2VAR( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) LastWritePosInfo
);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_FREESPACE_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/10/09                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
