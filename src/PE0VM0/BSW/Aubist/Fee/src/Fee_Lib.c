/* Fee_Lib.c v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/LIB/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Ram.h"
#include "../inc/Fee_Common.h"

#include "../inc/Fee_Lib.h"
#include "../inc/Fee_Lib_Internal.h"

#include <Mscd_Common.h>

#include "../inc/Fee_ExConst.h"

#include "../inc/Fee_Dfc.h"
#include "../inc/Fee_Mpu_Dev_Const.h"
#include "../inc/Fee_Legacy.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Final write record position association definition */
/* Data for buffer initialization */
#define FEE_LWPBLKNO_INIT   ((uint8)0xFFU)      /* Initial block number */
#define FEE_LWPBS_INIT      ((uint8)0xFFU)      /* Initial block status */

/* Mirror checking data */
#define FEE_MIRROR_CHECK_BLOCK_NO       ((uint8)0xFFU)          /* Block number */
#define FEE_MIRROR_CHECK_BLOCK_STATUS   ((uint8)0xFFU)          /* Block status */
#define FEE_MIRROR_CHECK_SET_KIND       ((uint8)0xFFU)          /* Setting processing type */
#define FEE_MIRROR_CHECK_WRITE_POS      ((uint32)0xFFFFFFFFU)   /* Write destination address offset during data write/transition */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_InitCpuDtfData                                       */
/* Description   | MHA (Data Flash) Management Data Initialization          */
/* Preconditions | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |             MHA management data                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_InitCpuDtfData( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    ptstCPUDTFInfo->u1ProcessStatus = FEE_STATUSIDLE;                           /* Operational status */
    ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSINVALID;                          /* MAIN STATE */
    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSINVALID;                           /* Substate */
    ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSINVALID;                       /* Subsubstate */
    ptstCPUDTFInfo->u1Result = FEE_RSP_OK;                                      /* Result of processing */
    ptstCPUDTFInfo->u1AreaNum = (uint8)FEE_AREANUM_INVALID;                     /* Area number */

    ptstCPUDTFInfo->u4BlockCount = 0U;                                          /* Block counter */
    ptstCPUDTFInfo->u4FailCount = 0U;                                           /* Failure counters */
    ptstCPUDTFInfo->u4SrchRemainCount = 0U;                                     /* searchable */
    ptstCPUDTFInfo->u4MoveSrcAddress = FEE_ADDRESS_INVALID;                     /* Data transfer source address */
    ptstCPUDTFInfo->u4ReadSrchAddress = FEE_ADDRESS_INVALID;                    /* ID-specified data read-destination address */
    ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr = FEE_ADDRESS_INVALID;             /* Address to write when data is written and transferred */
    ptstCPUDTFInfo->u4WriteLastRecDatAbsAddr = FEE_ADDRESS_INVALID;
    ptstCPUDTFInfo->u4MainTimerCnt = FEE_TM_INVALID;                            /* Main timer counter */
    ptstCPUDTFInfo->u4DFCTimerCnt = FEE_TM_INVALID;                             /* D.F.C. Timer Counter */
    ptstCPUDTFInfo->u1MainBlockNo = FEE_BLOCKNUM_INVALID;                       /* MAIN BLOCK NUMBER */
    ptstCPUDTFInfo->u1MainBlockStatus = FEE_BS_INVALID;                         /* MAIN BLOCK STATUS */
    ptstCPUDTFInfo->u1SubBlockNo = FEE_BLOCKNUM_INVALID;                        /* Subblock number */
    ptstCPUDTFInfo->u1SubBlockStatus = FEE_BS_INVALID;                          /* Subblock status */
    ptstCPUDTFInfo->u2DATA_ID = FEE_INIDAT_UINT16;                              /* DATA-ID */
    ptstCPUDTFInfo->u2MovDataId = FEE_INIDAT_UINT16;
    ptstCPUDTFInfo->u1LastWritePosFlag = FEE_FLAG_OFF;                          /* Last write record position update permission flag */
    ptstCPUDTFInfo->ptstAreaInf = NULL_PTR;                                     /* Area-dependent data structure */
    ptstCPUDTFInfo->ptu1ReqWriteAddr = NULL_PTR;                                /* Write data address */
    ptstCPUDTFInfo->ptu1ReqReadAddr  = NULL_PTR;                                /* Read data address */
    ptstCPUDTFInfo->u2ReqDataLen = FEE_LENGTH_INVALID;
    ptstCPUDTFInfo->u2MovDataLen = FEE_LENGTH_INVALID;

    return;
}

