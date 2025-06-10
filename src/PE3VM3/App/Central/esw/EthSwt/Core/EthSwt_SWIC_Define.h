/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Define.h                                         */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_DEFINE_H
#define ETHSWT_SWIC_DEFINE_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#define	SWIC_REG_TBL(a)		{(a), SWIC_TBL_NUM(a)}	/* swic_reg_tbl設定用 */
#define	SWIC_TBL_NUM(a)	(sizeof(a)/sizeof((a)[0]))
                             
#define D_ETHSWT_SWIC_REG_FACT_NONE     (0x0000uL)
#define D_ETHSWT_SWIC_REG_FACT_POWEROFF	(0x0001uL)	/* SWIC電源OFF */
#define D_ETHSWT_SWIC_REG_FACT_CRC	    (0x0002uL)	/* CRC異常 */
#define D_ETHSWT_SWIC_REG_FACT_BSY	    (0x0004uL)	/* BSY待ち */
#define D_ETHSWT_SWIC_REG_FACT_SPI	    (0x0008uL)	/* CRC異常→SPI異常 */
#define D_ETHSWT_SWIC_REG_FACT_INIT	    (0x0010uL)	/* 初期化でレジスタ/テーブル化け */ 			/* ★初期化でレジスタ/テーブル化けしかない？ */
#define D_ETHSWT_SWIC_REG_FACT_INTN	    (0x0020uL)	/* SWIC内部エラー */
#define D_ETHSWT_SWIC_REG_FACT_RESET	(0x0040uL)	/* SWICリセット検出 */
#define D_ETHSWT_SWIC_REG_FACT_NOT_CTRL	(0x0080uL)	/* 対象レジスタコントロールなし(起きない) */


/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_DEFINE_H */
/* -------------------------------------------------------------------------- */
