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
#include <EthSwt_SWIC_initRegListSeqAclTbl.h>
/* -------------------------------------------------------------------------- */
struct swic_reg_tbl {								/* レジスタテーブル */
	const swic_reg_data_t	*tbl;
	const uint32			num;
};

static const struct swic_reg_tbl G_ETHSWT_SWIC_MIB_TABLE_LIST[]
= {	{g_regListSeqGetStreamFilterData_ID0, SWIC_TBL_NUM(g_regListSeqGetStreamFilterData_ID0)}
,	{g_regListSeqGetStreamFilterData_ID1, SWIC_TBL_NUM(g_regListSeqGetStreamFilterData_ID1)}
,	{g_regListSeqGetStreamFilterData_ID2, SWIC_TBL_NUM(g_regListSeqGetStreamFilterData_ID2)}
,	{g_regListSeqGetStreamFilterData_ID3, SWIC_TBL_NUM(g_regListSeqGetStreamFilterData_ID3)}
,	{g_regListSeqGetStreamFilterData_ID4, SWIC_TBL_NUM(g_regListSeqGetStreamFilterData_ID4)}
};
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_MIB_CFG_H */
/* -------------------------------------------------------------------------- */
