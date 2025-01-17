/* Fee_Dfc.c v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/DFC/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Common.h"

#include "../inc/Fee_Dfc.h"
#include "../inc/Fee_Dfc_Internal.h"
#include "../inc/Fee_Dfc_Ram.h"
#include "../inc/Fee_DfcMpu.h"

#include <Fls.h>
#include <Mscd_Common.h>

#include "../inc/Fee_ExConst.h"

#include "../inc/Fee_Mpu_Dev_Const.h"
#include "../inc/Fee_Lib.h"
#include "../inc/Fee_Legacy.h"
#include "../inc/Fee_FlsWrp.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Return Values and Hook Result */
#define FEE_DFC_RSP_OK                      ((uint8)0x00)   /* Success         */
#define FEE_DFC_RSP_NG_PARAM_ERROR          ((uint8)0x81)   /* Parameter error */
#define FEE_DFC_RSP_NG_DECLINE              ((uint8)0x82)   /* Request reject  */
#define FEE_DFC_RSP_NG_BUSY                 ((uint8)0x83)   /* Failure(busy)   */
#define FEE_DFC_RSP_NG_HARD_ERROR           ((uint8)0x84)   /* Hard error      */
#define FEE_DFC_RSP_NG_RAM_ERROR            ((uint8)0x85)   /* RAM error       */
#define FEE_DFC_RSP_NG_BLANK_ERROR          ((uint8)0x86)   /* Blank error     */

/* データFlashのベースアドレス */
#define FEE_DFC_BASEADDRESS     FEE_DATA_FLASH_ADDRESS_START

/* 消去単位サイズ */
#define FEE_DFC_DEFAULT_ERASE_SIZE      (FEE_DATA_FLASH_SECTOR_SIZE)

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

/****************************************************************************/
/* Function Name | Fee_Dfc_CheckRAM                                         */
/* Description   | Function to check RAMs.                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Check result.                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_Dfc_CheckRAM( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    Std_ReturnType Rtn = E_NOT_OK;

    if((( Fee_DrvWrap_State            ^ Fee_DrvWrap_StateSub            ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_DrvWrap_WrittenAdr       ^ Fee_DrvWrap_WrittenAdrSub       ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_Dfc_BlankCheckEndAdr     ^ Fee_Dfc_BlankCheckEndAdrSub     ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_Dfc_MaxBlankCheckNum     ^ Fee_Dfc_MaxBlankCheckNumSub     ) == (uint32)FEE_MIRROR_CHECK_UINT32 )
    && (( Fee_DrvWrap_BlankCheck_State ^ Fee_DrvWrap_BlankCheck_StateSub ) == (uint32)FEE_MIRROR_CHECK_UINT32 ))
    {
        Rtn = E_OK;
    }

    return Rtn;
#else /* FEE_USE_REDUNDANCY_RAM == STD_OFF */
    return E_OK;
#endif /* FEE_USE_REDUNDANCY_RAM */
}