/****************************************************************************/
/* Function Name | Fee_Lib_CheckCpuDtfData                                  */
/* Description   | Function to check Fee_CpuDtfType value.                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Check result.                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_Lib_CheckCpuDtfData( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    Std_ReturnType Rtn = E_NOT_OK;

    if((( Fee_CpuDtfInfo.u1ProcessStatus          ^ Fee_CpuDtfInfoSub.u1ProcessStatus          ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_CpuDtfInfo.u1MainStatus             ^ Fee_CpuDtfInfoSub.u1MainStatus             ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_CpuDtfInfo.u1SubStatus              ^ Fee_CpuDtfInfoSub.u1SubStatus              ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_CpuDtfInfo.u1SubSubStatus           ^ Fee_CpuDtfInfoSub.u1SubSubStatus           ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_CpuDtfInfo.u1AreaNum                ^ Fee_CpuDtfInfoSub.u1AreaNum                ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_CpuDtfInfo.u4BlockCount             ^ Fee_CpuDtfInfoSub.u4BlockCount             ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_CpuDtfInfo.u4MoveSrcAddress         ^ Fee_CpuDtfInfoSub.u4MoveSrcAddress         ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_CpuDtfInfo.u4ReadSrchAddress        ^ Fee_CpuDtfInfoSub.u4ReadSrchAddress        ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_CpuDtfInfo.u4WriteLastRecMngAbsAddr ^ Fee_CpuDtfInfoSub.u4WriteLastRecMngAbsAddr ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_CpuDtfInfo.u4WriteLastRecDatAbsAddr ^ Fee_CpuDtfInfoSub.u4WriteLastRecDatAbsAddr ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_CpuDtfInfo.u1MainBlockNo            ^ Fee_CpuDtfInfoSub.u1MainBlockNo            ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_CpuDtfInfo.u1SubBlockNo             ^ Fee_CpuDtfInfoSub.u1SubBlockNo             ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_CpuDtfInfo.u1MainBlockStatus        ^ Fee_CpuDtfInfoSub.u1MainBlockStatus        ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_CpuDtfInfo.u1SubBlockStatus         ^ Fee_CpuDtfInfoSub.u1SubBlockStatus         ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && (( Fee_CpuDtfInfo.u2DATA_ID                ^ Fee_CpuDtfInfoSub.u2DATA_ID                ) == (uint16)FEE_MIRROR_CHECK_UINT16 )
    && (( Fee_CpuDtfInfo.u2MovDataId              ^ Fee_CpuDtfInfoSub.u2MovDataId              ) == (uint16)FEE_MIRROR_CHECK_UINT16 )
    && (( Fee_CpuDtfInfo.u1LastWritePosFlag       ^ Fee_CpuDtfInfoSub.u1LastWritePosFlag       ) == (uint8)FEE_MIRROR_CHECK_UINT8 )
    && ( Fee_CpuDtfInfo.ptstAreaInf              == Fee_CpuDtfInfoSub.ptstAreaInf )
    && (( Fee_CpuDtfInfo.u2ReqDataLen             ^ Fee_CpuDtfInfoSub.u2ReqDataLen             ) == (uint16)FEE_MIRROR_CHECK_UINT16 )
    && (( Fee_CpuDtfInfo.u2MovDataLen             ^ Fee_CpuDtfInfoSub.u2MovDataLen             ) == (uint16)FEE_MIRROR_CHECK_UINT16 ))
    {
        Rtn = E_OK;
    }

    return Rtn;
#else /* FEE_USE_REDUNDANCY_RAM == STD_OFF */
    return E_OK;
#endif /* FEE_USE_REDUNDANCY_RAM */
}

