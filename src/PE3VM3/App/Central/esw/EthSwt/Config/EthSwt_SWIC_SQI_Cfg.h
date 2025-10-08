/* EthSwt_SWIC_Sqi.c専用ヘッダファイル */

/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_SQI_Cfg.h                                        */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_SQI_CFG_H
#define ETHSWT_SWIC_SQI_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_initRegListSeqSqi.h>
/* -------------------------------------------------------------------------- */
struct swic_tbl_sqi {
	const swic_reg_data_t *tbl;
	const uint32		   num;
};
struct swic_reg_tbl {								/* レジスタテーブル */
	const struct swic_tbl_sqi	tbl;
	const uint32				sft;
};
/* -------------------------------------------------------------------------- */
static struct swic_reg_tbl	G_ETHSWT_SWIC_GET_SQI_TABLE[]
	=	{ {{&g_regListSeqGetSqi1000B[0], 7u}, 0uL}	/* P1 */
		, {{&g_regListSeqGetSqi1000B[7], 7u}, 0uL}	/* P2 */
		, {{NULL_PTR,                    0u}, 0uL}	/* P3 */
		, {{NULL_PTR,                    0u}, 0uL}  /* P4 */
		, {{NULL_PTR,                    0u}, 0uL}  /* P5 */
		, {{NULL_PTR,                    0u}, 0uL}  /* P6 */
		, {{NULL_PTR,                    0u}, 0uL}  /* P7 */
		, {{NULL_PTR,                    0u}, 0uL}	/* P8 */
		, {{NULL_PTR,                    0u}, 0uL}	/* P9 */
		};
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_SQI_CFG_H */
/* -------------------------------------------------------------------------- */
