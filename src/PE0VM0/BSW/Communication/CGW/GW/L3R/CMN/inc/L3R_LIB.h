/****************************************************************************/
/*  ファイル名      L3R_LIB.h                                               */
/*  モジュール名    ライブラリ定義                                          */
/*  機能            L3Rライブラリ                                           */
/*  備考                                                                    */
/*  変更履歴        V1.00   2013.05.13  Y.Kaseda                            */
/*                        新規作成            CGWコーディング規約 V1.00準拠 */
/*                  V1.01   2013.09.26  Y.tabuchi                           */
/*                        読み込みのみの変数がROM領域に割り付けられるよう   */
/*                        修正                                              */
/*                  V1.02   2017.03.03  Y.Katayama                          */
/*                        19PF向け型定義対応                                */
/*                  V1.03   2018/05/11  A.Yasui(FSI)                        */
/*                        中継のCHとPRTCL_BITの命名規則明確化レベルアップ   */
/*                  V1.04   2018/10/25  T.Yamamura                          */
/*                        コードレベルアップ対応(オブジェクト不変)          */
/*                  V2.00   2018.11.21 Y.Katayama                           */
/*                        中継改善(オブジェクト不変）                       */
/****************************************************************************/
#ifndef L3R_LIB_H
#define L3R_LIB_H

#include "Std_Types.h"
#include "L3R_Common.h"

/*----マクロ定義------------------------------------------------------------*/

/*----外部変数宣言----------------------------------------------------------*/

/*----プロトタイプ宣言------------------------------------------------------*/
#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/**
 * @fn			void L3R_LIB_memcpy
 * @brief		データコピー
 * @details		指定した格納先にデータをコピーする
 * @param[out]	dst[]	データコピー先
 * @param[in]	src[]	データコピー元
 * @param[in]	size	コピーデータサイズ
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void L3R_LIB_memcpy(uint8 dst[], const uint8 src[], uint16 size) __attribute__((always_inline,unused));
static inline void L3R_LIB_memcpy(uint8 dst[], const uint8 src[], uint16 size)
{
	uint8 *dstTmp = dst;
	const uint8	*srcTmp = src;
	uint32 sizeTmp = size;

	while (sizeTmp > 0U) {
		*dstTmp = *srcTmp;
		dstTmp++;
		srcTmp++;
		sizeTmp--;
	}
}

/**
 * @fn			void L3R_LIB_memset
 * @brief		データセット
 * @details		指定した格納先にデータをセットする
 * @param[out]	dst[]	データセット先
 * @param[in]	data	セット対象データ
 * @param[in]	size	セットデータサイズ
 * @return		なし
 * @attention	なし
 * @note		なし
 */
static inline void L3R_LIB_memset(uint8 dst[], uint8 data, uint16 size) __attribute__((always_inline,unused));
static inline void L3R_LIB_memset(uint8 dst[], uint8 data, uint16 size)
{
	uint8 *dstTmp = dst;
	uint32 sizeTmp = size;

	while (sizeTmp > 0U) {
		*dstTmp = data;
		dstTmp++;
		sizeTmp--;
	}
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

#endif	/* L3R_LIB_H */