/****************************************************************************/
/* Function Name | Fee_Dfc_SetRAMSub                                        */
/* Description   | Function to set value to sub RAMs from main RAMs.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Dfc_SetRAMSub( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    Fee_DrvWrap_StateSub            = (uint32)(~Fee_DrvWrap_State);
    Fee_DrvWrap_WrittenAdrSub       = (uint32)(~Fee_DrvWrap_WrittenAdr);
    Fee_Dfc_BlankCheckEndAdrSub     = (uint32)(~Fee_Dfc_BlankCheckEndAdr);
    Fee_Dfc_MaxBlankCheckNumSub     = (uint32)(~Fee_Dfc_MaxBlankCheckNum);
    Fee_DrvWrap_BlankCheck_StateSub = (uint32)(~Fee_DrvWrap_BlankCheck_State);
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

    return;
}

/****************************************************************************/
/*  関数名      : void Fee_Dfc_Write(const uint32 Address,              */
/*                  const uint8 * ptu1Data)                 */
/*  処理名      : 書込み関数                                                */
/*  機能説明    : DTFから要求されたデータをデータFlashに書き込む            */
/*  引数        : const uint32 Address : データを書込むアドレス         */
/*              : const uint32 Data    : データFlash に書込むデータ     */
/*              : const uint16 DataLen : Write Data Length                  */
/*  戻り値      : void                                                      */
/*  備考        : なし                                                      */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Dfc_Write(const uint32 Address, P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1Data, const uint16 u2Len)
{
    Std_ReturnType ret;

    /* FLSに書込み要求を出す */
    ret = Fee_FlsWrp_Write((Address - (Fls_AddressType)FEE_DFC_BASEADDRESS), ptu1Data, (Fls_LengthType)u2Len);

    if( ret == (Std_ReturnType)E_OK )
    {
        Fee_CpuDtfInfo.u4DFCTimerCnt = Fee_HwLmtWriteTime;
    }

    /* FLSの応答を上位層が期待する応答へ変換して保存 */
    Fee_DrvWrap_ConvDrvReqResult(ret);

    return;
}
/****************************************************************************/
/*  関数名      : void Fee_Dfc_Erase(const uint32 Address)          */
/*  処理名      : 消去関数                                                  */
/*  機能説明    : 指定されたアドレスから始まるブロックの内容を消去する      */
/*  引数        : const uint32 Address : 消去を開始するアドレス         */
/*  戻り値      : void                                                      */
/*  備考        : なし                                                      */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Dfc_Erase(const uint32 Address)
{
    Std_ReturnType ret;

    /* FLSに消去要求を出す */
    ret = Fee_FlsWrp_Erase((Address - (Fls_AddressType)FEE_DFC_BASEADDRESS), (Fls_LengthType)FEE_DFC_DEFAULT_ERASE_SIZE);

    if( ret == (Std_ReturnType)E_OK )
    {
        Fee_CpuDtfInfo.u4DFCTimerCnt = Fee_HwlmtInitTime;
    }

    /* DTFDの応答を上位層が期待する応答へ変換して保存 */
    Fee_DrvWrap_ConvDrvReqResult(ret);

    return;
}

