/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_RstDtct_Cfg.h                                    */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_RSTDTCT_CFG_H
#define ETHSWT_SWIC_RSTDTCT_CFG_H
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_initRegListSeqInitSeq.h>
#include <EthSwt_SWIC_initRegListGetResetDetect.h>
/* -------------------------------------------------------------------------- */

struct swic_reg_tbl {						/* ���W�X�^�e�[�u�� */
	const swic_reg_data_t* tbl;
	const uint32			num;
};

static const struct swic_reg_tbl G_ETHSWT_SWIC_RSTDTCT_TABLE[]
= {
	{&g_regListSeqGetResetDetect[0], 4u}
,   {&g_regListSeqGetResetDetect[4], 4u}
,   {&g_regListSeqGetResetDetect[8], 4u}
,   {&g_regListSeqGetResetDetect[12], 4u}
};

#define G_ETHSWT_SWIC_RSTDTCT_TABLE_NUM (sizeof(G_ETHSWT_SWIC_RSTDTCT_TABLE) / sizeof(G_ETHSWT_SWIC_RSTDTCT_TABLE[0]))

/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_RSTDTCT_CFG_H */
/* -------------------------------------------------------------------------- */
