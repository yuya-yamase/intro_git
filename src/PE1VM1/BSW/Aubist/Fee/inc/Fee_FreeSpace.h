/* Fee_FreeSpace.h v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/FREESPACE/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_FREESPACE_H
#define FEE_FREESPACE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee_Ext.h>
#include <Mscd_Common.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#if ( MSCD_FREESPACE_USE == STD_ON )

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_FreeSpace_GetFreeSpace(
    uint8  AreaNo,
    uint16 LimitSearchMngArea,
    uint32 LimitSearchDataArea,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

#endif /* FEE_FREESPACE_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/08/21                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
