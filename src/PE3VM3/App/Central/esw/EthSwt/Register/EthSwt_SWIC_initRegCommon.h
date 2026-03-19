#ifndef ETHSWT_SWIC_INIT_REG_LIST_COMMON_H
#define ETHSWT_SWIC_INIT_REG_LIST_COMMON_H
#include <Std_Types.h>

/*===================================================================*/
/* マクロ定義                                                        */
/*===================================================================*/
// 処理フラグ定義:E_REG_CTRL
#define REG_CTRL_WRITE		((uint8)0)	/* Write処理 */
#define REG_CTRL_READ		((uint8)1)	/* READ処理 */
#define REG_CTRL_WRITE_MASK	((uint8)2)	/* Write処理(保存した値に対してMASK計算して書き込み) */
#define REG_CTRL_READ_TMP	((uint8)3)	/* READ処理(値保持) */
#define REG_CTRL_WAIT		((uint8)4)	/* us待ち */

// 監視フラグ定義:E_SURVEILLANCE
#define SURVEILLANCE_OFF	((uint8)0)	/* 監視OFF */
#define SURVEILLANCE_ON		((uint8)1)	/* 監視ON */

// レジスタ初期化データ構造体
typedef struct
{
	uint8		devAddr;		/* Deviceアドレス */
	uint8		regAddr;		/* レジスタアドレス */
	uint8		regCtrl;		/* 処理フラグ (E_REG_CTRL参照) */
	uint8		surveillance;	/* 監視フラグ (E_SURVEILLANCE参照)*/
	uint16		mask;			/* READ時のマスク値 */
	uint16		value;			/* レジスタ書き込みorチェックデータ */
}	swic_reg_data_t;

// 初期化シーケンスリトライ回数
#define INIT_SEQ_RETRY_CNT	(3uL)

#endif	/* ETHSWT_SWIC_INIT_REG_LIST_COMMON_H */
