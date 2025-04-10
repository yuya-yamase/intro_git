/* NvM_Romb.c v1-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/ROMB/CODE                                             */
/*--------------------------------------------------------------------------*/
/* Notes        | None                                                      */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_Lib.h"
#include "../inc/NvM_Romb.h"
#include "../inc/NvM_Romb_Internal.h"

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_Romb_Init                                            */
/* Description   | Function for resetting this unit.                        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Romb_Init( void )
{
    return ;
}

/****************************************************************************/
/* Function Name | NvM_Romb_GetRomData                                      */
/* Description   | Function to copy ROM to DstData of the argument.         */
/* Preconditions | None                                                     */
/* Parameters    | BlockId : The BlockId is corresponding to ROM.           */
/*               | DstData : Copy destination data array.                   */
/* Return Value  | Std_ReturnType : Result of copy                          */
/*               |  E_OK    : Success.                                      */
/*               |  E_NOT_OK: Failure.                                      */
/*               |            ROM corresponding to BlockId is not found.    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, NVM_CODE )
NvM_Romb_GetRomData(
    NvM_BlockIdType BlockId,
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) DstData
){
    Std_ReturnType Rtn = E_NOT_OK;
#if ( NVM_USE_ROM_BLOCK == STD_ON )
    P2CONST( uint8, AUTOMATIC, NVM_APPL_CONST ) SrcDataAddr;
    uint16 Length;
    boolean IsExistingRomBlock;

    IsExistingRomBlock = NvM_Romb_IsExistingRomBlock( BlockId );
    if( IsExistingRomBlock == (boolean)TRUE )
    {
        SrcDataAddr = NvMBlockDescriptors[BlockId].NvMRomBlockDataAddress;
        Length = NvMBlockDescriptors[BlockId].NvMNvBlockLength;
        NvM_Lib_Memcpy( DstData, SrcDataAddr, (uint32)Length );
        Rtn = E_OK;
    }
#endif /* NVM_USE_ROM_BLOCK == STD_ON */

    return Rtn;
}

/****************************************************************************/
/* Function Name | NvM_Romb_IsExistingRomBlock                              */
/* Description   | Function to return existence or not of ROM Block.        */
/* Preconditions | None                                                     */
/* Parameters    | BlockId : Target Block ID.                               */
/* Return Value  | boolean : Check Result                                   */
/*               |  TRUE  : ROM Block is existence.                         */
/*               |  FALSE : ROM Block is non-existence.                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, NVM_CODE )
NvM_Romb_IsExistingRomBlock(
    NvM_BlockIdType BlockId
){
    boolean Rtn = FALSE;
    
#if ( NVM_USE_ROM_BLOCK == STD_ON )
    if( NvMBlockDescriptors[BlockId].NvMRomBlockNum > (uint8)NVM_ROMB_ROMBLOCK_NUM_ZERO )
    {
        Rtn = TRUE;
    }
#endif /* NVM_USE_ROM_BLOCK == STD_ON */

    return Rtn;
}

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
