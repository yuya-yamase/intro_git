/* Fee_FreeSpace.c v2-1-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/FREESPACE/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>
#include <Fee_Ext.h>

#include "../inc/Fee_Common.h"

#include "../inc/Fee_FreeSpace.h"
#include "../inc/Fee_FreeSpace_Internal.h"

#include <Mscd_Common.h>

#include "../inc/Fee_Lib.h"
#include "../inc/Fee_Dfc.h"

#include "../inc/Fee_FlsWrp.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

#if ( MSCD_FREESPACE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Fee_FreeSpace_GetFreeSpace                               */
/* Description   | Function to get free space sizes on data flash.          */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo                                                   */
/*               | LimitSearchMngArea                                       */
/*               | LimitSearchDataArea                                      */
/*               | FreeSpaceInfoPtr    : Output value                       */
/* Return Value  | The result of getting free space sizes.                  */
/*               |      FEE_EXT_E_FRSP_OK                                   */
/*               |      FEE_EXT_E_FRSP_PARAM_ERROR                          */
/*               |      FEE_EXT_E_FRSP_BUSY                                 */
/*               |      FEE_EXT_E_FRSP_AREA_FAULT                           */
/*               |      FEE_EXT_E_FRSP_INTERNAL_ERROR                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_FreeSpace_GetFreeSpace(
    uint8  AreaNo,
    uint16 LimitSearchMngArea,
    uint32 LimitSearchDataArea,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
){
    Fee_ExtFreeSpaceReturnType  Rtn;
    Fee_ExtFreeSpaceResultType  MaskedResult;
    Fee_LwpInfType              LastWritePosInfo;

    /* Init variables */
    FreeSpaceInfoPtr->Result       = FEE_EXT_FRSP_RESULT_OK;
    FreeSpaceInfoPtr->RcrdNum      = FEE_FREESPACE_MNGRCRD_NOSPACE;
    FreeSpaceInfoPtr->DataAreaByte = FEE_FREESPACE_DATBYTE_NOSPACE;

    /* Get last write positions. */
    Fee_FreeSpace_ClearLastWritePos( &LastWritePosInfo );
    /* Note: The return value of Fee_Lib_GetLastWritePosLite is not checked. */
    /*       Even if the return value is E_NOT_OK that means LastWritePosInfo is not updated, */
    /*       this function can fulfill its functionality with default values.               */
    (void)Fee_Lib_GetLastWritePosLite( AreaNo, FEE_LWPWRITE, &LastWritePosInfo );

    /* Get a free space. */
    Rtn = Fee_FreeSpace_CheckBS( AreaNo, &LastWritePosInfo, FreeSpaceInfoPtr );
    if( Rtn == (Fee_ExtFreeSpaceReturnType)FEE_EXT_E_FRSP_OK )
    {
        MaskedResult = (FreeSpaceInfoPtr->Result) & (Fee_ExtFreeSpaceResultType)(~FEE_EXT_FRSP_RESULT_AREAINFO_INCONSISTENT);
        if( MaskedResult == (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_OK )
        {
            Rtn = Fee_FreeSpace_GetFreeSpaceMngArea( AreaNo, LimitSearchMngArea, &LastWritePosInfo, FreeSpaceInfoPtr );
            if( Rtn == (Fee_ExtFreeSpaceReturnType)FEE_EXT_E_FRSP_OK )
            {
                Rtn = Fee_FreeSpace_GetFreeSpaceDatArea( AreaNo, LimitSearchDataArea, &LastWritePosInfo, FreeSpaceInfoPtr );
            }
            else /* Rtn == FEE_EXT_E_FRSP_BUSY */
            {
                /* No process. */
            }
        }
        else /* FreeSpaceInfoPtr->Result == FEE_EXT_FRSP_RESULT_PENDING_RBLD, FEE_EXT_FRSP_RESULT_BLANK, */
             /*                            ( FEE_EXT_FRSP_RESULT_PENDING_RBLD | FEE_EXT_FRSP_RESULT_AREAINFO_INCONSISTENT ) */
        {
            /* No process. */
        }
    }
    else /* Rtn == FEE_EXT_E_FRSP_BUSY, FEE_EXT_E_FRSP_AREA_FAULT */
    {
        /* No process. */
    }

    /* Set last write positions. */
    if( Rtn == (Fee_ExtFreeSpaceReturnType)FEE_EXT_E_FRSP_OK )
    {
        if( FreeSpaceInfoPtr->Result == (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_OK )
        {
            LastWritePosInfo.u1SetKind = FEE_LWPWRITE;
            Fee_Lib_SetLastWritePosLite( AreaNo, &LastWritePosInfo );
        }
    }

    return Rtn;
}
#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Fee_FreeSpace_CheckBS                                    */
/* Description   | Function to check BS for getting free spaces.            */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo                                                   */
/*               | LastWritePosInfo : An input and output value.            */
/*               |      Input structure members are the following.          */
/*               |          1. stMainBlockInfo.u1BlockStatus                */
/*               |          2. stSubBlockInfo.u1BlockStatus                 */
/*               |      Output structure members are the following.         */
/*               |          1. stMainBlockInfo.u1BlockNo                    */
/*               |          2. stMainBlockInfo.u1BlockStatus                */
/*               |          3. stSubBlockInfo.u1BlockNo                     */
/*               |          4. stSubBlockInfo.u1BlockStatus                 */
/*               | FreeSpaceInfoPtr : An output value.                      */
/*               |      Only when the return value is FEE_EXT_E_FRSP_OK,    */
/*               |      this function updates this value.                   */
/*               |      Output structure members are the following.         */
/*               |          1. Result ( 8-bit patterns )                    */
/*               |              FEE_EXT_FRSP_RESULT_PENDING_RBLD            */
/*               |              FEE_EXT_FRSP_RESULT_BLANK                   */
/*               |              FEE_EXT_FRSP_RESULT_AREAINFO_INCONSISTENT   */
/*               |            ( FEE_EXT_FRSP_RESULT_PENDING_RBLD |          */
/*               |              FEE_EXT_FRSP_RESULT_AREAINFO_INCONSISTENT ) */
/*               |          2. RcrdNum                                      */
/*               |          3. DataAreaByte                                 */
/* Return Value  | FEE_EXT_E_FRSP_OK                                        */
/*               | FEE_EXT_E_FRSP_AREA_FAULT                                */
/*               | FEE_EXT_E_FRSP_BUSY                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_FreeSpace_CheckBS(
    uint8  AreaNo,
    P2VAR( Fee_LwpInfType,           AUTOMATIC, TYPEDEF ) LastWritePosInfo,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
){
    Fee_ExtFreeSpaceReturnType Rtn;
    uint32                     SrchBSOnFlashRtn;
    uint32                     RcrdDataAreaStartAddr;
    uint8                      MainBlockStatus;
    boolean                    NeedsToFixBS;

    SrchBSOnFlashRtn = FEE_STATUS_OK;
    NeedsToFixBS = FALSE;
    if(( LastWritePosInfo->stMainBlockInfo.u1BlockStatus == FEE_BS_INVALID )
    || ( LastWritePosInfo->stSubBlockInfo.u1BlockStatus  == FEE_BS_INVALID ))
    {
        SrchBSOnFlashRtn = Fee_FreeSpace_CheckBSOnFlash( AreaNo, LastWritePosInfo, &NeedsToFixBS );
    }

    if( SrchBSOnFlashRtn == FEE_STATUS_OK )
    {
        MainBlockStatus = LastWritePosInfo->stMainBlockInfo.u1BlockStatus;
        if( MainBlockStatus == FEE_BS_USING )
        {
            Rtn = FEE_EXT_E_FRSP_OK;
        }
        else if( MainBlockStatus == FEE_BS_MOVE )
        {
            FreeSpaceInfoPtr->Result       |= (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_PENDING_RBLD;
            FreeSpaceInfoPtr->RcrdNum       = FEE_FREESPACE_MNGRCRD_NOSPACE;
            FreeSpaceInfoPtr->DataAreaByte  = FEE_FREESPACE_DATBYTE_NOSPACE;
            Rtn = FEE_EXT_E_FRSP_OK;
        }
        else /* MainBlockStatus == FEE_BS_USED, FEE_BS_UNUSED, FEE_BS_ILLEGAL */
        {
            Rtn = FEE_EXT_E_FRSP_AREA_FAULT;
        }
    }
    else if( SrchBSOnFlashRtn == FEE_STATUS_NODATA )
    {
        RcrdDataAreaStartAddr = Fee_AreaInfTBL[AreaNo].u2RcrdDataAreaStartAddr;

        FreeSpaceInfoPtr->Result       |= (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_BLANK;
        FreeSpaceInfoPtr->RcrdNum       = (uint16)(( RcrdDataAreaStartAddr - (uint32)FEE_STARTRECORDPOS ) / (uint32)FEE_RECORDMNGINFOLEN );
        FreeSpaceInfoPtr->DataAreaByte  = (uint32)FEE_DATA_FLASH_SECTOR_SIZE - RcrdDataAreaStartAddr;
        Rtn = FEE_EXT_E_FRSP_OK;
    }
    else if( SrchBSOnFlashRtn == FEE_STATUS_BUSY )
    {
        Rtn = FEE_EXT_E_FRSP_BUSY;
    }
    else /* SrchBSOnFlashRtn == FEE_STATUS_NG */
    {
        Rtn = FEE_EXT_E_FRSP_AREA_FAULT;
    }

    if( Rtn == (Fee_ExtFreeSpaceReturnType)FEE_EXT_E_FRSP_OK )
    {
        if( NeedsToFixBS == (boolean)TRUE )
        {
            FreeSpaceInfoPtr->Result |= (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_AREAINFO_INCONSISTENT;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FreeSpace_CheckBSOnFlash                             */
/* Description   | Function to check BS on the data flash.                  */
/* Preconditions | FEE is idling.                                           */
/* Parameters    | AreaNo                                                   */
/*               | LastWritePosInfo : An output value.                      */
/*               |      Only when the return value is FEE_STATUS_OK,        */
/*               |      this function updates this value.                   */
/*               |      Output structure members are the following.         */
/*               |          1. stMainBlockInfo.u1BlockNo                    */
/*               |          2. stMainBlockInfo.u1BlockStatus                */
/*               |          3. stSubBlockInfo.u1BlockNo                     */
/*               |          4. stSubBlockInfo.u1BlockStatus                 */
/*               | NeedsToFixBS     : An output value.                      */
/*               |      If FEE needs to fix, this value is set TRUE,        */
/*               |      otherwise this value is set FALSE.                  */
/* Return Value  | FEE_STATUS_OK     : BS has been correct status.          */
/*               | FEE_STATUS_NG     : BS has been faulty status.           */
/*               | FEE_STATUS_NODATA : BS, all of the sectors in the area,  */
/*               |                     has been blank.                      */
/*               | FEE_STATUS_BUSY   : FEE has not been idling.             */
/*               |                     Check has been failure.              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_FreeSpace_CheckBSOnFlash(
    uint8  AreaNo,
    P2VAR( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) LastWritePosInfo,
    P2VAR( boolean,        AUTOMATIC, TYPEDEF ) NeedsToFixBS
){
    uint32 Rtn = FEE_STATUS_BUSY;
    Std_ReturnType u1_dfPrepare;

    (*NeedsToFixBS) = FALSE;
    if( Fee_CpuDtfInfo.u1ProcessStatus == FEE_STATUSIDLE )
    {
        /* Preparing for MemAcc data flash access. */
        u1_dfPrepare = Fee_FlsWrp_ExtDfPreExecution();
        if( u1_dfPrepare == (Std_ReturnType)E_OK )
        {
            Fee_InitCpuDtfData( &Fee_CpuDtfInfo );
            Fee_CpuDtfInfo.u1AreaNum = AreaNo;
            Fee_SelectUseArea( &Fee_CpuDtfInfo );
    
            Rtn = Fee_Block_GetSectorInfo( &Fee_CpuDtfInfo, NeedsToFixBS );
            if( Rtn == FEE_STATUS_OK )
            {
                LastWritePosInfo->stMainBlockInfo.u1BlockNo     = Fee_CpuDtfInfo.u1MainBlockNo;
                LastWritePosInfo->stMainBlockInfo.u1BlockStatus = Fee_CpuDtfInfo.u1MainBlockStatus;
                LastWritePosInfo->stSubBlockInfo.u1BlockNo      = Fee_CpuDtfInfo.u1SubBlockNo;
                LastWritePosInfo->stSubBlockInfo.u1BlockStatus  = Fee_CpuDtfInfo.u1SubBlockStatus;
            }
            else /* Rtn == FEE_STATUS_NG, FEE_STATUS_NODATA */
            {
                /* No process. */
            }
    
            Fee_InitCpuDtfData( &Fee_CpuDtfInfo );
            Fee_Lib_SetCpuDtfDataSub();
            Fee_Block_SetUseBlockInfoSub();
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FreeSpace_GetFreeSpaceMngArea                        */
/* Description   | Function to get a free space information of a management */
/*               | area.                                                    */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo                                                   */
/*               | LimitSearchMngArea                                       */
/*               | LastWritePosInfo : An input and output value.            */
/*               |      Input structure members are the following.          */
/*               |          1. stMainBlockInfo.u1BlockNo                    */
/*               |          2. u4WriteLastRecMngAbsAddr                     */
/*               |      Output structure members are the following.         */
/*               |          1. u4WriteLastRecMngAbsAddr                     */
/*               | FreeSpaceInfoPtr : An output value.                      */
/*               |      Only when the return value is FEE_EXT_E_FRSP_OK,    */
/*               |      this function updates this value.                   */
/*               |      Output structure members are the following.         */
/*               |          1. Result                                       */
/*               |                  FEE_EXT_FRSP_RESULT_MNG_OVER_LIMIT      */
/*               |          2. RcrdNum                                      */
/* Return Value  | FEE_EXT_E_FRSP_OK                                        */
/*               | FEE_EXT_E_FRSP_BUSY                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_FreeSpace_GetFreeSpaceMngArea(
    uint8  AreaNo,
    uint16 LimitSearchMngArea,
    P2VAR( Fee_LwpInfType,           AUTOMATIC, TYPEDEF ) LastWritePosInfo,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
){
    uint32                     RcrdDataAreaStartAbsAddr;
    uint32                     SrchMngAreaOnFlashRtn;
    uint32                     FreeSpaceStartAddr;
    uint32                     SearchNum;
    Fee_ExtFreeSpaceReturnType Rtn;

    SrchMngAreaOnFlashRtn = FEE_STATUS_OK;
    if( LastWritePosInfo->u4WriteLastRecMngAbsAddr == FEE_ADDRESS_INVALID )
    {
        SearchNum = ( (uint32)LimitSearchMngArea * (uint32)FEE_RECORDMNGINFOLEN ) / (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE;
        SrchMngAreaOnFlashRtn = Fee_FreeSpace_SrchMngAreaOnFlash( AreaNo, SearchNum, LastWritePosInfo );
    }

    if( SrchMngAreaOnFlashRtn == FEE_STATUS_OK )
    {
        RcrdDataAreaStartAbsAddr = FEE_BLKSTARTADDRTBL[LastWritePosInfo->stMainBlockInfo.u1BlockNo] + (uint32)( Fee_AreaInfTBL[AreaNo].u2RcrdDataAreaStartAddr );
        FreeSpaceStartAddr = LastWritePosInfo->u4WriteLastRecMngAbsAddr + (uint32)FEE_RECORDMNGINFOLEN;
        FreeSpaceInfoPtr->RcrdNum = (uint16)(( RcrdDataAreaStartAbsAddr - FreeSpaceStartAddr ) / (uint32)FEE_RECORDMNGINFOLEN );
        Rtn = FEE_EXT_E_FRSP_OK;
    }
    else if( SrchMngAreaOnFlashRtn == FEE_STATUS_NG )
    {
        FreeSpaceInfoPtr->Result |= (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_MNG_OVER_LIMIT;
        FreeSpaceInfoPtr->RcrdNum = LimitSearchMngArea;
        Rtn = FEE_EXT_E_FRSP_OK;
    }
    else /* SrchMngAreaOnFlashRtn == FEE_STATUS_BUSY */
    {
        Rtn = FEE_EXT_E_FRSP_BUSY;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FreeSpace_SrchMngAreaOnFlash                         */
/* Description   | Function to search a management area on a data flash     */
/*               | for a last record position.                              */
/* Preconditions | FEE is idling.                                           */
/* Parameters    | AreaNo                                                   */
/*               | SearchNum                                                */
/*               | LastWritePosInfo : An input and output value.            */
/*               |      Only when the return value is FEE_STATUS_OK,        */
/*               |      this function updates this value.                   */
/*               |      Input structure members are the following.          */
/*               |          1. stMainBlockInfo.u1BlockNo                    */
/*               |      Output structure members are the following.         */
/*               |          1. u4WriteLastRecMngAbsAddr                     */
/* Return Value  | FEE_STATUS_OK   : The last record has been found.        */
/*               | FEE_STATUS_NG   : This function searched to the limit    */
/*               |                   and not found a last record.           */
/*               | FEE_STATUS_BUSY : FEE has not been idling.               */
/*               |                   Search has been failure.               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_FreeSpace_SrchMngAreaOnFlash(
    uint8  AreaNo,
    uint32 SearchNum,
    P2VAR( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) LastWritePosInfo
){
    uint32 Rtn;
    uint32 BCStartTailAddress;
    uint32 BCEndTopAddress;
    uint32 BCResult;
    uint32 NotBlankAddr;
    uint8  MainSectorNum;
    Std_ReturnType u1_dfPrepare;

    Rtn = FEE_STATUS_BUSY;
    if( Fee_CpuDtfInfo.u1ProcessStatus == FEE_STATUSIDLE )
    {
        /* Preparing for MemAcc data flash access. */
        u1_dfPrepare = Fee_FlsWrp_ExtDfPreExecution();
        if( u1_dfPrepare == (Std_ReturnType)E_OK )
        {
            /* Preparing for blankcheck on the data flash. */
            Fee_Dfc_End();

            /* Executing blank check. */
            MainSectorNum = LastWritePosInfo->stMainBlockInfo.u1BlockNo;
            BCStartTailAddress = FEE_BLKSTARTADDRTBL[MainSectorNum] + (uint32)( Fee_AreaInfTBL[AreaNo].u2RcrdDataAreaStartAddr );
            BCEndTopAddress    = FEE_BLKSTARTADDRTBL[MainSectorNum] + FEE_STARTRECORDPOS;

            Fee_Dfc_BlankCheck( BCStartTailAddress, BCEndTopAddress, SearchNum );

            /* Checking a result and setting output values. */
            NotBlankAddr = FEE_ADDRESS_INVALID;
            BCResult = Fee_Dfc_GetBlankCheckResult( &NotBlankAddr );
            if( BCResult == FEE_DFC_STATUS_BUSY ) /* The part of a management area is blank. */
            {
                Rtn = FEE_STATUS_NG;
            }
            else if( BCResult == FEE_DFC_STATUS_ERROR ) /* A management area is not blank. */
            {
                LastWritePosInfo->u4WriteLastRecMngAbsAddr = NotBlankAddr
                                                                - ( ( NotBlankAddr - BCEndTopAddress ) % (uint32)FEE_RECORDMNGINFOLEN );
                Rtn = FEE_STATUS_OK;
            }
            else /* BCResult == FEE_DFC_STATUS_OK, A management area is blank. */
            {
                LastWritePosInfo->u4WriteLastRecMngAbsAddr = BCEndTopAddress - (uint32)FEE_RECORDMNGINFOLEN;
                Rtn = FEE_STATUS_OK;
            }

            /* Post process for blankcheck on the data flash. */
            Fee_Dfc_End();
            Fee_Dfc_SetRAMSub();
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FreeSpace_GetFreeSpaceDatArea                        */
/* Description   | Function to get a free space information of a data       */
/*               | area.                                                    */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo                                                   */
/*               | LimitSearchDataArea                                      */
/*               | LastWritePosInfo : An input and output value.            */
/*               |      Input structure members are the following.          */
/*               |          1. stMainBlockInfo.u1BlockNo                    */
/*               |          2. u4WriteLastRecDatAbsAddr                     */
/*               |      Output structure members are the following.         */
/*               |          1. u4WriteLastRecDatAbsAddr                     */
/*               | FreeSpaceInfoPtr : An output value.                      */
/*               |      Only when the return value is FEE_EXT_E_FRSP_OK,    */
/*               |      this function updates this value.                   */
/*               |      Output structure members are the following.         */
/*               |          1. Result                                       */
/*               |                  FEE_EXT_FRSP_RESULT_DATA_OVER_LIMIT     */
/*               |          2. DataAreaByte                                 */
/* Return Value  | FEE_EXT_E_FRSP_OK                                        */
/*               | FEE_EXT_E_FRSP_BUSY                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_FreeSpace_GetFreeSpaceDatArea(
    uint8  AreaNo,
    uint32 LimitSearchDataArea,
    P2VAR( Fee_LwpInfType,           AUTOMATIC, TYPEDEF ) LastWritePosInfo,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
){
    uint32                     NextSectorStartAbsAddr;
    uint32                     SrchDatAreaOnFlashRtn;
    uint32                     FreeSpaceStartAddr;
    uint32                     SearchNum;
    Fee_ExtFreeSpaceReturnType Rtn;

    SrchDatAreaOnFlashRtn = FEE_STATUS_OK;
    if( LastWritePosInfo->u4WriteLastRecDatAbsAddr == FEE_ADDRESS_INVALID )
    {
        /* This function calculates the number of blankcheck in the following IF statements. */
        /* Blankcheck is executed every an ECC FIX SIZE. */
        /* So this function rounds up LimitSearchDataArea with a ECC FIX SIZE. */
        /* Note, however, that if LimitSearchDataArea is the max value 0xFFFFFFFF, this calculation is arithmetic overflow. */
        /* So if LimitSearchDataArea is bigger than FEE_DATA_FLASH_SECTOR_SIZE, this function sets a fixed size to the number of blankcheck. */
        if( LimitSearchDataArea > (uint32)FEE_DATA_FLASH_SECTOR_SIZE )
        {
            SearchNum = FEE_FREESPACE_MAX_NUM_OF_BC_DATAAREA;
        }
        else
        {
            SearchNum = ( LimitSearchDataArea + FEE_FREESPACE_ROUNDUP_VAL_ECC_FIX_SIZE ) / (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE;
        }
        SrchDatAreaOnFlashRtn = Fee_FreeSpace_SrchDatAreaOnFlash( AreaNo, SearchNum, LastWritePosInfo );
    }

    if( SrchDatAreaOnFlashRtn == FEE_STATUS_OK )
    {
        NextSectorStartAbsAddr = FEE_BLKSTARTADDRTBL[LastWritePosInfo->stMainBlockInfo.u1BlockNo] + (uint32)FEE_DATA_FLASH_SECTOR_SIZE;
        FreeSpaceStartAddr = LastWritePosInfo->u4WriteLastRecDatAbsAddr + (uint32)FEE_DATAAREA_REC_TAIL_OFFSET;
        FreeSpaceInfoPtr->DataAreaByte = NextSectorStartAbsAddr - FreeSpaceStartAddr;
        Rtn = FEE_EXT_E_FRSP_OK;
    }
    else if( SrchDatAreaOnFlashRtn == FEE_STATUS_NG )
    {
        FreeSpaceInfoPtr->Result |= (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_DATA_OVER_LIMIT;
        FreeSpaceInfoPtr->DataAreaByte = SearchNum * (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE;
        Rtn = FEE_EXT_E_FRSP_OK;
    }
    else /* SrchDatAreaOnFlashRtn == FEE_STATUS_BUSY */
    {
        Rtn = FEE_EXT_E_FRSP_BUSY;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FreeSpace_SrchDatAreaOnFlash                         */
/* Description   | Function to search a data area on a data flash           */
/*               | for a last record position.                              */
/* Preconditions | FEE is idling.                                           */
/* Parameters    | AreaNo                                                   */
/*               | SearchNum                                                */
/*               | LastWritePosInfo : An input and output value.            */
/*               |      Only when the return value is FEE_STATUS_OK,        */
/*               |      this function updates this value.                   */
/*               |      Input structure members are the following.          */
/*               |          1. stMainBlockInfo.u1BlockNo                    */
/*               |      Output structure members are the following.         */
/*               |          1. u4WriteLastRecDatAbsAddr                     */
/* Return Value  | FEE_STATUS_OK   : The last record has been found.        */
/*               | FEE_STATUS_NG   : This function searched to the limit    */
/*               |                   and not found a last record.           */
/*               | FEE_STATUS_BUSY : FEE has not been idling.               */
/*               |                   Search has been failure.               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_FreeSpace_SrchDatAreaOnFlash(
    uint8  AreaNo,
    uint32 SearchNum,
    P2VAR( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) LastWritePosInfo
){
    uint32 Rtn;
    uint32 BCStartTailAddress;
    uint32 BCEndTopAddress;
    uint32 BCResult;
    uint32 NotBlankAddr;
    uint8  MainSectorNum;
    Std_ReturnType u1_dfPrepare;

    Rtn = FEE_STATUS_BUSY;
    if( Fee_CpuDtfInfo.u1ProcessStatus == FEE_STATUSIDLE )
    {
        /* Preparing for MemAcc data flash access. */
        u1_dfPrepare = Fee_FlsWrp_ExtDfPreExecution();
        if( u1_dfPrepare == (Std_ReturnType)E_OK )
        {
            /* Preparing for blankcheck on the data flash. */
            Fee_Dfc_End();

            /* Executing blank check. */
            MainSectorNum = LastWritePosInfo->stMainBlockInfo.u1BlockNo;
            BCStartTailAddress = FEE_BLKSTARTADDRTBL[MainSectorNum] + (uint32)FEE_DATA_FLASH_SECTOR_SIZE;
            BCEndTopAddress    = FEE_BLKSTARTADDRTBL[MainSectorNum] + (uint32)( Fee_AreaInfTBL[AreaNo].u2RcrdDataAreaStartAddr );

            Fee_Dfc_BlankCheck( BCStartTailAddress, BCEndTopAddress, SearchNum );

            /* Checking a result and setting output values. */
            NotBlankAddr = FEE_ADDRESS_INVALID;
            BCResult = Fee_Dfc_GetBlankCheckResult( &NotBlankAddr );
            if( BCResult == FEE_DFC_STATUS_BUSY ) /* The part of a management area is blank. */
            {
                Rtn = FEE_STATUS_NG;
            }
            else if( BCResult == FEE_DFC_STATUS_ERROR ) /* A management area is not blank. */
            {
                LastWritePosInfo->u4WriteLastRecDatAbsAddr = ( NotBlankAddr + (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE ) - (uint32)FEE_DATAAREA_REC_TAIL_OFFSET;
                Rtn = FEE_STATUS_OK;
            }
            else /* BCResult == FEE_DFC_STATUS_OK, A management area is blank. */
            {
                LastWritePosInfo->u4WriteLastRecDatAbsAddr = BCEndTopAddress - (uint32)FEE_DATAAREA_REC_TAIL_OFFSET;
                Rtn = FEE_STATUS_OK;
            }

            /* Post process for blankcheck on the data flash. */
            Fee_Dfc_End();
            Fee_Dfc_SetRAMSub();
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_FreeSpace_ClearLastWritePos                          */
/* Description   | Function to clear last record positions                  */
/*               | in a formal argument.                                    */
/* Preconditions | None                                                     */
/* Parameters    | LastWritePosInfo                                         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_FreeSpace_ClearLastWritePos(
    P2VAR( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) LastWritePosInfo
){
    LastWritePosInfo->stMainBlockInfo.u1BlockNo      = FEE_BLOCKNUM_INVALID;
    LastWritePosInfo->stMainBlockInfo.u1BlockStatus  = FEE_BS_INVALID;
    LastWritePosInfo->stSubBlockInfo.u1BlockNo       = FEE_BLOCKNUM_INVALID;
    LastWritePosInfo->stSubBlockInfo.u1BlockStatus   = FEE_BS_INVALID;
    LastWritePosInfo->u1SetKind                      = FEE_LWPKIND_INIT;
    LastWritePosInfo->u4WriteLastRecMngAbsAddr       = FEE_ADDRESS_INVALID;
    LastWritePosInfo->u4WriteLastRecDatAbsAddr       = FEE_ADDRESS_INVALID;

    return;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/10/16                                              */
/*  2-0-0          :2022/08/24                                              */
/*  2-1-0          :2024/09/04                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
