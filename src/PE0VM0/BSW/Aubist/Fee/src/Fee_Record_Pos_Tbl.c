/* Fee_Record_Pos_Tbl.c v2-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/RECORD/POS/TBL/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Mpu_Const.h"
#include "../inc/Fee_Mpu_Dev_Const.h"

#include "../inc/Fee_Record_Pos_Tbl.h"
#include "../inc/Fee_Ram.h"
#include "../inc/Fee_Record_Pos_Tbl_Internal.h"
#include "../inc/Fee_Legacy.h"
#include "../inc/Fee_Pif.h"
#include "../inc/Fee_Lib.h"
#include "../inc/Fee_DfcMpu.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)
/* Valid record position TBL valid flag */
#define FEE_RPTBLFIXED          ((uint8)0x03U)      /* TBL Created */
#define FEE_RPTBLERASED         ((uint8)0x0CU)      /* TBL not created */
#define FEE_RPTBLMAKING         ((uint8)0x30U)      /* Creating TBL */

/* Valid record position TBL valid flag (mirror) */
#define FEE_RPTBL_MRR_FIXED         ((uint8)0xFCU)         /* TBL Created (Mirror) */
#define FEE_RPTBL_MRR_ERASED        ((uint8)0xF3U)        /* TBL not created (mirror) */
#define FEE_RPTBL_MRR_MAKING        ((uint8)0xCFU)        /* Creating TBL (Mirror) */

#define FEE_RPTBL_VALID_FLAG_COMPARE_MATCH    ((uint8)0xFFU)    /* TBL creation status match judgment */

/* Valid record position TBL status */
#define FEE_RPSTATUS_VALID      ((uint32)0x00000000UL)  /* TBL enabled */
#define FEE_RPSTATUS_INVALID    ((uint32)0x00000001UL)  /* TBL disabled */
#define FEE_RPSTATUS_ERROR      ((uint32)0x00000002UL)  /* TBL abnormal condition */

#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#if ( FEE_RECORDPOSTBL_ENABLE == STD_ON )

VAR( uint32, FEE_VAR_NO_INIT ) Fee_TBLMakeSrcAddress;
VAR( uint32, FEE_VAR_NO_INIT ) Fee_TBLMakeSrcAddressMrr;

#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */

#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_RecordPosTbl_ClearPosArea                            */
/* Description   | Effective record position TBL initializatio              */
/* Preconditions | None                                                     */
/* Parameters    | uint8u1AreaNum : Number of the area to be initialized    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_RecordPosTbl_ClearPosArea(
    uint8 u1AreaNum
){
#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)
    uint16          u2tTableIndex;                      /* TBL Index */
    uint16          u2tInitDataSize;                    /* Initialization size */

    /* Valid record position TBL valid flag set to "not created" */
    Fee_RecordPosTBLValidFlag[u1AreaNum] = FEE_RPTBLERASED;
    Fee_RecordPosTBLValidFlagMrr[u1AreaNum] = FEE_RPTBL_MRR_ERASED;
    
    /* Get index of argument area head ID */
    u2tTableIndex = Fee_OffsetPos[u1AreaNum];
    /* Get the number of DATA-IDs in the argument area */
    u2tInitDataSize = Fee_AreaInfTBL[u1AreaNum].u2UseDataIdNum;
    
    /* MAIN INITIALIZATION */
    Fee_RecordPosTbl_SetMemoryU2( &Fee_RecordPosTBL[u2tTableIndex],    FEE_IDNONE,      u2tInitDataSize );
    /* Sub Initialization */
    Fee_RecordPosTbl_SetMemoryU2( &Fee_RecordPosTBLMrr[u2tTableIndex], FEE_ID_MRR_NONE, u2tInitDataSize );

    /* TBL Create Search Address Initialization */
    Fee_TBLMakeSrcAddress    = FEE_ADDRESS_INVALID;
    Fee_TBLMakeSrcAddressMrr = (uint32)(~Fee_TBLMakeSrcAddress);
#endif /* FEE_RECORDPOSTBL_ENABLE == ON */

    return;
}

/****************************************************************************/
/* Function Name | Fee_RecordPosTbl_ClearPosAll                             */
/* Description   | All area valid record position TBL initializing process  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_RecordPosTbl_ClearPosAll( void )
{
#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)

    uint8 AreaCounter;
    uint8 TotalAreaNum;

    TotalAreaNum = Fee_AreaNumber;

    for ( AreaCounter = 0U; AreaCounter < TotalAreaNum; AreaCounter++ )
    {
        Fee_RecordPosTbl_ClearPosArea( AreaCounter );
    }

    return;

#else
    return;
#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */
}

