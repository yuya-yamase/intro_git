/* EthSwt_SWIC_Init.c専用ヘッダファイル */

/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Init_Cfg.h                                       */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_INIT_CFG_H
#define ETHSWT_SWIC_INIT_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Define.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_initRegListPort.h>
#include <EthSwt_SWIC_initRegListVlan.h>
#include <EthSwt_SWIC_initRegListL2.h>
#include <EthSwt_SWIC_initRegListQos.h>
#include <EthSwt_SWIC_initRegListAcl.h>
#include <EthSwt_SWIC_initRegListTC10.h>
#include <EthSwt_SWIC_initRegListBandwidthLimit.h>
#include <EthSwt_SWIC_initRegListSeqInitSeq.h>
#include <EthSwt_SWIC_initRegListSeqPhySwicOff.h>
#include <EthSwt_SWIC_initRegListSeqSetPortActDis.h>
/* -------------------------------------------------------------------------- */
struct swic_reg_tbl {								/* レジスタテーブル */
	const swic_reg_data_t	*tbl;
	const uint32			num;
};

struct swic_reg_seq {
        struct swic_reg_tbl tbl;
        const uint8			rst;		/* [STD_ON]値確認しリセット/[STD_OFF]読み捨て */
};

static const struct swic_reg_seq	G_ETHSWT_SWIC_INIT_TABLE[]
=	{
    /* {SWIC_REG_TBL(g_regListSeqSetResetDetect)	, STD_OFF},	*/          /* SWICリセット検知用 */
      {SWIC_REG_TBL(g_regListPort)					      , STD_OFF}              /* ポート設定 */
    , {SWIC_REG_TBL(g_regListVlan)					      , STD_OFF}              /* VLAN設定 */
    , {SWIC_REG_TBL(g_regListL2)					        , STD_OFF}              /* L2設定 */
    , {SWIC_REG_TBL(g_regListQos)					        , STD_OFF}              /* QoS設定 */
    , {SWIC_REG_TBL(g_regListAcl)					        , STD_OFF}              /* ACL設定 */
    /* , {SWIC_REG_TBL(g_regListArp)					    , STD_OFF} */           /* ARP設定 */
    , {SWIC_REG_TBL(g_regListTc10)					      , STD_OFF}              /* TC10設定 */
    /* , {SWIC_REG_TBL(g_regListPTP)					    , STD_OFF} */           /* PTP設定 */
    /* , {SWIC_REG_TBL(g_regListBandwidthLimit)		, STD_OFF} */           /* 帯域制限設定 */
    , {SWIC_REG_TBL(g_regListSeqInterruptClear)	  , STD_OFF}              /* 割り込み要因クリア */
    , {SWIC_REG_TBL(g_regListSeqSWICReset)			  , STD_OFF}              /* ソフトウェアリセット */
    , {SWIC_REG_TBL(g_regListSeqPPUOff)				    , STD_OFF}              /* PPU OFF */
    , {SWIC_REG_TBL(g_regListSeqGetWatchdogError)	, STD_ON}               /* レジスタ/テーブル化け確認レジスタ */
    , {SWIC_REG_TBL(g_regListSeqP1PhyOff)			    , STD_OFF}              /* Port1 PHY OFF */
    , {SWIC_REG_TBL(g_regListSeqP2PhyOff)			    , STD_OFF}              /* Port2 PHY OFF */
    , {SWIC_REG_TBL(g_regListSeqSetP1ActDis)		  , STD_OFF}              /* Port1設定 */
    , {SWIC_REG_TBL(g_regListSeqSetP2ActDis)		  , STD_OFF}              /* Port2設定 */
    /* , {SWIC_REG_TBL(g_regListSeqSetP3ActDis)		, STD_OFF} */           /* Port3設定 */
    /* , {SWIC_REG_TBL(g_regListSeqSetP4ActDis)		, STD_OFF} */           /* Port4設定 */
    , {SWIC_REG_TBL(g_regListSeqSetP5ActDis)		  , STD_OFF}              /* Port5設定 */
    /* , {SWIC_REG_TBL(g_regListSeqSetP6ActDis)		, STD_OFF} */           /* Port6設定 */
    , {SWIC_REG_TBL(g_regListSeqSetP7ActDis)		  , STD_OFF}              /* Port7設定 */
    , {SWIC_REG_TBL(g_regListSeqSetP8ActDis)		  , STD_OFF}              /* Port8設定 */
    /* , {SWIC_REG_TBL(g_regListSeqSetP9ActDis)		, STD_OFF} */           /* Port9設定 */
    };
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_INIT_CFG_H */
/* -------------------------------------------------------------------------- */
