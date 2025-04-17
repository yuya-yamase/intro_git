#ifndef ETHSWT_SWIC_DEF_H
#define ETHSWT_SWIC_DEF_H
#include <Std_Types.h>
/* Add #include "EthSwt_SWIC_Cfg.h" */
#include "EthSwt_SWIC_Cfg.h"
/* ★Debug_Start-------------------------------------------------------------- */
/* デバッグ用コンパイルスイッチ */
/* #define EthswtDebugMode1 (1)  デバッグ用：SPI         */
/* #define EthswtDebugMode2 (1)  デバッグ用：MIB取得     */
/* ★Debug_End---------------------------------------------------------------- */
#define	SWIC_TBL_NUM(a)	(sizeof(a)/sizeof((a)[0]))
#define SWIC_TBL_CHK(a)	((void)sizeof(char[1L - 2L*(sint32)(a)])) /* レジスタテーブル変更確認用 */
#define	SWIC_ETH_PERIOD	(1)		/* EthSwt_SWIC_MainFunction1MS周期(ms) */
#define	SWIC_REG_WAIT	(30u)	/* 30ms(REG_CTRL_READ.SURVEILLANCE_ON待ち時間(ns)) */
#define	SWIC_REG_WAIT_L	(((SWIC_REG_WAIT*1000000u)/2410u)+1u) /* ループガード値 */
								/* クロック2(20MHz)で1要求(6byte+10ns)=2410ns */
								/* ※クロックは10MHzなので倍になる */
								/* ※実測値の5倍程度になる */

/* Add #define	SWIC_REG_TMOLNK	(70u) */
#define	SWIC_REG_TMOLNK	(70u)	/* 起動後ETHTRCV_LINK_STATE_ACTIVEまで確認する時間(ms) */
/* Add #define	SWIC_REG_TIMRST	(100) */
#define	SWIC_REG_TIMRST	(100)	/* SWICリセット(異常)検出周期(ms)[T14] */
/* Add #define	SWIC_REG_TIMLNK	(100) */
#define	SWIC_REG_TIMLNK	(100)	/* リンク状態取得周期(ms) */

#define	SWIC_REG_TIMERR	(5)		/* SWIC内部エラー検出周期(ms) */
#define	SWIC_REG_LINK	(70u)	/* 起動後ETHTRCV_LINK_STATE_ACTIVEまで確認する時間(ms) */
#define PORTMODE_DATASIZE	(4u)		/* ChipComから受け取るポートモードのデータサイズ */
#define MCUINFO_PORT_DATASIZE	(7u)	/* ChipComに通知する1PORT分のデータサイズ */
#define SWIC_STS_DATAPOS	(0)		/* ChipComに通知するSWIC状態格納位置 */
#define PORT_MODE_DATAPOS1	(1)		/* ChipComに通知するポートモード格納位置(1byte目) */
#define PORT_MODE_DATAPOS2	(2)		/* ChipComに通知するポートモード格納位置(2byte目) */
#define PORT_MODE_DATAPOS3	(3)		/* ChipComに通知するポートモード格納位置(3byte目) */
#define PORT_MODE_DATAPOS4	(4)		/* ChipComに通知するポートモード格納位置(4byte目) */
#define IND_MODE_DATAPOS	(5)		/* ChipComに通知するindモード情報格納位置 */
#define LNK_STS_DATAPOS		(6)		/* ChipComに通知するリンク状態格納位置 */
#define LNK_ERR_DATAPOS		(7)		/* ChipComに通知するリンク状態取得結果格納位置 */
#define TRANSREQ_SHIFT_1BYTE	(8)			/* ビットシフト用(1byte) */
#define TRANSREQ_SHIFT_2BYTE	(16)		/* ビットシフト用(2byte) */
#define TRANSREQ_SHIFT_3BYTE	(24)		/* ビットシフト用(3byte) */
#define TRANSREQ_1BYTE_DATA_MASK	(0x000000FFu)	/* ChipComに通知するデータ加工用マスク */
#define SWIC_PORT1			(3u)					/* Port1(A-DC)の配列番号 */
#define SWIC_PORT2			(4u)					/* Port2(DCM)の配列番号 */
#define SWIC_PORT5			(0u)					/* Port5(SAIL)の配列番号 */
#define SWIC_PORT6			(7u)					/* Port6(DLC)の配列番号 */
#define SWIC_PORT7			(1u)					/* Port7(QNX)の配列番号 */
#define SWIC_PORT8			(2u)					/* Port8(Android)の配列番号 */
#define SWIC_PORT_NUM		(6u)					/* 有効ポート数 */
#define MCUINFO_DATASIZE	((SWIC_PORT_NUM * MCUINFO_PORT_DATASIZE)+1)	/* (ChipComに通知するポート毎のデータサイズ(7byte))*(有効ポート数(6))+(SWIC内部情報データサイズ(1byte)) */
#define	ETHSWT_SWIC_INITPORT \
	{ ETH_MODE_ACTIVE	/* P5：SIP SAILSS_RGMII0 RGMII:初期化でリンク済 */ \
	, ETH_MODE_ACTIVE	/* P7：SIP SGMII0 SGMII:初期化でリンク済 */ \
	, ETH_MODE_ACTIVE	/* P8：SIP SGMII1 SGMII:初期化でリンク済 */ \
	, ETH_MODE_ACTIVE	/* P1：ADC 1000BASE-T1:初期化でリンク済(★暫定対応) */ \
	, ETH_MODE_ACTIVE	/* P2：DCM 1000BASE-T1:初期化でリンク済(★暫定対応) */ \
	, ETH_MODE_DOWN		/* P3：無効ポート */ \
	, ETH_MODE_DOWN		/* P4：無効ポート */ \
	, ETH_MODE_DOWN		/* P6：DLC 100BASE-TX:初期化+ACTIVE要求でリンク */ \
	, ETH_MODE_DOWN		/* P9:無効ポート */ \
	}
#define	ETHSWT_SWIC_MIBPORT \
	{ STD_ON			/* P5:対象 */ \
	, STD_ON			/* P7:対象 */ \
	, STD_ON			/* P8:対象 */ \
	, STD_ON			/* P1:対象 */ \
	, STD_ON			/* P2:対象 */ \
	, STD_OFF			/* P3:不要 */ \
	, STD_OFF			/* P4:不要 */ \
	, STD_ON			/* P6:対象 */ \
	, STD_OFF			/* P9:不要 */ \
	}
#define	ETHSWT_SWIC_FASTLINKCHK \
	{ STD_ON			/* P5:対象 */ \
	, STD_ON			/* P7:対象 */ \
	, STD_ON			/* P8:対象 */ \
	, STD_ON			/* P1:対象 */ \
	, STD_ON			/* P2:対象 */ \
	, STD_OFF			/* P3:不要 */ \
	, STD_OFF			/* P4:不要 */ \
	, STD_OFF			/* P6:不要 */ \
	, STD_OFF			/* P9:不要 */ \
	}

#endif	/* ETHSWT_SWIC_DEF_H */
