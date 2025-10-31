/* Mscd_FreeSpace_Internal.h v1-0-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/FREESPACE/INTERNAL/HEADER                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MSCD_FREESPACE_INTERNAL_H
#define MSCD_FREESPACE_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

#if ( MSCD_FREESPACE_USE == STD_ON )

FUNC(void, MSCD_CODE)
Mscd_FreeSpace_TransformFreeSpaceInfo(
    P2VAR(Mscd_FreeSpaceInfoType, AUTOMATIC, MSCD_APPL_DATA) MscdFreeSpaceInfoPtr,
    P2CONST(Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF) FeeFreeSpaceInfoPtr
);

#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

#endif /* MSCD_FREESPACE_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/08/27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
