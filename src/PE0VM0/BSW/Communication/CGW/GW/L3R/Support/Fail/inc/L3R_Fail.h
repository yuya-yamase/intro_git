/****************************************************************************/
/*  ファイル名      L3R_Fail.h                                              */
/*  モジュール名    変換機能(ToyotaCAN専用)                                 */
/*  機能            個別プロトコル情報を共通フォーマットに変換する          */
/*  備考            Toyota向けCANプロトコル専用                             */
/*  変更履歴        V1.00   2013.05.13  Y.Kaseda                            */
/*                        新規作成            CGWコーディング規約 V1.00準拠 */
/*                  V1.01   2013.11.19  R.Moriyama                          */
/*                        MSG-ID対応コンパイルスイッチ導入                  */
/*                  V1.02   2014.05.06  R.Moriyama                          */
/*                      ・関数マクロを追加                                  */
/*                      ・関数マクロ化に伴い、u1g_ConvertPhysChtoLogicCh、  */
/*                        u1g_ConvertLogicChtoPhysChに名称変更              */
/*                      ・u1g_GW_RTR_TConvertor_GetDiagDataに引数を追加     */
/*                  V1.03   2014.06.02  H.Tanaka                            */
/*                        MPU異常時の処理追加                               */
/*                  V1.04   2014.06.04  R.Moriyama                          */
/*                        MISRA2004対応                                     */
/*                        ・u1g_GW_RTR_TConvertor_ReceiveCanDataの          */
/*                          引数：pu1t_Dataからconstを削除                  */
/*                  V1.05   2014.08.08  K.Yokooka                           */
/*                        課題No.17816対応                                  */
/*                        ・送信要求関数に引数 DelIndexNum追加              */
/*                        ・送信要求結果の定義を追加                        */
/*                  V1.06   2015.01.14  N.Shiraishi                         */
/*                        SD-A対応：物理論理chの結合を変更                  */
/*                  V1.20   2014.04.28  H.Tanaka                            */
/*                        SD-A対応：電動化NM仕様(バッファリング)対応        */
/*                  V1.21   2016.02.25  T.Matsumoto                         */
/*                        制御データ中継モード対応                          */
/*                  V1.22   2016.04.01  H.Tanaka                            */
/*                        SD-2対応：MPU異常発生時の処理削除、Gate課題対応   */
/*                  V1.23   2016.04.12  T.Nishiyama                         */
/*                        SD-2対応：チャネルマスタ対応(844655)              */
/*                  V1.24   2017.03.03  Y.Katayama                          */
/*                        19PF向け型定義対応                                */
/*                        制御データ中継モードの処理を削除                  */
/*                  V2.00   2018.05.16  T.Yamamura                          */
/*                        ・u1g_GW_RTR_TConvertor_ConvertLogicBitMap()削除  */
/*                  V3.00   2018.11.21  Y.Katayama                          */
/*                        中継改善(オブジェクト不変）                       */
/****************************************************************************/
#ifndef	L3R_FAIL_H
#define	L3R_FAIL_H

#include "L3R_Common.h"
#include "L3R_config.h"

/*----マクロ定義------------------------------------------------------------*/

/*----プロトタイプ宣言------------------------------------------------------*/
#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
extern uint16 L3R_Fail_FailChBit;
#define GW_L3R_STOP_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"

#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
extern void L3R_Fail_Init(void);
extern void L3R_Fail_MainTask(void);
extern void L3R_Fail_SendLockNotify(uint8 ch);
extern void L3R_Fail_BusoffNotify(uint8 ch);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"


/*----関数マクロ------------------------------------------------------------*/

#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/**
 * @fn			uint16 L3R_Fail_GetFailChBitAll(void)
 * @brief		フェール発生CH情報取得
 * @details		全チャンネル分のフェール発生CH情報を取得する
 * @param		なし
 * @return		全チャンネル分のフェール発生CH情報
 * @attention	なし
 * @note		なし
 */
static inline uint16 L3R_Fail_GetFailChBitAll(void) __attribute__((always_inline,unused));
static inline uint16 L3R_Fail_GetFailChBitAll(void)
{
   return L3R_Fail_FailChBit;
}

/**
 * @fn			uint16 L3R_Fail_GetFailChBit(uint8 ch)
 * @brief		指定チャンネルフェール発生CH情報取得
 * @details		指定チャンネルのフェール発生CH情報を取得する
 * @param		ch		Ch番号
 * @return		指定チャンネルフェール発生CH情報
 * @attention	なし
 * @note		なし
 */
static inline uint16 L3R_Fail_GetFailChBit(uint8 ch) __attribute__((always_inline,unused));
static inline uint16 L3R_Fail_GetFailChBit(uint8 ch)
{
   return (L3R_Fail_FailChBit & (((uint16)L3R_ON) << (ch)));
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

/**
 * @fn			L3R_Fail_SetFailChBit(ch)
 * @brief		フェール発生CH情報セット処理
 * @details		フェール発生Ch毎のビットをセットする
 * @param[in]	ch		Ch番号
 * @return		なし
 * @attention	なし
 * @note		なし
 */
#define L3R_Fail_SetFailChBit(ch)											\
	(L3R_Fail_FailChBit |= (((uint16)L3R_ON) << (ch)))

/**
 * @fn			L3R_Fail_ClrFailChBit()
 * @brief		フェール発生CH情報クリア処理
 * @details		フェール発生Ch毎のビットをクリアする
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 */
#define L3R_Fail_ClrFailChBit()											\
	(L3R_Fail_FailChBit = L3R_LOG_BIT_NULL)

#endif	/* L3R_FAIL_H */