/****************************************************************************/
/* Function Name | Fee_Lib_SetCpuDtfDataSub                                 */
/* Description   | Function to set value to Fee_CpuDtfType sub from main.   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Lib_SetCpuDtfDataSub( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    Fee_CpuDtfInfoSub.u1ProcessStatus           = (uint8)(~Fee_CpuDtfInfo.u1ProcessStatus);
    Fee_CpuDtfInfoSub.u1MainStatus              = (uint8)(~Fee_CpuDtfInfo.u1MainStatus);
    Fee_CpuDtfInfoSub.u1SubStatus               = (uint8)(~Fee_CpuDtfInfo.u1SubStatus);
    Fee_CpuDtfInfoSub.u1SubSubStatus            = (uint8)(~Fee_CpuDtfInfo.u1SubSubStatus);
    Fee_CpuDtfInfoSub.u1AreaNum                 = (uint8)(~Fee_CpuDtfInfo.u1AreaNum);
    Fee_CpuDtfInfoSub.u4BlockCount              = (uint32)(~Fee_CpuDtfInfo.u4BlockCount);
    Fee_CpuDtfInfoSub.u4MoveSrcAddress          = (uint32)(~Fee_CpuDtfInfo.u4MoveSrcAddress);
    Fee_CpuDtfInfoSub.u4ReadSrchAddress         = (uint32)(~Fee_CpuDtfInfo.u4ReadSrchAddress);
    Fee_CpuDtfInfoSub.u4WriteLastRecMngAbsAddr  = (uint32)(~Fee_CpuDtfInfo.u4WriteLastRecMngAbsAddr);
    Fee_CpuDtfInfoSub.u4WriteLastRecDatAbsAddr  = (uint32)(~Fee_CpuDtfInfo.u4WriteLastRecDatAbsAddr);
    Fee_CpuDtfInfoSub.u1MainBlockNo             = (uint8)(~Fee_CpuDtfInfo.u1MainBlockNo);
    Fee_CpuDtfInfoSub.u1SubBlockNo              = (uint8)(~Fee_CpuDtfInfo.u1SubBlockNo);
    Fee_CpuDtfInfoSub.u1MainBlockStatus         = (uint8)(~Fee_CpuDtfInfo.u1MainBlockStatus);
    Fee_CpuDtfInfoSub.u1SubBlockStatus          = (uint8)(~Fee_CpuDtfInfo.u1SubBlockStatus);
    Fee_CpuDtfInfoSub.u2DATA_ID                 = (uint16)(~Fee_CpuDtfInfo.u2DATA_ID);
    Fee_CpuDtfInfoSub.u2MovDataId               = (uint16)(~Fee_CpuDtfInfo.u2MovDataId);
    Fee_CpuDtfInfoSub.u1LastWritePosFlag        = (uint8)(~Fee_CpuDtfInfo.u1LastWritePosFlag);
    Fee_CpuDtfInfoSub.ptstAreaInf               = Fee_CpuDtfInfo.ptstAreaInf;
    Fee_CpuDtfInfoSub.u2ReqDataLen              = (uint16)(~Fee_CpuDtfInfo.u2ReqDataLen);
    Fee_CpuDtfInfoSub.u2MovDataLen              = (uint16)(~Fee_CpuDtfInfo.u2MovDataLen);
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

    return;
}

/****************************************************************************/
/* Function Name | Fee_Lib_SetMemory                                        */
/* Description   | Function to set memory to a specified value.             */
/* Preconditions | None                                                     */
/* Parameters    | DstPtr   : An address of destination data.               */
/*               | Constant : A value that wanted to set.                   */
/*               | Length   : Size of data for data setting.                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Lib_SetMemory( P2VAR(uint8, AUTOMATIC, TYPEDEF) DstPtr, uint8 Constant, uint32 Length )
{
    uint32          Index;
    
    for ( Index = 0U; Index < Length; Index++ )
    {
        DstPtr[Index] = Constant;
    }
    
    return;
}

/****************************************************************************/
/* Function Name | Fee_Lib_CompareMemory                                    */
/* Description   | Function to compare memory data                          */
/* Preconditions | None                                                     */
/* Parameters    | Data1  : Pointer to first data buffer                    */
/*               | Data2  : Pointer to second data buffer                   */
/*               | Length : Number of bytes for comparision                 */
/* Return Value  | FEE_LIB_EQUAL                                            */
/*               | FEE_LIB_UNEQUAL                                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, FEE_CODE )
Fee_Lib_CompareMemory(
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) Data1,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) Data2,
    uint32                               Length
){
    uint8  Rtn;
    uint32 Counter;

    Rtn = FEE_LIB_EQUAL;
    for( Counter = 0U; Counter < Length; Counter++ )
    {
        if( Data1[Counter] != Data2[Counter] )
        {
            Rtn = FEE_LIB_UNEQUAL;
            break;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Lib_CopyMemory                                       */
/* Description   | Function to copy memory data                             */
/* Preconditions | None                                                     */
/* Parameters    | DstData : Pointer to destination data buffer             */
/*               | SrcData : Pointer to source data buffer                  */
/*               | Length  : Number of bytes for copy                       */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Lib_CopyMemory(
    P2VAR( uint8, AUTOMATIC, TYPEDEF )   DstData,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) SrcData,
    uint32                               Length
){
    uint32 Counter;

    for( Counter = 0U; Counter < Length; Counter++ )
    {
        DstData[Counter] = SrcData[Counter];
    }

    return;
}

