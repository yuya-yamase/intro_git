/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Init.c                                           */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include <EthSwt_SWIC_init_Cfg.h>
#include "EthSwt_SWIC_Init.h"
#include "EthSwt_SWIC_Reg.h"
#include "EthSwt_SWIC_Define.h"
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Init_Setting(uint32 * const errFactor)
{
    Std_ReturnType	result = E_OK;
	uint32			idx;
	uint32			val;

    for (idx=0U ; idx < SWIC_TBL_NUM(G_ETHSWT_SWIC_INIT_TABLE) ; idx++) {		/* リードバック無 */
        result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_INIT_TABLE[idx].tbl.tbl, G_ETHSWT_SWIC_INIT_TABLE[idx].tbl.num, (G_ETHSWT_SWIC_INIT_TABLE[idx].rst == STD_OFF) ? &val : NULL_PTR, errFactor);
		if (result == E_NOT_OK) {
			if (*errFactor == D_ETHSWT_SWIC_ERR_WRONGVALUE) {
				*errFactor = D_ETHSWT_SWIC_ERR_INIT;				/* 初期レジスタ設定時に読出した値を確認するのは、テーブル化けのみのため */
			}
			break;
		}
	}

	return result;
}