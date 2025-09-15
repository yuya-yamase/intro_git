/* EthSwt_SWIC_Qci.c専用ヘッダファイル */

/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Qci_Cfg.h                                        */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_QCI_CFG_H
#define ETHSWT_SWIC_QCI_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Define.h>
#include <EthSwt_SWIC_initRegCommon.h>
/* -------------------------------------------------------------------------- */
struct swic_reg_tbl {								/* レジスタテーブル */
	const swic_reg_data_t	*tbl;
	const uint32			num;
};

static const struct swic_reg_tbl G_ETHSWT_SWIC_MIB_TABLE_LIST[];
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_MIB_CFG_H */
/* -------------------------------------------------------------------------- */
