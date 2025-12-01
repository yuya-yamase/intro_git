/* Fee_Lib.h v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/LIB/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef FEE_LIB_H
#define FEE_LIB_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Fee_Mpu_Const.h"
#include <Fls.h>
#include <Mscd_Common.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_DUMMY_AREA_NO_FOR_LWPOS     (0U)    /* Dummy area number at last write position initialization */

/* Setting processing type */
#define FEE_LWPREAD         ((uint8)0x00U)      /* Setting processing type: ID-specified read or free space check */
#define FEE_LWPWRITE        ((uint8)0x01U)      /* SetupProcessType: Write or Reorganize */
#define FEE_LWPKIND_INIT    ((uint8)0xFFU)      /* Setting processing type initial */

#define FEE_LIB_EQUAL       ((uint8)0x00U)
#define FEE_LIB_UNEQUAL     ((uint8)0x01U)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( Std_ReturnType, FEE_CODE )
Fee_Lib_CheckCpuDtfData( void );

FUNC( void, FEE_CODE )
Fee_Lib_SetCpuDtfDataSub( void );

FUNC( uint8, FEE_CODE )
Fee_Lib_CompareMemory(
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) Data1,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) Data2,
    uint32                               Length
);

FUNC( void, FEE_CODE )
Fee_Lib_CopyMemory(
    P2VAR( uint8, AUTOMATIC, TYPEDEF )   DstData,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) SrcData,
    uint32                               Length
);

#if ( MSCD_FREESPACE_USE == STD_ON )
FUNC( Std_ReturnType, FEE_CODE )
Fee_Lib_GetLastWritePosLite(
    uint8 AreaNo,
    uint8 CurrentJobKind,
    P2VAR( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) DstLastWritePos
);

FUNC( void, FEE_CODE )
Fee_Lib_SetLastWritePosLite(
    uint8 AreaNo,
    P2CONST( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) SrcLastWritePos
);
#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

/* Data flash address value conversion Absolute address </= relative address > Relative address */
FUNC(uint32, FEE_CODE) Fee_ConvAddr_AbsToBaseRelative( uint32 u4_absolute_address );
FUNC(uint32, FEE_CODE) Fee_ConvAddr_AbsToSectorTopRelative( uint32 u4_absolute_address );
FUNC(uint32, FEE_CODE) Fee_ConvAddr_RelativeToAbsolute( uint32 u4_relative_address );

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

/* Configuration items as a whole */
/* Write Hardware latency threshold */
extern CONST(AB_83_ConstV uint32, FEE_CONST) Fee_HwLmtWriteTime;

/* Area block status data address */
extern CONST(AB_83_ConstV uint8, FEE_CONST) Fee_ASBSDataTBL[FEE_ASBSDATASETNUM][FEE_ASBSDATAKINDNUM];

#define FEE_STOP_SEC_CONST_32
#include <Fee_MemMap.h>

#endif /* FEE_LIB_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/23                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
