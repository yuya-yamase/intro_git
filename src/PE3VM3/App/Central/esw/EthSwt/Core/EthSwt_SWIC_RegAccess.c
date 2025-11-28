/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_RegAccess.c                                      */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include "EthSwt_SWIC_RegAccessErr.h"
#include "EthSwt_SWIC_Reg.h"
#include "EthSwt_SWIC_STM.h"
#include "EthSwt_SWIC_RegAccess_Cfg.h"
#include <LIB.h>
#include "EthSwt_SWIC_Time.h"
#include "EthSwt_SWIC_Define.h"
/* -------------------------------------------------------------------------- */
static struct {
    const swic_reg_data_t *volatile	tbl;						/* 異常テーブル */
	volatile uint32					idx;						/* 異常位置 */
	uint32	cnt;												/* エラーカウンタ */
} S_ETHSWT_SWIC_REGACCESS

/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RegAccess_Init (void)/* レジスタアクセスエラー関連データの初期化 */
{

	S_ETHSWT_SWIC_REGACCESS.tbl                        = NULL_PTR;
	S_ETHSWT_SWIC_REGACCESS.idx                        = 0;
	S_ETHSWT_SWIC_REGACCESS.cnt                        = 0;

	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RegAccess_Clear (void)/* レジスタアクセスエラー関連データの初期化 */
{

	LIB_DI();

	S_ETHSWT_SWIC_REGACCESS.tbl                        = NULL_PTR;
	S_ETHSWT_SWIC_REGACCESS.idx                        = 0;
	S_ETHSWT_SWIC_REGACCESS.cnt                        = 0;

	LIB_EI();

	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RegAccess_RegAccessNotify(Std_ReturnType err, const swic_reg_data_t tbl[], const uint32 idx)
{
	if(E_NOT_OK == err)
	{
		/* 前回のレジスタアクセス異常と同じ場所でのエラーか確認 */
		if(S_ETHSWT_SWIC_REGACCESS.tbl == tbl)
		{
			S_ETHSWT_SWIC_REGACCESS.cnt++;
			/* 一定回数以上連続してエラー発生している場合、ChipComに通知 */
			if(G_ETHSWT_SWIC_REGACCESS_N_REGMONERREET <= S_ETHSWT_SWIC_REGACCESS.cnt)
			{
				S_ETHSWT_SWIC_REGACCESS.tbl                = NULL_PTR;
				S_ETHSWT_SWIC_REGACCESS.id++;
				S_ETHSWT_SWIC_REGACCESS.cnt                = 0;
				ETHSWT_SWIC_REGACCESS_NOTIFY(tbl, idx, id);
			}
		}
		else
		{
			/* 今回の異常の情報を保存 */
			S_ETHSWT_SWIC_REGACCESS.tbl = tbl;
			S_ETHSWT_SWIC_REGACCESS.cnt = 1;		
		}
	}
	else{
		S_ETHSWT_SWIC_REGACCESS.tbl                = NULL_PTR;
		S_ETHSWT_SWIC_REGACCESS.cnt                = 0;		
	}

	return;
}