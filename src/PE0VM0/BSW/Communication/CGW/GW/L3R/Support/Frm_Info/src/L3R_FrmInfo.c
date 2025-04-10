/****************************************************************************/
/*            Copyright DENSO Corporation. All rights reserved.             */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_FrmInfo.c
 * @brief		中継フレーム情報記憶
 * @details		中継フレームの送受信を記憶、公開する
 * @date		v1.00   2017/10/17   N.Shiraishi(FSI)		新規作成
 * @date		v1.10   2017/12/18   Y.Katayama(FSI)		CANIDを記憶、公開する機能の追加<BR>
 *															特定イベントフレームへの対応
 * @date		v1.11   2018/10/25   T.Yamamura(FSI)		コードレベルアップ対応(オブジェクト不変)
 * @date		v2.00   2018/11/21   Y.Katayama(FSI)		中継改善(オブジェクト不変)
 * @date		v6.00	2020/12/07   T.Yamamura(FSI)			[Post19CY] 29Bit対応 
 * @attention	なし
 * @note		なし
 ****************************************************************************/
/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "L3R_Common.h"
#include "L3R_FrmInfo.h"

/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/
#define L3R_FRM_SNDFLAGNUM				2U	/**< フラグ(更新用、参照用)数 */
#define L3R_FRM_ARRAYLAST_IDX			(L3R_FRM_SNDFLAGNUM - 1U)	/**< 配列最後尾のインデックス(参照用ポインタ算出用) */
#define L3R_FRM_BUF_BIT_ENABLE			0x01U	/* 配列Indexの有効bit(1bit:0 or 1) */
#define L3R_FRM_DEFAULT_UPDATE_IDX		0U	/**< 更新用フラグデフォルトIndex */
#define L3R_CANID_ARRAYSIZE				8U	/**< CANID記憶配列サイズ(制約:サイズには2のべき乗を設定すること) */

/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*		タイプ宣言															*/
/*--------------------------------------------------------------------------*/

/**	@struct	L3R_DIAG_FRMINFO
 * 	@brief	ダイアグ中継フレーム記憶情報定義
 */
typedef struct {
	uint32 CanId[L3R_CANID_ARRAYSIZE];		/* CANID */
	uint16 RcvFrmNum;						/* 受信フレーム数 */
	uint8 writepoint;						/* 書き込み位置 */
	boolean SndFlg;							/* 受信情報 */
} L3R_DIAG_FRMINFO;


/*--------------------------------------------------------------------------*/
/*		ファイル内変数														*/
/*--------------------------------------------------------------------------*/
/**	@var	L3R_Frm_UpdateIndex
 *	@brief	更新用中継フレーム受信フラグ配列Index
 */
#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
static uint8 L3R_Frm_UpdateIndex;

/**	@var	L3R_Diag_FrmInfo
 *	@brief	ダイアグ中継フレーム記憶情報構造体配列
 */
static L3R_DIAG_FRMINFO L3R_Diag_FrmInfo[L3R_FRM_SNDFLAGNUM];


/**	@var	L3R_Diag_SndFlgUpdate
 *	@brief	更新用ダイアグ中継フレーム受信フラグポインタ
 */
static L3R_DIAG_FRMINFO* L3R_Diag_SndFlgUpdate;

/**	@var	L3R_Diag_SndFlgReference
 *	@brief	参照用ダイアグ中継フレーム受信フラグポインタ
 */
static L3R_DIAG_FRMINFO* L3R_Diag_SndFlgReference;
#define GW_L3R_STOP_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/

#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/*************************************************************************//**
 * @fn			void L3R_FrmInfo_Initialize(void)
 * @brief		中継フレームの受信情報を初期化する
 * @details		中継フレームの受信情報を初期化する
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 ****************************************************************************/
void L3R_FrmInfo_Initialize(void)
{
	uint16 Index;
	L3R_Frm_UpdateIndex = L3R_FRM_DEFAULT_UPDATE_IDX;
	
	/* 更新用、参照用ポインタの初期化 */
	/* L3R_FrmInfo_SwitchFlag() で行う更新用と参照用の切り替え方法に合わせて処理を行う */
	/* ダイアグ中継フレーム用 */
	L3R_Diag_SndFlgUpdate = &L3R_Diag_FrmInfo[L3R_Frm_UpdateIndex];
	L3R_Diag_SndFlgReference = &L3R_Diag_FrmInfo[L3R_FRM_ARRAYLAST_IDX - L3R_Frm_UpdateIndex];
	
	/* 受信情報の初期化 */
	/* ダイアグ中継フレーム用 */
	L3R_Diag_SndFlgUpdate->SndFlg = FALSE;
	L3R_Diag_SndFlgReference->SndFlg = FALSE;
	
	/* 受信フレーム数の初期化 */
	/* ダイアグ中継フレーム用 */
	L3R_Diag_SndFlgUpdate->RcvFrmNum = L3R_CLR;
	L3R_Diag_SndFlgReference->RcvFrmNum = L3R_CLR;
	
	/* CANID記憶バッファ書き込み位置の初期化 */
	/* ダイアグ中継フレーム用 */
	L3R_Diag_SndFlgUpdate->writepoint = L3R_CLR;
	L3R_Diag_SndFlgReference->writepoint = L3R_CLR;
	
	/* CANID記憶バッファの初期化 */
	for(Index = L3R_CLR; Index < L3R_CANID_ARRAYSIZE; Index++){
		/* ダイアグ中継フレーム用 */
		L3R_Diag_SndFlgUpdate->CanId[Index] = L3R_CLR;
		L3R_Diag_SndFlgReference->CanId[Index] = L3R_CLR;
	}
	
	return;
}