/****************************************************************************/
/*  関数名      : void Fee_Dfc_BlankCheck                                   */
/*  処理名      : ブランクチェック関数                                      */
/*  機能説明    : 指定アドレスから始まるブロックのブランクチェックを行う    */
/*  引数        : const uint32 StartTailAddress : ブランクチェック開始アドレス   */
/*              : const uint32 EndTopAddress    : ブランクチェック終了アドレス   */
/*              : uint32 MaxBlankCheckNum       : The number of blank check in one cycle.   */
/*  戻り値      : void                                                      */
/*  備考        : なし                                                      */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Dfc_BlankCheck(
    const uint32 StartTailAddress,
    const uint32 EndTopAddress,
    uint32 MaxBlankCheckNum
){
    /* ブランクチェック状態を「実行中」に設定 */
    Fee_DrvWrap_BlankCheck_State = FEE_DFC_STATUS_BUSY;

    /* ブランクチェックの開始時は、ブランクチェック結果（最終書込みレコードアドレス）にブロック末尾アドレスを入れる */
    Fee_DrvWrap_WrittenAdr = StartTailAddress - (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE;
    Fee_Dfc_BlankCheckEndAdr = EndTopAddress;
    Fee_Dfc_MaxBlankCheckNum = MaxBlankCheckNum;

    /* ブランクチェック実行 */
    Fee_DrvWrap_BlankCheck_Main();

    return;
}

#if ( MSCD_FREESPACE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Fee_Dfc_GetBlankCheckResult                              */
/* Description   | Function to get blank check result.                      */
/* Preconditions | None                                                     */
/* Parameters    | WriteAddr : The flash address that is not a blank.       */
/* Return Value  | FEE_DFC_STATUS_OK                                        */
/*               | FEE_DFC_STATUS_ERROR                                     */
/*               | FEE_DFC_STATUS_BUSY                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Dfc_GetBlankCheckResult(
    P2VAR( uint32, AUTOMATIC, TYPEDEF ) WriteAddr
){
    uint32 Rtn = Fee_DrvWrap_BlankCheck_State;

    if( Rtn == FEE_DFC_STATUS_ERROR )
    {
        *WriteAddr = Fee_DrvWrap_WrittenAdr;
    }

    return Rtn;
}
#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

/****************************************************************************/
/*  関数名      : uint32 Fee_Dfc_ExecBlankCheck(void)                       */
/*  処理名      : 継続ブランクチェック                                      */
/*  機能説明    : 指定アドレスから始まるブロックのブランクチェックを行う    */
/*  引数        : なし                                                      */
/*  戻り値      : uint32 : データFlash動作確認結果                          */
/*                  FEE_DFC_STATUS_OK    全領域ブランク                     */
/*                  FEE_DFC_STATUS_ERROR 非ブランク領域あり                 */
/*                  FEE_DFC_STATUS_BUSY  ブランクチェック中                 */
/*  備考        : なし                                                      */
/****************************************************************************/
FUNC( uint32 ,FEE_CODE )
Fee_Dfc_ExecBlankCheck( void )
{
    if( Fee_DrvWrap_BlankCheck_State == FEE_DFC_STATUS_BUSY )
    {
        /* ブランクチェック実行 */
        Fee_DrvWrap_BlankCheck_Main();
    }

    return Fee_DrvWrap_BlankCheck_State;
}

/****************************************************************************/
/*  関数名      : void Fee_DrvWrap_BlankCheck_Main(void)                        */
/*  処理名      : ブランクチェック実行                                      */
/*  機能説明    : 指定アドレスから始まるブロックのブランクチェックを行う    */
/*  引数        : なし                                                      */
/*  戻り値      : なし                                                      */
/*  備考        : なし                                                      */
/****************************************************************************/
FUNC(void , FEE_CODE) Fee_DrvWrap_BlankCheck_Main(void)
{
    uint8  DfcMpuResult;
    uint32 NotBlankAddress;
    uint32 BlankCheckStartAdr;
    uint32 BlankCheckEndAdr;
    uint32 BlankCheckLength;
    uint32 MaxLength;
    uint32 MaxBlankCheckNum = Fee_Dfc_MaxBlankCheckNum;

    if( MaxBlankCheckNum > (uint32)FEE_BLANKCHECK_COUNT_ZERO )
    {
        BlankCheckStartAdr = Fee_DrvWrap_WrittenAdr + (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE;
        BlankCheckEndAdr = Fee_Dfc_BlankCheckEndAdr;
        NotBlankAddress = BlankCheckStartAdr;

        /* Set length of blank check. */
        MaxLength = MaxBlankCheckNum * (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE;
        BlankCheckLength = BlankCheckStartAdr - BlankCheckEndAdr;
        if( BlankCheckLength > MaxLength )
        {
            BlankCheckLength = MaxLength;
        }

        /* Execute blank check. */
        DfcMpuResult = Fee_DfcMpu_SyncNotBlankAddress( ( BlankCheckStartAdr - BlankCheckLength ), BlankCheckLength, &NotBlankAddress );
        if( DfcMpuResult == FEE_DFCMPU_RESULT_OK )
        {
            /* Set last written position. */
            Fee_DrvWrap_WrittenAdr = NotBlankAddress - ( NotBlankAddress % (uint32)FEE_DATA_FLASH_ECC_FIX_SIZE );
            Fee_DrvWrap_BlankCheck_State = FEE_DFC_STATUS_ERROR;
        }
        else if( DfcMpuResult == FEE_DFCMPU_RESULT_BLANK )
        {
            /* Update search address. */
            Fee_DrvWrap_WrittenAdr -= BlankCheckLength;
            if( Fee_DrvWrap_WrittenAdr < BlankCheckEndAdr )
            {
                /* In case of whole target area is blank. */
                Fee_DrvWrap_BlankCheck_State = FEE_DFC_STATUS_OK;
            }
        }
        else
        {
            /* Assume that last written position is found. */
            Fee_DrvWrap_BlankCheck_State = FEE_DFC_STATUS_ERROR;
        }
    }

    return;
}
/****************************************************************************/
/* Function Name | Fee_Dfc_ExecFlsMainFunction                              */
/* Description   | Run the Data Flash Driver, and return the results.       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Result of running Data Flash                             */
/*               |  FEE_DFC_STATUS_OK    Processing Success                 */
/*               |  FEE_DFC_STATUS_ERROR Error Occurred                     */
/*               |  FEE_DFC_STATUS_BUSY  Continue Processing                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_Dfc_ExecFlsMainFunction(void)
{
    uint32 ret;
    MemIf_JobResultType FlsJobResult;
    uint32 drvwrap_state_current = Fee_DrvWrap_State;

    Fee_FlsWrp_MainFunction();

    FlsJobResult = Fee_FlsWrp_GetJobResult();

    if( drvwrap_state_current == FEE_DFC_STATUS_OK ){
        Fee_DrvWrap_State = FEE_DFC_STATUS_OK;
    }
    else if( drvwrap_state_current == FEE_DFC_STATUS_BUSY )
    {
        switch( FlsJobResult ){
            case MEMIF_JOB_OK:
                Fee_DrvWrap_State = FEE_DFC_STATUS_OK;
                break;
            case MEMIF_JOB_PENDING:
                Fee_DrvWrap_State = FEE_DFC_STATUS_BUSY;
                break;
            default:
                Fee_DrvWrap_State = FEE_DFC_STATUS_ERROR;
                break;
        }
    }
    else{
        Fee_DrvWrap_State = FEE_DFC_STATUS_ERROR;
    }

    if( FlsJobResult == MEMIF_JOB_PENDING )
    {
        ret = FEE_DFC_STATUS_BUSY;
    }
    else
    {
        ret = Fee_DrvWrap_State;
        Fee_CpuDtfInfo.u4DFCTimerCnt = FEE_TM_INVALID;
    }

    return (ret);
}

/****************************************************************************/
/*  関数名      : void Fee_Dfc_End(void)                                */
/*  処理名      : フラッシュ操作終了関数                                    */
/*  機能説明    : フラッシュ操作の終了を行う                                */
/*  引数        : void                                                      */
/*  戻り値      : void                                                      */
/*  備考        : なし                                                      */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Dfc_End(void)
{
    /* 結合層のRAMを初期化 */
    Fee_DrvWrap_Init();

    return;
}

/****************************************************************************/
/* Function Name | Fee_Dfc_Cancel                                           */
/* Description   | Function to initialize under module.                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Dfc_Init( void )
{
    /* Do Nothing */
    return;
}

/****************************************************************************/
/* Function Name | Fee_Dfc_Cancel                                           */
/* Description   | Function to cancel under module.                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Dfc_Cancel( void )
{
    Fee_FlsWrp_Cancel();

    return;
}

/****************************************************************************/
/*  関数名      : uint32 Fee_Dfc_GetFLAP(void)                      */
/*  処理名      : FLAP 取得関数                                             */
/*  機能説明    : ブランクチェックで判明したブランクで無い箇所の            */
/*                アドレスを返却する                                        */
/*  引数        : void                                                      */
/*  戻り値      : U4 : ブランクで無い箇所のアドレス                         */
/*  備考        : なし                                                      */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_Dfc_GetFLAP(void)
{
    /* 保存してある最終書き込みレコードの先頭アドレスを返す */
    return (Fee_DrvWrap_WrittenAdr);
}

/****************************************************************************/
/* Function Name | Fee_Dfc_GetStatus                                        */
/* Description   | Function to return the Fls module status.                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Fls module status                                        */
/*               |  MEMIF_IDLE          :The Fls module is currently idle.  */
/*               |  MEMIF_BUSY          :The Fls module is currently busy.  */
/*               |  MEMIF_UNINIT        :The Fls module has not been        */
/*               |                       initialized (yet).                 */
/*               |  MEMIF_BUSY_INTERNAL :A fatal error has occured.         */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( MemIf_StatusType, FEE_CODE ) Fee_Dfc_GetStatus(void)
{
    MemIf_StatusType FlsStatus;

    FlsStatus = Fee_FlsWrp_GetStatus();

    return (FlsStatus);
}

/****************************************************************************/
/* Function Name | Fee_DrvWrap_ConvDrvReqResult                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | result                                                   */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_DrvWrap_ConvDrvReqResult(
    const Std_ReturnType result
){
    uint32 drvwrap_state_new;

    switch(result){
        /* 「処理成功」の場合「処理継続」を返す */
        case E_OK:
            drvwrap_state_new = FEE_DFC_STATUS_BUSY;
            break;

        /* 「要求拒否」「パラメータエラー」「その他(異常)」の場合「エラー発生」を返す */
        default:
            drvwrap_state_new = FEE_DFC_STATUS_ERROR;
            break;
    }

    Fee_DrvWrap_State = drvwrap_state_new;

    return;
}

/****************************************************************************/
/*  関数名      : void Fee_DrvWrap_Init(void)                               */
/*  処理名      : RAMクリア関数                                             */
/*  機能説明    : 結合層内のRAMをクリアする                                 */
/*  引数        : void                                                      */
/*  戻り値      : void                                                      */
/*  備考        : なし                                                      */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_DrvWrap_Init(void)
{
    Fee_DrvWrap_State = FEE_DFC_STATUS_OK;
    Fee_DrvWrap_WrittenAdr          = FEE_DFC_ADDRESS_INVALID;
    Fee_Dfc_BlankCheckEndAdr        = FEE_DFC_ADDRESS_INVALID;
    Fee_Dfc_MaxBlankCheckNum        = FEE_BLANKCHECK_COUNT_ZERO;
    Fee_DrvWrap_BlankCheck_State    = FEE_DFC_STATUS_OK;

    return;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/19                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
