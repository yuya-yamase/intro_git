#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Init.h>
#include <EthSwt_SWIC_Reg.h>
#include <EthSwt_SWIC_Core_Cfg.h>

#include "EthSwt_SWIC_initRegCommon.h"
#include "EthSwt_SWIC_initRegListPort.h"
#include "EthSwt_SWIC_initRegListVlan.h"
#include "EthSwt_SWIC_initRegListL2.h"
#include "EthSwt_SWIC_initRegListQos.h"
#include "EthSwt_SWIC_initRegListAcl.h"
#include "EthSwt_SWIC_initRegListArp.h"
#include "EthSwt_SWIC_initRegListTC10.h"
#include "EthSwt_SWIC_initRegListPTP.h"
#include "EthSwt_SWIC_initRegListBandwidthLimit.h"
#include "EthSwt_SWIC_initRegListSeqInitSeq.h"
#include "EthSwt_SWIC_initRegListSeqSetPortActDis.h"
#include "EthSwt_SWIC_initRegListSeq100BTx.h"
#include "EthSwt_SWIC_initRegListSeqAclTbl.h"
#include "EthSwt_SWIC_initRegListSeqGetInterrupt.h"
#include "EthSwt_SWIC_initRegListSeqPhySwicOff.h"
#include "EthSwt_SWIC_initRegListSeqGetLink.h"
#include "EthSwt_SWIC_initRegListSeqPhyReset.h"

/* -------------------------------------------------------------------------- */
#define	SWIC_REG_TBL(a)		{(a), SWIC_TBL_NUM(a)}	/* swic_reg_tbl設定用 */
#define	SWIC_TBL_NUM(a)	(sizeof(a)/sizeof((a)[0]))
/* -------------------------------------------------------------------------- */
struct swic_reg_tbl {								/* レジスタテーブル */
	const swic_reg_data_t	*tbl;
	const uint32			num;
};
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Init_Setting(void)
{
    struct swic_reg_seq {
        struct swic_reg_tbl tbl;
        const uint8			rst;		/* [STD_ON]値確認しリセット/[STD_OFF]読み捨て */
    };
    static const struct swic_reg_seq	tbl[]
	=	{
		#ifndef	g_regListSeqSetResetDetect							/* SWICリセット検出 */
		  {SWIC_REG_TBL(g_regListSeqSetResetDetect)		, STD_OFF},	/* リセット検知用設定 */
		#endif														/* g_regListSeqSetResetDetect */
		  {SWIC_REG_TBL(g_regListPort)					, STD_OFF}	/* ポート設定 */
		, {SWIC_REG_TBL(g_regListVlan)					, STD_OFF}	/* VLAN設定 */
		, {SWIC_REG_TBL(g_regListL2)					, STD_OFF}	/* L2設定 */
		, {SWIC_REG_TBL(g_regListQos)					, STD_OFF}	/* QoS設定 */
		, {SWIC_REG_TBL(g_regListAcl)					, STD_OFF}	/* ACL設定 */
		#ifndef	g_regListArp
		, {SWIC_REG_TBL(g_regListArp)					, STD_OFF}	/* ARP設定 */
		#endif														/* g_regListArp */
		, {SWIC_REG_TBL(g_regListTc10)					, STD_OFF}	/* TC10設定 */
		#ifndef	g_regListPTP
		, {SWIC_REG_TBL(g_regListPTP)					, STD_OFF}	/* PTP設定 */
		#endif														/* g_regListPTP */
		, {SWIC_REG_TBL(g_regListBandwidthLimit)		, STD_OFF}	/* 帯域制限設定 */
		, {SWIC_REG_TBL(g_regListSeqInterruptClear)		, STD_OFF}	/* 割り込み要因クリア */
		, {SWIC_REG_TBL(g_regListSeqSWICReset)			, STD_OFF}	/* ソフトウェアリセット */
		, {SWIC_REG_TBL(g_regListSeqPPUOff)				, STD_OFF}	/* PPU OFF */
		, {SWIC_REG_TBL(g_regListSeqGetWatchdogError)	, STD_ON}	/* レジスタ/テーブル化け確認レジスタ */
		, {SWIC_REG_TBL(g_regListSeqRelayOn)			, STD_OFF}	/* 中継ON */
		#ifndef	g_regListSeqSetP1ActDis
		, {SWIC_REG_TBL(g_regListSeqSetP1ActDis)		, STD_OFF}	/* Port1設定 */
		#endif														/* g_regListSeqSetP1ActDis */
		#ifndef	g_regListSeqSetP2ActDis
		, {SWIC_REG_TBL(g_regListSeqSetP2ActDis)		, STD_OFF}	/* Port2設定 */
		#endif														/* g_regListSeqSetP2ActDis */
		#ifndef	g_regListSeqSetP3ActDis
		, {SWIC_REG_TBL(g_regListSeqSetP3ActDis)		, STD_OFF}	/* Port3設定 */
		#endif														/* g_regListSeqSetP3ActDis */
		#ifndef	g_regListSeqSetP4ActDis
		, {SWIC_REG_TBL(g_regListSeqSetP4ActDis)		, STD_OFF}	/* Port4設定 */
		#endif														/* g_regListSeqSetP4ActDis */
		#ifndef	g_regListSeqSetP5ActDis
		, {SWIC_REG_TBL(g_regListSeqSetP5ActDis)		, STD_OFF}	/* Port5設定 */
		#endif														/* g_regListSeqSetP5ActDis */
		#ifndef	g_regListSeqSetP7ActDis
		, {SWIC_REG_TBL(g_regListSeqSetP7ActDis)		, STD_OFF}	/* Port7設定 */
		#endif														/* g_regListSeqSetP7ActDis */
		#ifndef	g_regListSeqSetP8ActDis
		, {SWIC_REG_TBL(g_regListSeqSetP8ActDis)		, STD_OFF}	/* Port8設定 */
		#endif														/* g_regListSeqSetP8ActDis */
        #ifndef	g_regListSeqSetP9ActDis
		, {SWIC_REG_TBL(g_regListSeqSetP9ActDis)		, STD_OFF}	/* Port8設定 */
		#endif														/* g_regListSeqSetP8ActDis */
		};
    Std_ReturnType ret = E_OK;
    Std_ReturnType	err = E_OK;
	uint32			idx;
	uint32			val;

    for (idx=0U ; idx < SWIC_TBL_NUM(tbl) ; idx++) {		/* リードバック無 */
        
	}
}