/*************************************************************************//**
 * @fn			void L3R_FrmInfo_SndDiagRlyFrm(uint32 CanId)
 * @brief		ダイアグ中継フレームの受信情報を記憶する
 * @details		ダイアグ中継フレームの受信情報を記憶する
 * @param[in]	CanId	CANID
 * @return		なし
 * @attention	なし
 * @note		なし
 ****************************************************************************/
void L3R_FrmInfo_SndDiagRlyFrm(uint32 CanId)
{
	L3R_Diag_SndFlgUpdate->SndFlg = TRUE;
	
	L3R_Diag_SndFlgUpdate->RcvFrmNum++;
	L3R_Diag_SndFlgUpdate->CanId[L3R_Diag_SndFlgUpdate->writepoint] = CanId;
	L3R_Diag_SndFlgUpdate->writepoint = (L3R_Diag_SndFlgUpdate->writepoint + (1U)) & (L3R_CANID_ARRAYSIZE - (1U));

	return;
}

/*************************************************************************//**
 * @fn			boolean L3R_FrmInfo_IsSndDiagRlyFrm(void)
 * @brief		ダイアグ中継フレーム受信情報を公開する
 * @details		ダイアグ中継フレーム受信情報を公開する
 * @param		なし
 * @return		ダイアグフレーム受信情報
 * @retval		TRUE	受信あり
 * @retval		FALSE	受信なし
 * @attention	なし
 * @note		なし
 ****************************************************************************/
boolean L3R_FrmInfo_IsSndDiagRlyFrm(void)
{
	return L3R_Diag_SndFlgReference->SndFlg;
}

/*************************************************************************//**
 * @fn			void L3R_FrmInfo_SwitchFlag(void)
 * @brief		更新用フラグと参照用フラグの切り替えを行う
 * @details		更新用フラグと参照用フラグの切り替えを行う
 * @param		なし
 * @return		なし
 * @attention	なし
 * @note		なし
 ****************************************************************************/
void L3R_FrmInfo_SwitchFlag(void)
{
	uint16 Index;
	
	/* 更新用と参照用の切り替え前に参照用のデータのクリア処理を実施する */
	/* ダイアグ中継フレーム用 */
	L3R_Diag_SndFlgReference->SndFlg = FALSE;
	L3R_Diag_SndFlgReference->RcvFrmNum = L3R_CLR;
	L3R_Diag_SndFlgReference->writepoint = L3R_CLR;
	
	for(Index = L3R_CLR; Index < L3R_CANID_ARRAYSIZE; Index++){
		/* ダイアグ中継フレーム用 */
		L3R_Diag_SndFlgReference->CanId[Index] = L3R_CLR;
	}
	
	L3R_DI();

	/* 更新用と参照用の切り替え */
	/* 更新用バッファの切り替え */
	/* 0と1の切り替えを排他的論理和で行う */
	L3R_Frm_UpdateIndex = (L3R_Frm_UpdateIndex ^ L3R_FRM_BUF_BIT_ENABLE) & (L3R_FRM_BUF_BIT_ENABLE);
	L3R_Diag_SndFlgUpdate = &L3R_Diag_FrmInfo[L3R_Frm_UpdateIndex];
	/* 参照用バッファの切り替え */
	/* 更新用バッファのIndexをもとに計算することにより、同一バッファを指すことがないようにする */
	L3R_Diag_SndFlgReference = &L3R_Diag_FrmInfo[L3R_FRM_ARRAYLAST_IDX - L3R_Frm_UpdateIndex];
	
	L3R_EI();

	return;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