/****************************************************************************/
/* Function Name | Fee_RecordPosTbl_ReadyPosArea                            */
/* Description   | Function to get ready to use a record position table.    */
/*               | READY means checking status of a record                  */
/*               | position table and making a record position table        */
/*               | as necessary.                                            */
/* Preconditions | None                                                     */
/* Parameters    | u1AreaNum                                                */
/*               | u1BlockNum                                               */
/*               | u4SrchAddress                                            */
/* Return Value  | The activation result.                                   */
/*               |      FEE_STATUS_OK   : To activate a table has been      */
/*               |                        finished successfully.            */
/*               |      FEE_STATUS_NG   : To activate a table was failure.  */
/*               |                        RECORDPOSTBL is disabled.         */
/*               |      FEE_STATUS_BUSY : To activate a table has not been  */
/*               |                        finished yet.                     */
/* Notes         | 1. Only when FEE_RECORDPOSTBL_ENABLE is STD_ON,          */
/*               |    FEE_STATUS_OK/BUSY are returned.                      */
/*               | 2. Only when FEE_RECORDPOSTBL_ENABLE is STD_OFF,         */
/*               |    FEE_STATUS_NG is returned.                            */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_RecordPosTbl_ReadyPosArea(
    uint8 u1AreaNum,
    uint8 u1BlockNum,
    uint32 u4SrchAddress
){
    uint32          u4tReturn;                          /* RETURN */
#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)
    uint32          u4tValidityResult;                  /* Validity check result */
    uint32          u4tMakeRecordPosTblResult;          /* Result of creating effective record position TBL */

    /* Validity check of valid record position TBL */
    u4tValidityResult = Fee_RecordPosTbl_GetStatusArea( u1AreaNum );
    if ( u4tValidityResult == FEE_RPSTATUS_VALID )
    {
        /* No need to create valid record position TBL when valid record position TBL is "enabled" */
        u4tReturn = FEE_STATUS_OK;
    }
    else
    {
        if( u4tValidityResult == FEE_RPSTATUS_INVALID )
        {
            /* If valid record position TBL is "invalid," valid record position TBL creation */
            u4tMakeRecordPosTblResult = Fee_RecordPosTbl_MakePosArea( u1AreaNum, u1BlockNum, u4SrchAddress );
        }
        else
        {
            /* If effective record position TBL is "abnormal," create by initializing effective record position TBL */
            Fee_RecordPosTbl_ClearPosArea( u1AreaNum );
            u4tMakeRecordPosTblResult = Fee_RecordPosTbl_MakePosArea( u1AreaNum, u1BlockNum, u4SrchAddress );
        }

        /* When effective record position TBL creation is completed */
        if ( u4tMakeRecordPosTblResult == FEE_STATUS_OK )
        {
            u4tReturn = FEE_STATUS_OK;
        }
        /* If valid record position TBL creation is not completed */
        else
        {
            u4tReturn = FEE_STATUS_BUSY;
        }
    }

#else /* FEE_RECORDPOSTBL_ENABLE == STD_OFF */
    u4tReturn = FEE_STATUS_NG;
#endif/* FEE_RECORDPOSTBL_ENABLE == *** */

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_RecordPosTbl_GetPos                                  */
/* Description   | Function to get a record position from a record          */
/*               | position table.                                          */
/* Preconditions | None                                                     */
/* Parameters    | u1AreaNum                                                */
/*               | u2DataNum                                                */
/*               | ptu2RecordPos : Output argument. A record position.      */
/* Return Value  | The result of getting a record position.                 */
/*               |  FEE_STATUS_OK     : A record position is registered.    */
/*               |  FEE_STATUS_NODATA : A record position is unregistered.  */
/*               |  FEE_STATUS_NG     : A record position data is broken.   */
/*               |                    Or This function has been turned off. */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_RecordPosTbl_GetPos(
    uint8 u1AreaNum,
    uint16 u2DataNum,
    P2VAR(uint16, AUTOMATIC, TYPEDEF) ptu2RecordPos
){
#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)
    uint32          u4tReturn;                          /* RETURN */
    uint16          u2tTableIndex;                      /* TBL Index */
    uint16          u2tRecordPos;                       /* Effective record position */
    uint16          u2tRecordPosMrr;                    /* Effective record position (mirror) */
    Std_ReturnType  GetTblIdxResult;
    
    u4tReturn = FEE_STATUS_NG;

    /* Calculate TBL Index */
    GetTblIdxResult = Fee_RecordPosTbl_GetTblIdx( u1AreaNum, u2DataNum, &u2tTableIndex );

    if ( GetTblIdxResult == (Std_ReturnType)E_OK )
    {
        /* Get valid record position */
        u2tRecordPos    = Fee_RecordPosTBL[u2tTableIndex];
        u2tRecordPosMrr = Fee_RecordPosTBLMrr[u2tTableIndex];
        /* Match the retrieved data */
        if ( u2tRecordPos == (uint16)(~u2tRecordPosMrr) )
        {
            /* Check if the acquired data is not registered (if not registered, return no data) */
            if ( u2tRecordPos != FEE_IDNONE )
            {
                u4tReturn = FEE_STATUS_OK;
                *ptu2RecordPos = u2tRecordPos;
            }
            else
            {
                u4tReturn = FEE_STATUS_NODATA;
            }
        }
    }

    return u4tReturn;
#else /* FEE_RECORDPOSTBL_ENABLE == STD_OFF */
    return FEE_STATUS_NG;
#endif /* FEE_RECORDPOSTBL_ENABLE */
}

/****************************************************************************/
/* Function Name | Fee_RecordPosTbl_SetPos                                  */
/* Description   | Valid record position setting                            */
/* Preconditions | None                                                     */
/* Parameters    | u1AreaNum: area number                                   */
/*               | u2DataNum : ID #                                         */
/*               | u2RecordPos: Valid record position                       */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_RecordPosTbl_SetPos(
    uint8 u1AreaNum,
    uint16 u2DataNum,
    uint16 u2RecordPos
){
#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)
    uint16          u2tTableIndex;                      /* TBL Index */
    Std_ReturnType  GetTblIdxResult;

    /* Calculate TBL Index */
    GetTblIdxResult = Fee_RecordPosTbl_GetTblIdx( u1AreaNum, u2DataNum, &u2tTableIndex );

    if ( GetTblIdxResult == (Std_ReturnType)E_OK )
    {
        /* Set to effective record position TBL */
        Fee_RecordPosTBL[u2tTableIndex]    = u2RecordPos;
        Fee_RecordPosTBLMrr[u2tTableIndex] = (uint16)(~u2RecordPos);
    }
#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */

    return;
}

#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Fee_RecordPosTbl_MakePosArea                             */
/* Description   | Effective record position TBL creation                   */
/* Preconditions | None                                                     */
/* Parameters    | u1AreaNum     : area number                              */
/*               | u1BlockNum    : block number number                      */
/*               | u4SrchAddress : Search address                           */
/*               | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |               MHA management data                        */
/* Return Value  | Result of creating valid record position TBL             */
/*               | 0x00000000 : FEE_STATUS_OK : Creation completed          */
/*               | 0x00000001 : FEE_STATUS_N G: Not created                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_RecordPosTbl_MakePosArea(
    uint8 u1AreaNum,
    uint8 u1BlockNum,
    uint32 u4SrchAddress
){
    uint32          u4tReturn;                          /* RETURN */
    uint32          u4tSearchEndAddress;                /* Search end address */
    uint32          u4tGetRecordPosResult;              /* Result of obtaining effective record position */
    uint32          u4tLocalSrchAddress;                /* Search address */
    uint32          SrchRemainCount;                    /* searchable */
    uint16          u2tDataNum;                         /* ID # */
    uint16          u2tRecordPos;                       /* Effective record position */
    uint8           u1tValidFlag;                       /* Valid flag */
    uint8           u1tCompareResult;                   /* result of comparision of Write-CHECK */

    /* Load into local variables (register variables) */
    SrchRemainCount = Fee_CpuDtfInfo.u4SrchRemainCount;
    u4tReturn = FEE_STATUS_NG;

    /* Calculate block first record address */
    u4tSearchEndAddress = FEE_BLKSTARTADDRTBL[u1BlockNum] + FEE_STARTRECORDPOS;

    /* if valid record position TBL valid flag is "creating" */
    u1tValidFlag = Fee_RecordPosTBLValidFlag[u1AreaNum];

    if ( u1tValidFlag == FEE_RPTBLMAKING )
    {
        if(( Fee_TBLMakeSrcAddress ^ Fee_TBLMakeSrcAddressMrr ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
        {
            /* Set the last search address from the last interruption as the starting address for this search */
            u4tLocalSrchAddress = Fee_TBLMakeSrcAddress;
        }
        else
        {
            /* Note : This case is that Fee_TBLMakeSrcAddress has become garbled.                       */
            /*        So this function resets an address of initiating a search to u4SrchAddress.       */
            /*        However this function does not initialize record position data,                   */
            /*        because it checks that the latest position data has already been set using        */
            /*        Fee_RecordPosTbl_GetPos().                                                        */
            u4tLocalSrchAddress = u4SrchAddress;
        }
    }
    else
    {
        /* Valid record position TBL enable flag set to "creating" */
        Fee_RecordPosTBLValidFlag[u1AreaNum] = FEE_RPTBLMAKING;
        Fee_RecordPosTBLValidFlagMrr[u1AreaNum] = FEE_RPTBL_MRR_MAKING;

        /* Set search address to "Trailing record address" */
        u4tLocalSrchAddress = u4SrchAddress;
    }
    
    /* Loop from the search start address to the block head record address and below while decrementing by record length */
    while ( ( u4tSearchEndAddress <= u4tLocalSrchAddress )
                && ( (uint32)FEE_SRCH_REMAIN_COUNT_ZERO <  SrchRemainCount ) )
    {
        /* Decrement searchable count */
        SrchRemainCount--;
        
        /* Check Write-CHECK. */
        u1tCompareResult = Fee_DfcMpu_SyncCompare_EccFixSize( ( u4tLocalSrchAddress + (uint32)FEE_WRITECHECKPOS ), &Fee_FixWCData[0] );
        if ( u1tCompareResult == FEE_DFCMPU_RESULT_OK )
        {
            /* In case of Write-CHECK is valid. */
            /* Return value is not checked. */
#if ( FEE_RECORD_FORMAT_OFFSET_ID != 0U )
        (void)Fee_DfcMpu_SyncReadUint16( ( u4tLocalSrchAddress + FEE_RECORD_FORMAT_OFFSET_ID ), &u2tDataNum );
#else
        (void)Fee_DfcMpu_SyncReadUint16( u4tLocalSrchAddress, &u2tDataNum );
#endif
            /* Get effective record position */
            u4tGetRecordPosResult = Fee_RecordPosTbl_GetPos( u1AreaNum, u2tDataNum, &u2tRecordPos );
            if ( u4tGetRecordPosResult == FEE_STATUS_NODATA )
            {
                /* Set valid record position if valid record position failed */
                Fee_RecordPosTbl_SetPos( u1AreaNum, u2tDataNum, 
                                            (uint16)( ( u4tLocalSrchAddress - u4tSearchEndAddress ) / (uint32)FEE_RECORDMNGINFOLEN ) );
            }
            else /* u4tGetRecordPosResult == FEE_STATUS_OK, FEE_STATUS_NG */
            {
                /* No process. This reason is below.                                            */
                /*      If FEE_STATUS_OK was returned, the latest data has already been set.    */
                /*      If FEE_STATUS_NG was returned, the record position has been broken.     */
                /*      In this case, this function doesn't change its position and             */
                /*      restoration activity will be executed when its position will be gotten.   */
            }
        }
        else
        {
            /* No process, in case of Write-CHECK error */
        }
        
        /* decrement search address by record length */
        u4tLocalSrchAddress -= (uint32)FEE_RECORDMNGINFOLEN;
    }
    

    /* Write back search address */
    if ( u4tSearchEndAddress > u4tLocalSrchAddress )
    {
        /* When searching all records */
        /* Initialize TBL creation search address */
        Fee_TBLMakeSrcAddress = FEE_ADDRESS_INVALID;
        /* Set valid record position TBL flag to "created" */
        Fee_RecordPosTBLValidFlag[u1AreaNum] = FEE_RPTBLFIXED;
        Fee_RecordPosTBLValidFlagMrr[u1AreaNum] = FEE_RPTBL_MRR_FIXED;
        /* Set return value to complete creation (STATUS _ OK) */
        u4tReturn = FEE_STATUS_OK;
    }
    else
    {
        /* When the number of searches per periodic operation is reached */
        /* Keep this last search address */
        Fee_TBLMakeSrcAddress = u4tLocalSrchAddress;
    }
    
    /* Write back searchable count */
    Fee_CpuDtfInfo.u4SrchRemainCount = SrchRemainCount;

    Fee_TBLMakeSrcAddressMrr = (uint32)(~Fee_TBLMakeSrcAddress);

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_RecordPosTbl_GetStatusArea                           */
/* Description   | Validity acquisition of effective record position TBL    */
/* Preconditions | None                                                     */
/* Parameters    | uint8u1AreaNum: area number                              */
/*               | u1BlockNum    : block number number                      */
/*               | u4SrchAddress : Search address                           */
/*               | stCPUDTF *ptstCPUDTFInfo                                 */
/* Return Value  |  Result of obtaining validity                            */
/*               | 0x00000000 : FEE_RPSTATUS_VALID   : Valid                */
/*               | 0x00000001 : FEE_RPSTATUS_INVALID : Invalid              */
/*               | 0x00000002 : FEE_RPSTATUS_ERROR   : Abnormal             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_RecordPosTbl_GetStatusArea(
    uint8 u1AreaNum
){
    uint32          u4tReturn;                  /* RETURN */
    uint8           u1tValidFlag;               /* Valid flag */
    uint8           u1tValidFlagMrr;            /* Valid flag mirror */

    u1tValidFlag = Fee_RecordPosTBLValidFlag[u1AreaNum];
    u1tValidFlagMrr = Fee_RecordPosTBLValidFlagMrr[u1AreaNum];
    if ( (u1tValidFlag ^ u1tValidFlagMrr) == FEE_RPTBL_VALID_FLAG_COMPARE_MATCH )
    {
        if ( u1tValidFlag == FEE_RPTBLFIXED )
        {
            /* If the enable flag is "created" */
            u4tReturn = FEE_RPSTATUS_VALID;
        }
        else
        {
            /* If valid flag is "not created" or "creating" */
            u4tReturn = FEE_RPSTATUS_INVALID;
        }
    }
    else
    {
        u4tReturn = FEE_RPSTATUS_ERROR;
    }

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_RecordPosTbl_GetTblIdx                               */
/* Description   | Function to get an index of the record position table.   */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo      : An area number.                            */
/*               | BlockNumber : A block number.                            */
/*               | RecPosTblIdx: An output parameter.                       */
/*               |               An index of the record position table.     */
/* Return Value  | Getting result.                                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_RecordPosTbl_GetTblIdx(
    uint8  AreaNo,
    uint16 BlockNumber,
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) RecPosTblIdx
){
    Std_ReturnType Rtn = E_NOT_OK;
    Std_ReturnType GetCfgTblIndexResult;

    uint16         CfgTblIdx;
    uint16         DatasetIdx;
    uint16         TmpRecPosTblIdx;
    uint16         RecPosTblSize;
    uint16         OffsetPos;

    GetCfgTblIndexResult = Fee_Pif_GetCfgTblIdxFromBlockNumber( BlockNumber, &CfgTblIdx );
    if( GetCfgTblIndexResult == (Std_ReturnType)E_OK )
    {
        Fee_Pif_GetDatasetIdxFromBlockNumber( BlockNumber, &DatasetIdx );

        OffsetPos = Fee_OffsetPos[AreaNo];
        TmpRecPosTblIdx = ( FeeRecPosTblIdx[CfgTblIdx] + DatasetIdx ) + OffsetPos;
        RecPosTblSize = Fee_RecordPosTBLSize;
        if ( TmpRecPosTblIdx < RecPosTblSize )
        {
            *RecPosTblIdx = TmpRecPosTblIdx;
            Rtn = E_OK;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_RecordPosTbl_SetMemoryU2                             */
/* Description   | Data set processing                                      */
/* Preconditions | None                                                     */
/* Parameters    | setto address                                            */
/*               | u2Data : Data to set                                     */
/*               | u2SetLen : set size                                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_RecordPosTbl_SetMemoryU2(
    P2VAR( uint16, AUTOMATIC, TYPEDEF ) ptu2Dst,
    uint16 u2Data,
    uint16 u2SetLen
){
    uint16 Index;

    for( Index = 0U; Index < u2SetLen; Index++ )
    {
        ptu2Dst[Index] = u2Data;
    }

    return;
}
#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/27                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
