#ifndef ETHSWT_SWIC_DEF_H
#define ETHSWT_SWIC_DEF_H
#include <Std_Types.h>
#include "EthSwt_SWIC_Cfg.h"

#define	SWIC_TBL_NUM(a)	(sizeof(a)/sizeof((a)[0]))
#define SWIC_TBL_CHK(a) ((void)sizeof(char[1L - 2L*(sint32)(a)])) /* レジスタテーブル変更確認用 */
#define	SWIC_ETH_PERIOD	(1)		/* EthSwt_SWIC_MainFunction1MS周期(ms) */
#define	SWIC_REG_WAIT	(30u)	/* 30ms(REG_CTRL_READ.SURVEILLANCE_ON待ち時間(ns)) */
#define	SWIC_REG_WAIT_L	(((SWIC_REG_WAIT*1000000u)/2410u)+1u) /* ループガード値 */
								/* クロック2(20MHz)で1要求(6byte+10ns)=2410ns */
								/* ※クロックは10MHzなので倍になる */
								/* ※実測値の5倍程度になる */
#define	SWIC_REG_TIMRST	(100)	/* SWICリセット(異常)検出周期(ms)[T14] */
#define	SWIC_REG_TIMERR	(5)		/* SWIC内部エラー検出周期(ms) */
#define	SWIC_REG_TIMLNK	(100)	/* リンク状態取得周期(ms) */
#define	SWIC_REG_TMOLNK	(70u)	/* 起動後ETHTRCV_LINK_STATE_ACTIVEまで確認する時間(ms) */

#endif	/* ETHSWT_SWIC_DEF_H */
