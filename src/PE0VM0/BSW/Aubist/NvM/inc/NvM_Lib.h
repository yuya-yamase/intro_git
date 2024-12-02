/* NvM_Lib.h v2-1-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/LIB/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_LIB_H
#define     NVM_LIB_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
#define NVM_LIB_DATA1_EQUAL_DATA2       ( 0 )
#define NVM_LIB_DATA2_LARGER_THAN_DATA1 ( -1 )
#define NVM_LIB_DATA1_LARGER_THAN_DATA2 ( 1 )
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef struct {
    uint32  Parameter;
    uint32  Result;
} NvM_Lib_ValueConvertPairType;

typedef struct {
    uint32 Size;
    P2CONST( AB_83_ConstV NvM_Lib_ValueConvertPairType, NVM_CONST, NVM_CONST ) Pairs;
} NvM_Lib_ValueConvertTableType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

#if ( NVM_USE_ROM_BLOCK == STD_ON )
FUNC( void, NVM_CODE )
NvM_Lib_Memcpy(
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) ptDst,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ptSrc,
    uint32 u4Length
);
#endif /* NVM_USE_ROM_BLOCK == STD_ON */

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
FUNC( void, NVM_CODE )
NvM_Lib_MemcpyBitInvert(
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) ptDst,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ptSrc,
    uint32 u4Length
);

FUNC( sint32, NVM_CODE )
NvM_Lib_MemcmpBitInvert(
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) Data1,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) Data2,
    uint32 u4Length
);
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */
FUNC( uint32, NVM_CODE )
NvM_Lib_ConvertValue(
    uint32 ConvPara,
    uint32 DefaultValue,
    P2CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType, AUTOMATIC, NVM_CONST ) Table
);

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_LIB_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2018/10/24                                              */
/*  2-0-0          :2020/12/20                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
