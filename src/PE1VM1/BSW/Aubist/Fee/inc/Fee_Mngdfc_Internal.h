/* Fee_Mngdfc_Internal.h v2-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/MNGDFC/INTERNAL/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_MNGDFC_INTERNAL_H
#define FEE_MNGDFC_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_NEXT_CWRITENUM_OFFSET       (1U)    /* 連続書き込み数の次要素のオフセット */
#define FEE_CWRITENUM_ZERO              (0U)    /* 連続書き込み数0 */
#define FEE_CWRITE_LAST_INDEX_OFFSET    (1U)    /* 最後の連続書き込みデータを示すインデックスを算出するためのオフセット */
#define FEE_HALFWORD_DATA_INVALID       (0U)    /* ハーフワードデータ無効値 */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/* データFlash制御管理書き込み終了処理 */
FUNC(void, FEE_CODE) Fee_MngDfcEndWriteProcess( void );
/* データFlash制御管理ブランクチェック終了処理 */
FUNC(void, FEE_CODE) Fee_MngDfcEndBlanckCheckProcess( void );
/* データFlash制御管理ブランクチェック終了処理 */
FUNC(void, FEE_CODE) Fee_MngDfcEndEraseProcess( void );

FUNC(uint32, FEE_CODE) Fee_MngDfcComCWrite(
    uint32 u4tDFCResult
);
FUNC(uint32, FEE_CODE) Fee_MngDfcComRetry( void );
FUNC(void, FEE_CODE) Fee_MngDfcReqWrite( void );
/* データFlash制御管理共通処理 */
FUNC(uint32, FEE_CODE) Fee_MngDfcCom( void );

FUNC( uint32, FEE_CODE )
Fee_MngDfc_ExecDfcAndCheckStatus( void );

FUNC( void, FEE_CODE )
Fee_MngDfc_VolChkWrite(
    const uint32 u4Address,
    P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1Data,
    const uint16 u2Len,
    const uint16 u2Flag
);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_MNGDFC_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  2-0-0          :2021/06/02                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
