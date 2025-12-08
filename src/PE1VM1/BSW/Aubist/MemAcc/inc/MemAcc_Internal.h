/* MemAcc_Internal.h v2-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MEMACC/INTERNAL/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MEMACC_INTERNAL_H
#define MEMACC_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define MEMACC_MIRROR_CHECK_UINT8  (0xFFU)
#define MEMACC_MIRROR_CHECK_UINT16 (0xFFFFU)
#define MEMACC_MIRROR_CHECK_UINT32 (0xFFFFFFFFU)

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEMACC_START_SEC_CONST_32
#include <MemAcc_MemMap.h>

extern CONST( AB_83_ConstV Std_VersionInfoType, MEMACC_CONST ) MemAcc_VersionInfo;

#define MEMACC_STOP_SEC_CONST_32
#include <MemAcc_MemMap.h>

#endif /* MEMACC_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2024/08/08                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