#if ( MSCD_FREESPACE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Fee_Lib_GetLastWritePosLite                              */
/* Description   | Function to get last record positions from LIB.          */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo                                                   */
/*               | CurrentJobKind                                           */
/*               | DstLastWritePos                                          */
/* Return Value  | E_OK                                                     */
/*               | E_NOT_OK                                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_Lib_GetLastWritePosLite(
    uint8 AreaNo,
    uint8 CurrentJobKind,
    P2VAR( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) DstLastWritePos
){
    Std_ReturnType Rtn;
    Std_ReturnType RedundantCheckResult;
    uint8 StoredJobKind;

    Rtn = E_NOT_OK;
    RedundantCheckResult = Fee_ChkLastWritePosRedundancyData( &Fee_LastWPosInfo1[AreaNo], &Fee_LastWPosInfo2[AreaNo] );
    if( RedundantCheckResult== (Std_ReturnType)E_OK )
    {
        StoredJobKind = Fee_LastWPosInfo1[AreaNo].u1SetKind;
        if(( CurrentJobKind == FEE_LWPWRITE )
        && ( StoredJobKind  == FEE_LWPWRITE ))
        {
            DstLastWritePos->stMainBlockInfo.u1BlockNo      = Fee_LastWPosInfo1[AreaNo].stMainBlockInfo.u1BlockNo;
            DstLastWritePos->stMainBlockInfo.u1BlockStatus  = Fee_LastWPosInfo1[AreaNo].stMainBlockInfo.u1BlockStatus;
            DstLastWritePos->stSubBlockInfo.u1BlockNo       = Fee_LastWPosInfo1[AreaNo].stSubBlockInfo.u1BlockNo;
            DstLastWritePos->stSubBlockInfo.u1BlockStatus   = Fee_LastWPosInfo1[AreaNo].stSubBlockInfo.u1BlockStatus;
            DstLastWritePos->u1SetKind                      = StoredJobKind;
            DstLastWritePos->u4WriteLastRecMngAbsAddr       = Fee_LastWPosInfo1[AreaNo].u4WriteLastRecMngAbsAddr;
            DstLastWritePos->u4WriteLastRecDatAbsAddr       = Fee_LastWPosInfo1[AreaNo].u4WriteLastRecDatAbsAddr;

            Rtn = E_OK;
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_Lib_SetLastWritePosLite                              */
/* Description   | Function to set last record positions to LIB.            */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo                                                   */
/*               | SrcLastWritePos                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Lib_SetLastWritePosLite(
    uint8 AreaNo,
    P2CONST( Fee_LwpInfType, AUTOMATIC, TYPEDEF ) SrcLastWritePos
){
    uint8 CurrentJobKind;

    CurrentJobKind = SrcLastWritePos->u1SetKind;

    if( CurrentJobKind == FEE_LWPWRITE )
    {
        Fee_LastWPosInfo1[AreaNo].stMainBlockInfo.u1BlockNo         = SrcLastWritePos->stMainBlockInfo.u1BlockNo;
        Fee_LastWPosInfo1[AreaNo].stMainBlockInfo.u1BlockStatus     = SrcLastWritePos->stMainBlockInfo.u1BlockStatus;
        Fee_LastWPosInfo1[AreaNo].stSubBlockInfo.u1BlockNo          = SrcLastWritePos->stSubBlockInfo.u1BlockNo;
        Fee_LastWPosInfo1[AreaNo].stSubBlockInfo.u1BlockStatus      = SrcLastWritePos->stSubBlockInfo.u1BlockStatus;
        Fee_LastWPosInfo1[AreaNo].u1SetKind                         = CurrentJobKind;
        Fee_LastWPosInfo1[AreaNo].u4WriteLastRecMngAbsAddr          = SrcLastWritePos->u4WriteLastRecMngAbsAddr;
        Fee_LastWPosInfo1[AreaNo].u4WriteLastRecDatAbsAddr          = SrcLastWritePos->u4WriteLastRecDatAbsAddr;

        Fee_LastWPosInfo2[AreaNo].stMainBlockInfo.u1BlockNo         =  (uint8)(~Fee_LastWPosInfo1[AreaNo].stMainBlockInfo.u1BlockNo);
        Fee_LastWPosInfo2[AreaNo].stMainBlockInfo.u1BlockStatus     =  (uint8)(~Fee_LastWPosInfo1[AreaNo].stMainBlockInfo.u1BlockStatus);
        Fee_LastWPosInfo2[AreaNo].stSubBlockInfo.u1BlockNo          =  (uint8)(~Fee_LastWPosInfo1[AreaNo].stSubBlockInfo.u1BlockNo);
        Fee_LastWPosInfo2[AreaNo].stSubBlockInfo.u1BlockStatus      =  (uint8)(~Fee_LastWPosInfo1[AreaNo].stSubBlockInfo.u1BlockStatus);
        Fee_LastWPosInfo2[AreaNo].u1SetKind                         =  (uint8)(~Fee_LastWPosInfo1[AreaNo].u1SetKind);
        Fee_LastWPosInfo2[AreaNo].u4WriteLastRecMngAbsAddr          = (uint32)(~Fee_LastWPosInfo1[AreaNo].u4WriteLastRecMngAbsAddr);
        Fee_LastWPosInfo2[AreaNo].u4WriteLastRecDatAbsAddr          = (uint32)(~Fee_LastWPosInfo1[AreaNo].u4WriteLastRecDatAbsAddr);
    }

    return;
}
#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

/****************************************************************************/
/* Function Name | Fee_RefLastWritePos                                      */
/* Description   | Final write record position read processing              */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |                MHA management data                       */
/* Return Value  | Read Results                                             */
/*               | 0x00000000 : FEE_STATUS_OK : Read successful             */
/*               | 0x00000001 : FEE_STATUS_NG : Read failed                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_RefLastWritePos( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                          /* RETURN */
    uint32          u4tChkResult;                       /* Trailing data validation result */
    uint8           u1tAreaNum;                         /* Area number */
    uint32          u4tClearFlag;                       /* Whether to clear tail data */

    /* Initialize on failure to read return variable */
    u4tReturn = FEE_STATUS_NG;
    /* Initialize without clearing flag on whether to clear tail data */
    u4tClearFlag = FEE_STATUS_NG;
    /* Eject Area Number */
    u1tAreaNum = ptstCPUDTFInfo->u1AreaNum;

    /* Validate tail-record retention data */
    u4tChkResult = Fee_ChkLastWritePos( ptstCPUDTFInfo );

    if ( u4tChkResult == FEE_STATUS_OK )
    {
        /* If correct */
        /* Operating status check */
        if (   ( ptstCPUDTFInfo->u1ProcessStatus == FEE_STATUSWRITE ) 
            || ( ptstCPUDTFInfo->u1ProcessStatus == FEE_STATUSMOVE ) )
        {
            /* If the operating state is writing or reorganizing data */
            if ( ( Fee_LastWPosInfo1[u1tAreaNum].u1SetKind) == FEE_LWPWRITE )
            {
                /* When processing setting type is set to write */
                /* Set return variable to read success */
                u4tReturn = FEE_STATUS_OK;
            }
            /* Set to clear tail data */
            u4tClearFlag = FEE_STATUS_OK;
        }
        else
        {
            /* If the operating state is anything else (reading or idle) */
            /* Set return variable to read success */
            u4tReturn = FEE_STATUS_OK;
        }
    }

    if ( u4tReturn == FEE_STATUS_OK )
    {
        /* If the return variable is read successfully */
        /* Set data */
        /* MAIN BLOCK NUMBER */
        ptstCPUDTFInfo->u1MainBlockNo = Fee_LastWPosInfo1[u1tAreaNum].stMainBlockInfo.u1BlockNo;
        /* MAIN BLOCK STATUS */
        ptstCPUDTFInfo->u1MainBlockStatus = Fee_LastWPosInfo1[u1tAreaNum].stMainBlockInfo.u1BlockStatus;
        /* Subblock number */
        ptstCPUDTFInfo->u1SubBlockNo = Fee_LastWPosInfo1[u1tAreaNum].stSubBlockInfo.u1BlockNo;
        /* Subblock status */
        ptstCPUDTFInfo->u1SubBlockStatus = Fee_LastWPosInfo1[u1tAreaNum].stSubBlockInfo.u1BlockStatus;
        /* Address to write when data is written and transferred */
        ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr = Fee_LastWPosInfo1[u1tAreaNum].u4WriteLastRecMngAbsAddr;
        ptstCPUDTFInfo->u4WriteLastRecDatAbsAddr = Fee_LastWPosInfo1[u1tAreaNum].u4WriteLastRecDatAbsAddr;
    }
    if ( u4tClearFlag == FEE_STATUS_OK )
    {
        /* To clear tail data */
        /* Initialize last write record position (specified area) */
        Fee_InitLastWritePos( u1tAreaNum, FEE_INIT_ONE );
    }


    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_SetLastWritePos                                      */
