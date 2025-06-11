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
                             
#define D_ETHSWT_SWIC_ERR_NONE          (0x0000uL)
#define D_ETHSWT_SWIC_ERR_POWEROFF	    (0x0001uL)	/* SWIC電源OFF */
#define D_ETHSWT_SWIC_ERR_CRC	        (0x0002uL)	/* CRC異常 */
#define D_ETHSWT_SWIC_ERR_BUSY	        (0x0004uL)	/* BSY待ち */
#define D_ETHSWT_SWIC_ERR_WRONGVALUE    (0x0008uL)	/* 読出し値が期待と異なる */
#define D_ETHSWT_SWIC_ERR_INIT	        (0x0010uL)	/* 初期化でレジスタ/テーブル化け */
#define D_ETHSWT_SWIC_ERR_INTN	        (0x0020uL)	/* SWIC内部エラー */
#define D_ETHSWT_SWIC_ERR_RESET	        (0x0040uL)	/* SWICリセット検出 */
#define D_ETHSWT_SWIC_ERR_NOPROC	    (0x0080uL)	/* 対象レジスタアクセス処理なし(起きない) */


/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_DEFINE_H */
/* -------------------------------------------------------------------------- */
