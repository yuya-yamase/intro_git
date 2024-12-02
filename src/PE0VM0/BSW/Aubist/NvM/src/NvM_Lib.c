/* NvM_Lib.c v2-1-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/LIB/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        | None                                                      */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_Lib.h"
#include "../inc/NvM_Lib_Internal.h"

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

#if ( NVM_USE_ROM_BLOCK == STD_ON )
/****************************************************************************/
/* Function Name | NvM_Lib_Memcpy                                           */
/* Description   | Function to copy source data area to destination data    */
/*               | area.                                                    */
/* Preconditions | None                                                     */
/* Parameters    | ptDst : An address of destination data.                  */
/*               | ptSrc : An address of source data.                       */
/*               | u4Length : Size of data for copy                         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Lib_Memcpy(
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) ptDst,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ptSrc,
    uint32 u4Length
){
    uint32 u4_Index;
    
    for( u4_Index = 0U; u4_Index < u4Length; u4_Index++ ){
        ptDst[u4_Index] = ptSrc[u4_Index];
    }
    
    return;
}
#endif /* NVM_USE_ROM_BLOCK == STD_ON */

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
/****************************************************************************/
/* Function Name | NvM_Lib_MemcpyBitInvert                                  */
/* Description   | Function to copy source data area to bit inverted        */
/*               | destination data area.                                   */
/* Preconditions | None                                                     */
/* Parameters    | ptDst : An address of destination data.                  */
/*               | ptSrc : An address of source data.                       */
/*               | u4Length : Size of data for copy                         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Lib_MemcpyBitInvert(
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) ptDst,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) ptSrc,
    uint32 u4Length
){
    uint32 u4_Index;
    
    for( u4_Index = 0U; u4_Index < u4Length; u4_Index++ ){
        ptDst[u4_Index] = (uint8)~ptSrc[u4_Index];
    }
    
    return;
}

/****************************************************************************/
/* Function Name | NvM_Lib_MemcmpBitInvert                                  */
/* Description   | Function to compare first data with bit inverted second  */
/*               | data.                                                    */
/* Preconditions | None                                                     */
/* Parameters    | Data1: An address of first data.                         */
/*               | Data2: An address of second data.                        */
/*               | u4Length : Size of data for comparison                   */
/* Return Value  | sint32 : Comparison result                               */
/*               |  NVM_LIB_DATA1_EQUAL_DATA2       :                       */
/*               |                 Data1 equals Bit inverted Data2.         */
/*               |  NVM_LIB_DATA2_LARGER_THAN_DATA1 :                       */
/*               |                 Bit inverted Data2 is larger than Data1. */
/*               |  NVM_LIB_DATA1_LARGER_THAN_DATA2 :                       */
/*               |                 Data1 is larger than Bit inverted Data2. */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( sint32, NVM_CODE )
NvM_Lib_MemcmpBitInvert(
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) Data1,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) Data2,
    uint32 u4Length
){
    uint32 u4_Index;
    sint32 s4_Result = NVM_LIB_DATA1_EQUAL_DATA2;
    uint8  u1_Data1Element;
    uint8  u1_Data2Element;
    
    for( u4_Index = 0U; u4_Index < u4Length; u4_Index++ ){
        u1_Data1Element = Data1[u4_Index];
        u1_Data2Element = (uint8)~Data2[u4_Index];
        
        if( u1_Data1Element != u1_Data2Element ){
            if( u1_Data1Element < u1_Data2Element ){
                  s4_Result = NVM_LIB_DATA2_LARGER_THAN_DATA1;
            }else{
                  s4_Result = NVM_LIB_DATA1_LARGER_THAN_DATA2;
            }
            break;
        }
    }
    
    return( s4_Result );
}
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */

/****************************************************************************/
/* Function Name | NvM_Lib_ConvertValue                                     */
/* Description   | Function to convert value using conversion table.        */
/* Preconditions | None                                                     */
/* Parameters    | ConvPara     : Source value                              */
/*               | DefaultValue : Default value                             */
/*               | Table        : Conversion table                          */
/* Return Value  | uint32 : Converted value                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, NVM_CODE )
NvM_Lib_ConvertValue(
    uint32 ConvPara,
    uint32 DefaultValue,
    P2CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType, AUTOMATIC, NVM_CONST ) Table
){
    uint32 ConvResult;
    uint32 TableSize;
    uint32 Index;

    ConvResult = DefaultValue;
    TableSize  = Table->Size;

    for( Index = 0U; Index < TableSize; Index++ ){
        if( Table->Pairs[Index].Parameter == ConvPara ){
            ConvResult = Table->Pairs[Index].Result;
            break;
        }
    }
    return ConvResult;
}

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2018/10/24                                              */
/*  2-0-0          :2020/12/20                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