/* Description   | Final write record position saving process               */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |              MHA management data                         */
/* Return Value  | Read Results                                             */
/*               | 0x00000000 : FEE_STATUS_OK : Save successful             */
/*               | 0x00000001 : FEE_STATUS_NG : Save failed                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_SetLastWritePos( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                          /* RETURN */
    uint32          u4tChkResult;                       /* Trailing data validation result */
    uint8           u1tAreaNum;                         /* Area number */

    /* Initialize with failure to save return variable */
    u4tReturn = FEE_STATUS_NG;
    /* Eject Area Number */
    u1tAreaNum = ptstCPUDTFInfo->u1AreaNum;

    /* Operating status check */
    if (   ( ptstCPUDTFInfo->u1ProcessStatus == FEE_STATUSWRITE ) 
        || ( ptstCPUDTFInfo->u1ProcessStatus == FEE_STATUSMOVE ) )
    {
        /* If the operating state is writing or reorganizing data */
        /* Set processing setting type to write */
        Fee_LastWPosInfo1[u1tAreaNum].u1SetKind = FEE_LWPWRITE;
        /* Set return variable to save success */
        u4tReturn = FEE_STATUS_OK;
    }
    else
    {
        /* If the operating state is anything else (reading or idle) */
        /* Validate tail-record retention data */
        u4tChkResult = Fee_ChkLastWritePos( ptstCPUDTFInfo );
        if ( u4tChkResult == FEE_STATUS_NG )
        {
            /* Incorrect */
            /* Set processing setting type to read */
            Fee_LastWPosInfo1[u1tAreaNum].u1SetKind = FEE_LWPREAD;
            /* Set return variable to save success */
            u4tReturn = FEE_STATUS_OK;
        }
    }

    if ( u4tReturn == FEE_STATUS_OK )
    {
        /* If the return variable was successfully saved */
        /* MAIN BLOCK NUMBER */
        Fee_LastWPosInfo1[u1tAreaNum].stMainBlockInfo.u1BlockNo = ptstCPUDTFInfo->u1MainBlockNo;
        /* MAIN BLOCK STATUS */
        Fee_LastWPosInfo1[u1tAreaNum].stMainBlockInfo.u1BlockStatus = ptstCPUDTFInfo->u1MainBlockStatus;
        /* Subblock number */
        Fee_LastWPosInfo1[u1tAreaNum].stSubBlockInfo.u1BlockNo = ptstCPUDTFInfo->u1SubBlockNo;
        /* Subblock status */
        Fee_LastWPosInfo1[u1tAreaNum].stSubBlockInfo.u1BlockStatus = ptstCPUDTFInfo->u1SubBlockStatus;
        /* Address to write when data is written and transferred */
        Fee_LastWPosInfo1[u1tAreaNum].u4WriteLastRecMngAbsAddr = ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr;
        Fee_LastWPosInfo1[u1tAreaNum].u4WriteLastRecDatAbsAddr = ptstCPUDTFInfo->u4WriteLastRecDatAbsAddr;
        
        /* Set memory buffer 2 */
        Fee_LastWPosInfo2[u1tAreaNum].stMainBlockInfo.u1BlockNo = (uint8)(~Fee_LastWPosInfo1[u1tAreaNum].stMainBlockInfo.u1BlockNo);
        Fee_LastWPosInfo2[u1tAreaNum].stMainBlockInfo.u1BlockStatus = (uint8)(~Fee_LastWPosInfo1[u1tAreaNum].stMainBlockInfo.u1BlockStatus);
        Fee_LastWPosInfo2[u1tAreaNum].stSubBlockInfo.u1BlockNo = (uint8)(~Fee_LastWPosInfo1[u1tAreaNum].stSubBlockInfo.u1BlockNo);
        Fee_LastWPosInfo2[u1tAreaNum].stSubBlockInfo.u1BlockStatus = (uint8)(~Fee_LastWPosInfo1[u1tAreaNum].stSubBlockInfo.u1BlockStatus);
        Fee_LastWPosInfo2[u1tAreaNum].u1SetKind = (uint8)(~Fee_LastWPosInfo1[u1tAreaNum].u1SetKind);
        Fee_LastWPosInfo2[u1tAreaNum].u4WriteLastRecMngAbsAddr = (uint32)(~(Fee_LastWPosInfo1[u1tAreaNum].u4WriteLastRecMngAbsAddr));
        Fee_LastWPosInfo2[u1tAreaNum].u4WriteLastRecDatAbsAddr = (uint32)(~(Fee_LastWPosInfo1[u1tAreaNum].u4WriteLastRecDatAbsAddr));
    }

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_InitLastWritePos                                     */
/* Description   | Last write record position initialization                */
/* Preconditions | None                                                     */
/* Parameters    | uint8 u1Mode    : Initialization mode                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_InitLastWritePos( uint8 u1AreaNum, uint8 u1Mode )
{
    uint32          u4tCounter;                         /* Counter */
    uint32          u4tStartAreaNum;                    /* Starting area number */
    uint32          u4tEndAreaNum;                      /* End area number */

    /* Initialization mode check */
    if ( u1Mode == FEE_INIT_ONE )
    {
        /* Designated Area */
        u4tStartAreaNum = (uint32)u1AreaNum;
        u4tEndAreaNum = (uint32)u1AreaNum + (uint32)FEE_NEXT_AREANUM_OFFSET;
    }
    else
    {
        /* ALL AREA */
        u4tStartAreaNum = (uint32)FEE_START_AREANUM;
        u4tEndAreaNum = (uint32)Fee_AreaNumber;
    }

    for ( u4tCounter = u4tStartAreaNum; u4tCounter < u4tEndAreaNum; u4tCounter++ )
    {
        /* Set memory buffer 1 */
        Fee_LastWPosInfo1[u4tCounter].stMainBlockInfo.u1BlockNo = FEE_LWPBLKNO_INIT;    /* MAIN BLOCK NUMBER */
        Fee_LastWPosInfo1[u4tCounter].stMainBlockInfo.u1BlockStatus = FEE_LWPBS_INIT;   /* MAIN BLOCK STATUS */
        Fee_LastWPosInfo1[u4tCounter].stSubBlockInfo.u1BlockNo = FEE_LWPBLKNO_INIT; /* Subblock number */
        Fee_LastWPosInfo1[u4tCounter].stSubBlockInfo.u1BlockStatus = FEE_LWPBS_INIT;    /* Subblock status */
        Fee_LastWPosInfo1[u4tCounter].u1SetKind = FEE_LWPKIND_INIT;                 /* Setting processing type */
        Fee_LastWPosInfo1[u4tCounter].u4WriteLastRecMngAbsAddr = FEE_ADDRESS_INVALID;               /* Address to write when data is written and transferred */
        Fee_LastWPosInfo1[u4tCounter].u4WriteLastRecDatAbsAddr = FEE_ADDRESS_INVALID;
        /* Set memory buffer 2 */
        Fee_LastWPosInfo2[u4tCounter].stMainBlockInfo.u1BlockNo = FEE_LWPBLKNO_INIT;    /* MAIN BLOCK NUMBER */
        Fee_LastWPosInfo2[u4tCounter].stMainBlockInfo.u1BlockStatus = FEE_LWPBS_INIT;   /* MAIN BLOCK STATUS */
        Fee_LastWPosInfo2[u4tCounter].stSubBlockInfo.u1BlockNo = FEE_LWPBLKNO_INIT; /* Subblock number */
        Fee_LastWPosInfo2[u4tCounter].stSubBlockInfo.u1BlockStatus = FEE_LWPBS_INIT;    /* Subblock status */
        Fee_LastWPosInfo2[u4tCounter].u1SetKind = FEE_LWPKIND_INIT;                 /* Setting processing type */
        Fee_LastWPosInfo2[u4tCounter].u4WriteLastRecMngAbsAddr = FEE_ADDRESS_INVALID;               /* Address to write when data is written and transferred */
        Fee_LastWPosInfo2[u4tCounter].u4WriteLastRecDatAbsAddr = FEE_ADDRESS_INVALID;
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_ChkLastWritePos                                      */
/* Description   | Final write record position check processing             */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |              MHA management data                         */
/* Return Value  | Read Results                                             */
/*               | 0x00000000 : FEE_STATUS_OK : Check successful            */
/*               | 0x00000001 : FEE_STATUS_NG : Check failed                */
/* Notes         | Initialize last write record position when check fails   */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_ChkLastWritePos( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                          /* RETURN */
    uint8           u1tAreaNum;
    Std_ReturnType  CheckResult;

    u4tReturn = FEE_STATUS_NG;
    u1tAreaNum = ptstCPUDTFInfo->u1AreaNum;

    CheckResult = Fee_ChkLastWritePosRedundancyData( &Fee_LastWPosInfo1[u1tAreaNum], &Fee_LastWPosInfo2[u1tAreaNum] );
    if( CheckResult == (Std_ReturnType)E_OK )
    {
        CheckResult = Fee_ChkLastWritePosBlock( &Fee_LastWPosInfo1[u1tAreaNum], ptstCPUDTFInfo );
        if( CheckResult == (Std_ReturnType)E_OK )
        {
            CheckResult = Fee_ChkLastWritePosLastRecAddr( &Fee_LastWPosInfo1[u1tAreaNum], ptstCPUDTFInfo );
        }
    }

    if( CheckResult == (Std_ReturnType)E_OK )
    {
        u4tReturn = FEE_STATUS_OK;
    }
    else
    {
        Fee_InitLastWritePos( u1tAreaNum, FEE_INIT_ONE );
    }

    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_ChkLastWritePosRedundancyData                        */
/* Description   | Function to check last position information data.        */
/* Preconditions | None                                                     */
/* Parameters    | LastWPosInfo1                                            */
/*               | LastWPosInfo2                                            */
/*               | AreaNum                                                  */
/* Return Value  | Check result.                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_ChkLastWritePosRedundancyData(
    P2CONST( Fee_LwpInfType, AUTOMATIC, FEE_VAR_NO_INIT ) LastWPosInfo1,
    P2CONST( Fee_LwpInfType, AUTOMATIC, FEE_VAR_NO_INIT ) LastWPosInfo2
){
    Std_ReturnType  Rtn = E_NOT_OK;

    if((( LastWPosInfo1->stMainBlockInfo.u1BlockNo       ^ LastWPosInfo2->stMainBlockInfo.u1BlockNo )     == FEE_MIRROR_CHECK_BLOCK_NO )
    && (( LastWPosInfo1->stMainBlockInfo.u1BlockStatus   ^ LastWPosInfo2->stMainBlockInfo.u1BlockStatus ) == FEE_MIRROR_CHECK_BLOCK_STATUS )
    && (( LastWPosInfo1->stSubBlockInfo.u1BlockNo        ^ LastWPosInfo2->stSubBlockInfo.u1BlockNo )      == FEE_MIRROR_CHECK_BLOCK_NO )
    && (( LastWPosInfo1->stSubBlockInfo.u1BlockStatus    ^ LastWPosInfo2->stSubBlockInfo.u1BlockStatus )  == FEE_MIRROR_CHECK_BLOCK_STATUS )
    && (( LastWPosInfo1->u1SetKind                       ^ LastWPosInfo2->u1SetKind )                     == FEE_MIRROR_CHECK_SET_KIND )
    && (( LastWPosInfo1->u4WriteLastRecMngAbsAddr        ^ LastWPosInfo2->u4WriteLastRecMngAbsAddr )      == FEE_MIRROR_CHECK_WRITE_POS )
    && (( LastWPosInfo1->u4WriteLastRecDatAbsAddr        ^ LastWPosInfo2->u4WriteLastRecDatAbsAddr )      == FEE_MIRROR_CHECK_WRITE_POS ))
    {
        Rtn = E_OK;
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_ChkLastWritePosBlock                                 */
/* Description   | Function to check last position information data.        */
/* Preconditions | None                                                     */
/* Parameters    | LastWPosInfo                                             */
/*               | CPUDTFInfo                                               */
/*               | AreaNum                                                  */
/* Return Value  | Check result.                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_ChkLastWritePosBlock(
    P2CONST( Fee_LwpInfType, AUTOMATIC, FEE_VAR_NO_INIT ) LastWPosInfo,
    P2CONST( Fee_CpuDtfType, AUTOMATIC, TYPEDEF         ) CPUDTFInfo
){
    Std_ReturnType  Rtn = E_NOT_OK;
    uint8           MainBlockNo;
    uint8           SubBlockNo;
    uint8           MainBlockStatus;
    uint8           SubBlockStatus;
    uint8           BlockNum;
    uint8           StartBlockNo;

    BlockNum        = CPUDTFInfo->ptstAreaInf->u1BlockNum;
    StartBlockNo    = CPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum;

    /* Check sector number range. */
    MainBlockNo = LastWPosInfo->stMainBlockInfo.u1BlockNo;
    SubBlockNo  = LastWPosInfo->stSubBlockInfo.u1BlockNo;
    if((((uint8)( MainBlockNo - StartBlockNo) ) < BlockNum )
    && (((uint8)( SubBlockNo  - StartBlockNo) ) < BlockNum ))
    {
        /* Check relation between main and sub sector number. */
        if( MainBlockNo != SubBlockNo )
        {
            /* Check block status range. */
            MainBlockStatus = LastWPosInfo->stMainBlockInfo.u1BlockStatus;
            SubBlockStatus  = LastWPosInfo->stSubBlockInfo.u1BlockStatus;
            if(( MainBlockStatus < FEE_BS_MAX )
            && ( SubBlockStatus  < FEE_BS_MAX ))
            {
                Rtn = E_OK;
            }
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_ChkLastWritePosLastRecAddr                           */
/* Description   | Function to check last position information data.        */
/* Preconditions | None                                                     */
/* Parameters    | LastWPosInfo                                             */
/*               | CPUDTFInfo                                               */
/*               | AreaNum                                                  */
/* Return Value  | Check result.                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_ChkLastWritePosLastRecAddr(
    P2CONST( Fee_LwpInfType, AUTOMATIC, FEE_VAR_NO_INIT ) LastWPosInfo,
    P2CONST( Fee_CpuDtfType, AUTOMATIC, TYPEDEF         ) CPUDTFInfo
){
    Std_ReturnType  Rtn = E_NOT_OK;
    uint16          RcrdDataAreaStartAddr;
    uint32          WriteLastRecMngRelAddr;
    uint32          WriteLastRecDatRelAddr;
    uint32          MaxRecMngRelAddr;

    RcrdDataAreaStartAddr = CPUDTFInfo->ptstAreaInf->u2RcrdDataAreaStartAddr;

    /* Check a last record address of a management area. */
    WriteLastRecMngRelAddr = Fee_ConvAddr_AbsToSectorTopRelative( LastWPosInfo->u4WriteLastRecMngAbsAddr );
    MaxRecMngRelAddr = (uint32)RcrdDataAreaStartAddr - (uint32)FEE_RECORDMNGINFOLEN;
    if(( (uint32)( FEE_STARTRECORDPOS - (uint32)FEE_RECORDMNGINFOLEN ) <= WriteLastRecMngRelAddr )
    && (((( WriteLastRecMngRelAddr + (uint32)FEE_RECORDMNGINFOLEN ) - (uint32)FEE_STARTRECORDPOS ) % (uint32)FEE_RECORDMNGINFOLEN )
        == (uint32)FEE_LIB_RESIDUAL_VAL_CALC_MULTIPLES_REC )
    && ( WriteLastRecMngRelAddr <= MaxRecMngRelAddr ))
    {
        /* Check a last record address of a data area. */
        if( LastWPosInfo->u1SetKind == FEE_LWPREAD )
        {
            /* Check a last record is invalid.                                                 */
            /*      Note : Fee_Read() only uploads a last record address of a management area. */
            /*             A last record address of a data area is invalid.                    */
            if( LastWPosInfo->u4WriteLastRecDatAbsAddr == FEE_ADDRESS_INVALID )
            {
                Rtn = E_OK;
            }
        }
        else /* LastWPosInfo->u1SetKind != FEE_LWPREAD */
        {
            WriteLastRecDatRelAddr = Fee_ConvAddr_AbsToSectorTopRelative( LastWPosInfo->u4WriteLastRecDatAbsAddr );
            if((( (uint32)RcrdDataAreaStartAddr - (uint32)FEE_DATAAREA_REC_TAIL_OFFSET ) <= WriteLastRecDatRelAddr )
            && ( WriteLastRecDatRelAddr <= ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE - (uint32)FEE_DATAAREA_REC_TAIL_OFFSET ))
            && ((( WriteLastRecDatRelAddr + (uint32)FEE_DATAAREA_REC_TAIL_OFFSET ) % (uint32)FEE_DATA_FLASH_READ_SIZE )
                == (uint32)FEE_LIB_RESIDUAL_VAL_CALC_MULTIPLES_REC ))
            {
                Rtn = E_OK;
            }
        }
    }

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_ConvAddr_AbsToSectorTopRelative                      */
/* Description   | Absolute addresses are converted to relative addresses   */
/* Preconditions | None                                                     */
/* Parameters    | u4 _ absolute _ address: absolute address                */
/* Return Value  | Translation result: Relative address                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_ConvAddr_AbsToBaseRelative( uint32 u4_absolute_address )
{
    uint32 u4_relative_address;

    /* Calculate the relative address to the head address from the absolute address of the flash */
    u4_relative_address = u4_absolute_address - (uint32)FEE_DATA_FLASH_ADDRESS_START;

    return u4_relative_address;
}

/****************************************************************************/
/* Function Name | Fee_ConvAddr_AbsToSectorTopRelative                      */
/* Description   | Absolute address is converted to a relative address      */
/*               | from the beginning of the sector                         */
/* Preconditions | None                                                     */
/* Parameters    | u4_relative_address   : relative address                 */
/* Return Value  | Translation result    : Absolute address                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_ConvAddr_AbsToSectorTopRelative( uint32 u4_absolute_address )
{
    uint32 u4_relative_address;

    /* Calculate the relative address to the sector head address from the absolute address of the flash */
    u4_relative_address = u4_absolute_address - (uint32)FEE_DATA_FLASH_ADDRESS_START;
    u4_relative_address = u4_relative_address % (uint32)FEE_DATA_FLASH_SECTOR_SIZE;
    
    return u4_relative_address;
}

/****************************************************************************/
/* Function Name | Fee_ConvAddr_RelativeToAbsolute                          */
/* Description   | Relative address is converted to absolute address        */
/* Preconditions | None                                                     */
/* Parameters    | u4_relative_address   : relative address                 */
/* Return Value  | Translation result    : Absolute address                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_ConvAddr_RelativeToAbsolute( uint32 u4_relative_address )
{
    uint32 u4_absolute_address;

    /* Calculate absolute address from relative address */
    u4_absolute_address = u4_relative_address + (uint32)FEE_DATA_FLASH_ADDRESS_START;

    return u4_absolute_address;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/23                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
