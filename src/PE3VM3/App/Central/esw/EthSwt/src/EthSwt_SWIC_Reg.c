#include <Std_Types.h>

#if 0 /* For BSW */
#include <Eth_GeneralTypes.h>
#include <Eth.h>
#include <EthIf.h>
#endif

#include <LIB.h>
#include <EthSwt_SWIC.h>

#if 0 /* For HND EthDbg */
/*koko*/#include <EthDbg.h>		/* EthDbg_GetMibOFF/EthDbg_Swt_CrcOFF */
#endif

#include "EthSwt_SWIC_Def.h"
#include "EthSwt_SWIC_Reg.h"
#include "EthSwt_SWIC_Spi.h"
#include "EthSwt_SWIC_Org.h"
#include "EthSwt_SWIC_Pwr.h"
#if 1 /* NCOS Soft */
#include "EthSwt_SWIC_Log.h"
#endif

#if 0 /* For HND */
#include "EthSwt_SWIC_DTC.h"
#endif

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

#if 1 /* NCOS Soft */
#include <EthSwt_SWIC_initRegListSeqMib.h>
#include <EthSwt_SWIC_initRegListSeqBaseT1.h>
#endif

#if 0 /* 未対応 SQI */
#include "EthSwt_SWIC_initRegListSeqSqi.h"
#endif

#ifndef	g_regListSeqSetResetDetect					/* SWICリセット検出 */
#include "EthSwt_SWIC_initRegListGetResetDetect.h"
#endif												/* g_regListSeqSetResetDetect */

#if 0 /* For HND PMIC */
#ifdef	SWIC_OPT_PMIC								/* Ether PMIC有:EthSwt_SWIC_Def.hの後 */
#include <I2cM.h>									/* I2cM_Rslt_Ethpmic_GetState */
#endif												/* SWIC_OPT_PMIC */
#endif

typedef enum										/* EthSwt_SWIC初期化状態 */
{	ETHSWT_SWIC_STATE_UNINIT = ETHSWT_STATE_UNINIT	/* 停止 -> ETHSWT_SWIC_STATE_INIT */
,	ETHSWT_SWIC_STATE_INIT   = ETHSWT_STATE_INIT	/* 初期化中 -> ETHSWT_SWIC_STATE_ACTIVE */
,	ETHSWT_SWIC_STATE_ACTIVE = ETHSWT_STATE_ACTIVE	/* 動作中 */
,	ETHSWT_SWIC_STATE_RESET							/* RESET中 -> ETHSWT_SWIC_STATE_ACTIVE */
,	ETHSWT_SWIC_STATE_PMIC							/* PMIC OFF検出 -> ETHSWT_SWIC_STATE_INIT */
}	EthSwt_SWIC_StateType;

#define	SWIC_REG_TBL(a)		{(a), SWIC_TBL_NUM(a)}	/* swic_reg_tbl設定用 */
#define	SWIC_REG_BIT(a)		(1uL << (a))			/* ビット */
struct swic_reg_tbl {								/* レジスタテーブル */
	const swic_reg_data_t	*tbl;
	const uint32			num;
};

#define ETHSWT_START_SEC_CONFIG_DATA_PREBUILD
#include <EthSwt_SWIC_MemMap.h>

#if 0 /* 未対応 IDS */
#ifdef	SWIC_REG_IDSPORT		/* IDS対象 */
static const uint16	swic_Reg_IdsPort[] = SWIC_REG_IDSPORT;	/* StreamFilterテーブルのNo(0:無) */
#endif							/* SWIC_REG_IDSPORT */
#endif

static const struct {
	Eth_ModeType	mode;		/* 初期化時のポートモード[ETH_MODE_ACTIVE]リンク済/[ETH_MODE_DOWN]リンク無 */
	sint32			tmo_IDS;	/* IDS取得周期[T12][T13](0:対象外) */	/* EthIDSの取得周期(60s)で割り切れる値 */
	sint32			tmo_SQI;	/* SQI取得周期(0:対象外) */
}	swic_Reg_PortDef[]
#if 0 /* For HND ポート設定*/
=	{ {ETH_MODE_ACTIVE,  0,    0}	/* P8 */
	#ifdef	g_regListSeqSetP1ActDis
	, {ETH_MODE_DOWN,    0,    0}	/* P1無 */
	#else
	, {ETH_MODE_ACTIVE, 20, 1000}	/* P1有 */
	#endif								/* g_regListSeqSetP1ActDis */
	#ifdef	g_regListSeqSetP2ActDis
	, {ETH_MODE_DOWN,    0,    0}	/* P2無 */
	#else
	, {ETH_MODE_ACTIVE, 20, 1000}	/* P2有 */
	#endif								/* g_regListSeqSetP2ActDis */
	#ifdef	g_regListSeqSetP3ActDis
	, {ETH_MODE_DOWN,    0,    0}	/* P3無 */
	#else
	, {ETH_MODE_ACTIVE, 20, 1000}	/* P3有 */
	#endif								/* g_regListSeqSetP3ActDis */
	#ifdef	g_regListSeqSetP4ActDis
	, {ETH_MODE_DOWN,    0,    0}	/* P4無 */
	#else
	, {ETH_MODE_ACTIVE, 20, 1000}	/* P4有 */
	#endif								/* g_regListSeqSetP4ActDis */
	#ifdef	g_regListSeqSetP5ActDis
	, {ETH_MODE_DOWN,    0,    0}	/* P5無 */
	#else
	, {ETH_MODE_ACTIVE, 20, 1000}	/* P5有 */
	#endif								/* g_regListSeqSetP5ActDis */
	, {ETH_MODE_DOWN,    0,    0}	/* P6 */
	};
#endif
=	{
	#ifdef	g_regListSeqSetP9ActDis
	  {ETH_MODE_DOWN,    0,    0}	/* P9無 */
	#else
	  {ETH_MODE_ACTIVE, 20, 1000}	/* P9有 */
	#endif
	, {ETH_MODE_ACTIVE,  0,    0}	/* P1 */
	, {ETH_MODE_ACTIVE,  0,    0}	/* P2 */
	#ifdef	g_regListSeqSetP3ActDis
	, {ETH_MODE_DOWN,    0,    0}	/* P3無 */
	#else
	, {ETH_MODE_ACTIVE, 20, 1000}	/* P3有 */
	#endif								/* g_regListSeqSetP3ActDis */
	#ifdef	g_regListSeqSetP4ActDis
	, {ETH_MODE_DOWN,    0,    0}	/* P4無 */
	#else
	, {ETH_MODE_ACTIVE, 20, 1000}	/* P4有 */
	#endif								/* g_regListSeqSetP4ActDis */
	, {ETH_MODE_ACTIVE,  0,    0}	/* P5 */
	, {ETH_MODE_DOWN,  0,    0}		/* P6 */
	, {ETH_MODE_ACTIVE,  0,    0}	/* P7 */
	, {ETH_MODE_ACTIVE,  0,    0}	/* P8 */
	};

#if 0 /* 未対応　SQI */
#define	SWIC_PHY_INISQI	(500)			/* swic_Reg_Mode[].sqi.tim初期値:初回発火時間調整用 */
#endif

#define ETHSWT_STOP_SEC_CONFIG_DATA_PREBUILD
#include <EthSwt_SWIC_MemMap.h>

#define	ETHSWT_START_SEC_VAR_CLEARED
#include <EthSwt_SWIC_MemMap.h>
struct swic_Reg_Timer {						/* タイマ */
	sint32			tim;					/* タイマカウンタ */
	volatile uint8	req;					/* 処理要求 */
};
static struct {								/* 初期化情報 */
	volatile EthSwt_SWIC_StateType	sts;	/* 初期化状態 */
	volatile Std_ReturnType			err;	/* 初期化異常有無 */
	volatile uint16					tim;	/* タイマ:レジスタアクセスを抑えるため周期タスクでカウント */
#if 0 /* 未対応 SWICリセット(異常)検出 */
	struct swic_Reg_Timer			timrst;	/* SWICリセット(異常)検出周期 */
#endif
#if 0 /* 未対応 SWIC内部エラー検出 */
	struct swic_Reg_Timer			timerr;	/* SWIC内部エラー検出周期 */
#endif
	struct swic_Reg_Timer			timlnk;	/* リンク状態取得周期 */
}	swic_Reg_Inf;
static struct {								/* ベリファイ異常記憶用 */
	const swic_reg_data_t *volatile	tbl;	/* 異常テーブル */
	volatile uint32					idx;	/* 異常位置 */
	volatile uint16					val;	/* 読めた値 */
	volatile uint8					mon_seq;/* 割り込み時の処理レジスタ種別 */
	volatile uint8					mon_val;/* 割り込み時の処理レジスタ値 */
	volatile uint32					rst_fct;/* リセット要因 */
}	swic_Reg_Err;
static struct {									/* EthSwt_SetSwitchPortMode */
	Eth_ModeType					mode;
	volatile Eth_ModeType			mode_chg;	/* アクセス順不動なのでvolatile */
	volatile uint8					req_mode;	/* ↑ */
	volatile uint8					ind_mode;	/* ↑ */
	volatile Std_ReturnType			lnk_err;	/* アクセス順不動なのでvolatile */
	volatile EthTrcv_LinkStateType	lnk_sts;	/* ↑ */
	volatile uint8					req_rst;
	uint8							lnk_chk;
	EthTrcv_LinkStateType			lnk_exp;
	uint16							lnk_tim;
	uint16							lnk_tmo;
#if 0 /* 未対応 SQI */
	volatile Std_ReturnType			sqi_err;	/* アクセス順不動なのでvolatile */
	volatile uint8					sqi_val;	/* ↑ */
#endif
#if 0 /* 未対応 帯域制限 */
	uint32							FiltFrm;	/* Flow Meter Filtered Counter */
#endif
#if 0 /* 未対応 IDS */
	struct swic_Reg_Timer			ids;
#endif
#if 0 /* 未対応 SQI */
	struct swic_Reg_Timer			sqi;
#endif
}	swic_Reg_Mode[SWIC_TBL_NUM(swic_Reg_PortDef)];	/* 0～8 : 0=Port9 */

#if 0 /* For HND DeInit */
static uint8			swic_Reg_ReqDeInit;		/* EthSwt_SWIC_DeInit要求 */
#endif
#if 0 /* For DTC */
static uint8			swic_Reg_ReqClrDTC;		/* DTCクリア要求 */
#endif

#define	ETHSWT_STOP_SEC_VAR_CLEARED
#include <EthSwt_SWIC_MemMap.h>

#define	ETHSWT_START_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
static void swic_Reg_InitLink(void)
{	/* ETHSWT_SWIC_STATE_INITになる状態に遷移するときに呼び出す */
	unsigned	idx;
	for (idx=0U ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		swic_Reg_Mode[idx].lnk_err = E_NOT_OK;

#if 0 /* 未対応 SQI */
		swic_Reg_Mode[idx].sqi_err = E_NOT_OK;
#endif

	}
}
static void swic_Reg_SetState(const EthSwt_SWIC_StateType sts)
{	/* ログを残して遷移 */

#if 0 /* For HND EthDbg */
/*koko*/EthDbg_LOGCHG(89u, ETHSWT_SWIC_IDX, 0u, sts)
#endif

	swic_Reg_Inf.sts = sts;
	switch (sts) {
	case ETHSWT_SWIC_STATE_PMIC:
	
#if 0 /* For HND PMIC */
		EthSwt_SWIC_Org_PmicOFF();	/* Ether PMIC無→処理無 */
#endif

		swic_Reg_InitLink();
		break;
	case ETHSWT_SWIC_STATE_RESET:
		swic_Reg_InitLink();
		break;
	case ETHSWT_SWIC_STATE_UNINIT:
	case ETHSWT_SWIC_STATE_INIT:
	case ETHSWT_SWIC_STATE_ACTIVE:
	default:	/* default */
		break;
	}

#if 0 /* For HND DTC */
	EthSwt_SWIC_DTC_Run((sts == ETHSWT_SWIC_STATE_ACTIVE) ? STD_ON : STD_OFF);
#endif

}
static void swic_Reg_LinkTimSet(const uint8 SwitchPortIdx, const EthTrcv_LinkStateType LinkState, const uint16 tmo)
{
	if (SwitchPortIdx < SWIC_TBL_NUM(swic_Reg_Mode)) {
		swic_Reg_Mode[SwitchPortIdx].lnk_chk = STD_ON;
		swic_Reg_Mode[SwitchPortIdx].lnk_exp = LinkState;
		swic_Reg_Mode[SwitchPortIdx].lnk_tim = swic_Reg_Inf.tim;
		swic_Reg_Mode[SwitchPortIdx].lnk_tmo = tmo;
	}
}

#if 0 /* 未対応 IDS */
static void swic_Reg_TimClrDTC(void)
{	/* DTC周期タイマ初期化：1ms|ETHSWT_SWIC_STATE_ACTIVE以外 */
	uint8	idx;
	for (idx=0U ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		swic_Reg_Mode[idx].ids.tim = 0;
		swic_Reg_Mode[idx].ids.req = STD_OFF;
	}
}
#endif

static void swic_Reg_TimClr(void)
{	/* 全周期タイマ初期化：1ms|ETHSWT_SWIC_STATE_ACTIVE以外 */
#if 0 /* 未対応 SQI*/
	uint8	idx;
#endif
#if 0 /* 未対応 SWICリセット(異常)検出 */
	swic_Reg_Inf.timrst.tim = 0;
	swic_Reg_Inf.timrst.req = STD_OFF;
#endif
#if 0 /* 未対応 SWIC内部エラー検出 */
	swic_Reg_Inf.timerr.tim = 0;
	swic_Reg_Inf.timerr.req = STD_OFF;
#endif
	swic_Reg_Inf.timlnk.tim = 0;
	swic_Reg_Inf.timlnk.req = STD_ON;

#if 0 /* 未対応 SQI*/
	for (idx=0U ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		swic_Reg_Mode[idx].sqi.tim = SWIC_PHY_INISQI;
		swic_Reg_Mode[idx].sqi.req = STD_OFF;
	}
#endif

#if 0 /* For HND DTC*/
	swic_Reg_TimClrDTC();
#endif

}
void EthSwt_SWIC_Reg_Init(void)
{	/* 初期化タスク */
	uint8		i;
#if 0 /* For HND DTC */
/*koko*/EthDbg_LOG(89u, ETHSWT_SWIC_IDX, 0u, 0u)
	EthSwt_SWIC_DTC_Init();
#endif

	EthSwt_SWIC_Spi_Init();

#if 0 /* NCOS Soft */
	EthSwt_SWIC_Org_Init();
#endif

	swic_Reg_Inf.sts	= ETHSWT_SWIC_STATE_UNINIT;	/* 確認用 */
	swic_Reg_Inf.err	= E_OK;
	swic_Reg_Inf.tim	= 0u;
	swic_Reg_Err.tbl	= NULL_PTR;
	swic_Reg_Err.idx	= 0u;
	swic_Reg_Err.val	= 0u;
	swic_Reg_Err.mon_seq= 0u;
	swic_Reg_Err.mon_val= 0u;
	swic_Reg_Err.rst_fct= 0uL;
	for (i=0U ; i<SWIC_TBL_NUM(swic_Reg_Mode) ; i++) {
		swic_Reg_Mode[i].mode					= swic_Reg_PortDef[i].mode;
		swic_Reg_Mode[i].mode_chg				= swic_Reg_PortDef[i].mode;
		swic_Reg_Mode[i].req_mode				= STD_OFF;
		swic_Reg_Mode[i].ind_mode				= STD_OFF;
		swic_Reg_Mode[i].lnk_err				= E_NOT_OK;
		swic_Reg_Mode[i].lnk_sts				= ETHTRCV_LINK_STATE_DOWN;
		swic_Reg_Mode[i].req_rst				= STD_OFF;
		swic_Reg_Mode[i].lnk_chk				= STD_OFF;
		swic_Reg_Mode[i].lnk_exp				= ETHTRCV_LINK_STATE_DOWN;
		swic_Reg_Mode[i].lnk_tim				= 0u;
		swic_Reg_Mode[i].lnk_tmo				= 0u;
#if 0 /* 未対応 SQI*/
		swic_Reg_Mode[i].sqi_err				= E_NOT_OK;
		swic_Reg_Mode[i].sqi_val				= 0u;
#endif
#if 0 /* 未対応 帯域制限 */
		swic_Reg_Mode[i].FiltFrm				= 0u;
#endif
#if 0 /* 未対応 IDS */
		swic_Reg_Mode[i].ids.tim				= 0;
		swic_Reg_Mode[i].ids.req				= STD_OFF;
#endif
#if 0 /* 未対応 SQI */
		swic_Reg_Mode[i].sqi.tim				= SWIC_PHY_INISQI;
		swic_Reg_Mode[i].sqi.req				= STD_OFF;
#endif
		if (swic_Reg_PortDef[i].mode == ETH_MODE_ACTIVE) {
			swic_Reg_LinkTimSet(i, ETHTRCV_LINK_STATE_ACTIVE, SWIC_REG_TMOLNK);
		}
	}
	swic_Reg_TimClr();

#if 0 /* For HND DeInit */
	swic_Reg_ReqDeInit	= STD_OFF;
#endif
#if 0 /* For HND DTC */
	swic_Reg_ReqClrDTC	= STD_OFF;
#endif

	swic_Reg_SetState(ETHSWT_SWIC_STATE_PMIC);
/*	EthSwt_SWIC_BackgroundTask();	*/	/* 初期化時間計測用 */
}

#if 0 /* For HND DeInit */
void EthSwt_SWIC_DeInit(void)
{	/* 1msタスク */
	swic_Reg_ReqDeInit = STD_ON;
}
#endif

static void swic_Reg_TimUpd(struct swic_Reg_Timer *const tim, const sint32 tmo)
{
	if (tmo > 0) {
		sint32	cnt = tim->tim + SWIC_ETH_PERIOD;
		if (cnt >= tmo) {
			cnt -= tmo;
			tim->req = STD_ON;		/* 定期動作:遅れても複数回処理しない */
		}
		tim->tim = cnt;
	}
}
void EthSwt_SWIC_MainFunction1MS(void)
{	/* 1ms周期タスク */
	swic_Reg_Inf.tim = swic_Reg_Inf.tim + (uint16)SWIC_ETH_PERIOD;
	if (swic_Reg_Inf.sts == ETHSWT_SWIC_STATE_ACTIVE) {
		uint32		i;
#if 0 /* 未対応 SWICリセット(異常)検出 */
		swic_Reg_TimUpd(&swic_Reg_Inf.timrst, SWIC_REG_TIMRST);
#endif
#if 0 /* 未対応 SWIC内部エラー検出 */
		swic_Reg_TimUpd(&swic_Reg_Inf.timerr, SWIC_REG_TIMERR);
#endif
		swic_Reg_TimUpd(&swic_Reg_Inf.timlnk, SWIC_REG_TIMLNK);
		for (i=0U ; i<SWIC_TBL_NUM(swic_Reg_Mode) ; i++) {
#if 0 /* 未対応 IDS */
			swic_Reg_TimUpd(&swic_Reg_Mode[i].ids, swic_Reg_PortDef[i].tmo_IDS);
#endif
#if 0 /* 未対応 SQI */
			swic_Reg_TimUpd(&swic_Reg_Mode[i].sqi, swic_Reg_PortDef[i].tmo_SQI);
#endif
		}

	}
}

#if 0 /* NCOS Soft */
void EthSwt_SWIC_MainFunction5MS(void)
{
	EthSwt_SWIC_Org_MainFunction();
}

void EthSwt_SWIC_RESET_N_Lo(void)
{
    EthSwt_SWIC_Org_ResetSig_Lo();
    return;
}
void EthSwt_SWIC_RESET_N_Hi(void)
{
    EthSwt_SWIC_Org_ResetSig_Hi();
    return;
}
void EthSwt_SWIC_DeInit(void){
    EthSwt_SWIC_Org_DeInit();
    return;
}
#endif

#if 0 /* For HND DTC */
	EthSwt_SWIC_DTC_MainFunction1MS();
#endif


#if 0 /* For BSW */
void EthSwt_SWIC_MainFunction(void)
{	/* Ethの周期タスク */
	uint8	idx;
	for (idx=0u ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		if (swic_Reg_Mode[idx].ind_mode == STD_ON) {
			swic_Reg_Mode[idx].ind_mode = STD_OFF;
			EthIf_SwitchPortModeIndication(ETHSWT_SWIC_IDX, idx, swic_Reg_Mode[idx].mode);	/* [SWS_EthSwt_00398] */
		}
	}
}
#endif


Std_ReturnType EthSwt_SWIC_Reg_SetSwitchPortMode(const uint8 SwitchPortIdx, const Eth_ModeType PortMode)
{	/* 1msタスク */
	if (swic_Reg_Inf.sts == ETHSWT_SWIC_STATE_UNINIT)	{ return E_NOT_OK; }
	if (SwitchPortIdx >= SWIC_TBL_NUM(swic_Reg_Mode))	{ return E_NOT_OK; }
	swic_Reg_Mode[SwitchPortIdx].mode_chg	= PortMode;
	swic_Reg_Mode[SwitchPortIdx].req_mode	= STD_ON;	/* 処理前に複数呼ばれた場合は最新が有効 */
	return E_OK;
}
#if 0 /* For BSW */
Std_ReturnType EthSwt_SWIC_Reg_GetSwitchPortMode(const uint8 SwitchPortIdx, Eth_ModeType *const SwitchModePtr)
{	/* 1msタスク */
	if (swic_Reg_Inf.sts == ETHSWT_SWIC_STATE_UNINIT)	{ return E_NOT_OK; }
	if (SwitchPortIdx >= SWIC_TBL_NUM(swic_Reg_Mode))	{ return E_NOT_OK; }
	if (SwitchModePtr == NULL_PTR)						{ return E_NOT_OK; }
	*SwitchModePtr = swic_Reg_Mode[SwitchPortIdx].mode;	/* 変数に記憶するので[SWS_EthSwt_00400]は不要 */
	return E_OK;
}
#endif
Std_ReturnType EthSwt_SWIC_Reg_GetLinkState(const uint8 SwitchPortIdx, EthTrcv_LinkStateType * const LinkStatePtr)
{	/* 1msタスク */
	if (swic_Reg_Inf.sts != ETHSWT_SWIC_STATE_ACTIVE)	{ return E_NOT_OK; }	/* 初期化中は異常 */
	if (SwitchPortIdx >= SWIC_TBL_NUM(swic_Reg_Mode))	{ return E_NOT_OK; }
	if (LinkStatePtr == NULL_PTR)						{ return E_NOT_OK; }
	*LinkStatePtr = swic_Reg_Mode[SwitchPortIdx].lnk_sts;
	return swic_Reg_Mode[SwitchPortIdx].lnk_err;
}

#if 0 /* For HND PhyReset*/
Std_ReturnType EthSwt_SWIC_Reg_PortPhyResetRequest(const uint8 SwitchPortIdx)
{	/* 5msタスク */
	if (swic_Reg_Inf.sts != ETHSWT_SWIC_STATE_ACTIVE)	{ return E_NOT_OK; }
	if (SwitchPortIdx >= SWIC_TBL_NUM(swic_Reg_Mode))	{ return E_NOT_OK; }
	swic_Reg_Mode[SwitchPortIdx].req_rst = STD_ON;
	return E_OK;
}
#endif

#if 0 /* 未対応 IDS */
Std_ReturnType EthSwt_SWIC_Reg_GetIDSInfo(const uint8 SwitchPortIdx, uint32 *const IDSInfo)
{	/* 5msタスク */
	if (swic_Reg_Inf.sts == ETHSWT_SWIC_STATE_UNINIT)	{ return E_NOT_OK; }
	if (SwitchPortIdx >= SWIC_TBL_NUM(swic_Reg_Mode))	{ return E_NOT_OK; }
	if (IDSInfo == NULL_PTR)							{ return E_NOT_OK; }
	*IDSInfo = swic_Reg_Mode[SwitchPortIdx].FiltFrm;
	swic_Reg_Mode[SwitchPortIdx].FiltFrm = 0uL;
	return E_OK;
}
#endif

#if 0 /* 未対応 SQI */
Std_ReturnType EthSwt_SWIC_Reg_GetSqiValue(const uint8 SwitchPortIdx, uint8 *const SqiValuePrt)
{	/* 5msタスク */
	if (swic_Reg_Inf.sts == ETHSWT_SWIC_STATE_UNINIT)	{ return E_NOT_OK; }
	if (SwitchPortIdx >= SWIC_TBL_NUM(swic_Reg_Mode))	{ return E_NOT_OK; }
	if (SqiValuePrt == NULL_PTR)						{ return E_NOT_OK; }
	*SqiValuePrt = swic_Reg_Mode[SwitchPortIdx].sqi_val;/* 更新前は同じ値を返す */
	return swic_Reg_Mode[SwitchPortIdx].sqi_err;
}
#endif

#if 0 /* For HND DTC */
#ifdef	SWIC_OPT_DTC	/* DTC有 */
void EthSwt_SWIC_Reg_ClrDTC(void)
{	/* 1ms/5msタスク:[対象]保持している値/レジスタ値/タイマ:同じ値を書き込むだけなので排他不要 */
	uint8	idx;
	for (idx=0u ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		swic_Reg_Mode[idx].FiltFrm = 0uL;
	}
	if (swic_Reg_Inf.sts == ETHSWT_SWIC_STATE_ACTIVE) {	/* 保持値ぐらいはクリアしておく */
		swic_Reg_ReqClrDTC = STD_ON;
		LIB_DI();	/* 1msに負荷をかけないようここでクリア */
		swic_Reg_TimClrDTC();
		LIB_EI();
	}
}
#endif					/* SWIC_OPT_DTC */
#endif

#if 0 /* For HND RSW2*/
EthSwt_StateType EthSwt_SWIC_GetState(void)
{	/* 1msタスク */
	EthSwt_StateType	ret;
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_ACTIVE:
		ret = ETHSWT_STATE_ACTIVE;
		break;
	case ETHSWT_SWIC_STATE_INIT:
		ret = ETHSWT_STATE_INIT;
		break;
	case ETHSWT_SWIC_STATE_RESET:
	case ETHSWT_SWIC_STATE_PMIC:
		ret = ETHSWT_STATE_PORTINIT_COMPLETED;
		break;
	case ETHSWT_SWIC_STATE_UNINIT:
	default:	/* default */
		ret = ETHSWT_STATE_UNINIT;
		break;
	}
	return ret;
}
#endif

#if 0 /* For HND EthDbg */
static void swic_Reg_ResetFact(const uint32 fact)
{	/* リセット要因更新 */
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_ACTIVE:	/* ACTIVEから遷移するときにクリア */
		swic_Reg_Err.rst_fct  = fact << 16;
		break;
	case ETHSWT_SWIC_STATE_RESET:	/* RESET中は反映しない */
	case ETHSWT_SWIC_STATE_PMIC:	/* PMIC OFF中も反映しない */
		break;
	case ETHSWT_SWIC_STATE_UNINIT:
	case ETHSWT_SWIC_STATE_INIT:
	default:						/* 他は追記 */
		swic_Reg_Err.rst_fct |= fact;
		break;
	}
}
#endif

static void swic_Reg_Reset(const uint32 fact)
{
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_UNINIT:	/* 停止中は遷移しない */
	case ETHSWT_SWIC_STATE_PMIC:	/* Ether PMICが優先 */
		break;
	case ETHSWT_SWIC_STATE_ACTIVE:
	case ETHSWT_SWIC_STATE_INIT:
	case ETHSWT_SWIC_STATE_RESET:
	default:
#if 0 /* For HND EthDbg */
/*koko*/#ifndef EthDbg_Swt_CrcOFF
/*koko*/if (EthDbg_Swt_CrcOFF(fact) != E_OK) { break; }
/*koko*/#endif	/* EthDbg_Swt_CrcOFF */
		swic_Reg_ResetFact(fact);
#endif
		swic_Reg_SetState(ETHSWT_SWIC_STATE_RESET);
		break;
	}
}

#if 0 /* For HND EthDbg */
#ifndef	EthDbg_GetMibOFF			/* EthDbg用 */
uint32 EthSwt_SWIC_Reg_GetResetFact(void)	{ return swic_Reg_Err.rst_fct; }
void EthSwt_SWIC_Reg_Reset(void)			{ swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_CMD); }
#endif								/* EthDbg_GetMibOFF */
#endif

static Std_ReturnType swic_Reg_SetTblErr(const swic_reg_data_t tbl[], const uint32 idx, const uint16 val)
{
	swic_Reg_Err.tbl	= tbl;
	swic_Reg_Err.idx	= idx;
	swic_Reg_Err.val	= val;

#if 0 /* For HND EthDbg */
/*koko*/EthDbg_LOGCHG(89u, ETHSWT_SWIC_IDX | 0xF0u, idx, tbl)
/*koko*//*EthDbg_LOGCHG(89u, ETHSWT_SWIC_IDX | 0xF0u, idx, val)*/
#endif

	return E_NOT_OK;
}

#if 0 /* For HND PMIC */
#ifdef	SWIC_OPT_PMIC				/* Ether PMIC有 */
static Std_ReturnType swic_Reg_EtherPMIC(void)
{
	uint8	err, stat, din;
	err = I2cM_Rslt_Ethpmic_GetState(&stat, &din);
/*koko*/EthDbg_LOGCHG(89u, ETHSWT_SWIC_IDX, 0x20u, ((uint32)err << 24) | ((uint32)stat << 8) | din)
	if (err != E_OK)				{ return E_NOT_OK; }
	if ((stat & 0x1Fu) != 0x14u)	{ return E_NOT_OK; }	/* INTERNAL_STATE=0x14:[addr]1Ah[bit]4～0 */
	if ((din  & 0x20u) == 0u)		{ return E_NOT_OK; }	/* DIN2_STAT=1        :[addr]19h[bit]5 */
	return E_OK;
}
static Std_ReturnType swic_Reg_EtherPMIC_OFF(void)
{
	Std_ReturnType	err;
	err = swic_Reg_EtherPMIC();
	if (err != E_OK) {
		swic_Reg_ResetFact(ETHSWT_SWIC_REG_FACT_PMIC);
		swic_Reg_SetState(ETHSWT_SWIC_STATE_PMIC);
	}
	return err;
}
#endif								/* SWIC_OPT_PMIC */
#endif

static Std_ReturnType swic_Reg_SetTblWriteOFF(const Std_ReturnType ret, const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx)
{
	Std_ReturnType	err;
	uint32			i;
	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		err = EthSwt_SWIC_Spi_Write(tbl, cnt, idx);
		if (err == E_OK) {
#if 0 /* For HND DTC */
			EthSwt_SWIC_DTC_SpiOK();
#endif
			return ret;
		}
#if 0 /* For HND PMIC */
		#ifdef	SWIC_OPT_PMIC					/* Ether PMIC有 */
		err = swic_Reg_EtherPMIC_OFF();
		if (err != E_OK)	{ return err; }
		#endif									/* SWIC_OPT_PMIC */
#endif
	}
#if 0 /* For HND DTC */
	EthSwt_SWIC_DTC_SpiNG();
#endif
	swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_CRC);	/* リセット */
	return swic_Reg_SetTblErr(tbl, idx, 0u);
}
static Std_ReturnType swic_Reg_SetTblReadOFF(const Std_ReturnType ret, const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx, uint32 * const dat)
{
	Std_ReturnType	err;
	uint16			val = 0u;
	uint32			i;
	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		err = EthSwt_SWIC_Spi_Read(tbl, cnt, idx, &val);
		if (err == E_OK) {
#if 0 /* For HND DTC */
			EthSwt_SWIC_DTC_SpiOK();
#endif
			if (dat != NULL_PTR) {	/* データ取得 */
				*dat = (*dat << 16) | ((uint32)val & (uint32)tbl[idx].mask);
				return ret;
			}						/* リードバック無効に以降はない */
			if (((val ^ tbl[idx].value) & tbl[idx].mask) == 0u)	{ return ret; }	/* 一致 */
			return swic_Reg_SetTblErr(tbl, idx, val);	/* リードバック異常はswic_Reg_SwitchInitでリセット */
		}

#if 0 /* For HND PMIC */
		#ifdef	SWIC_OPT_PMIC					/* Ether PMIC有 */
		err = swic_Reg_EtherPMIC_OFF();
		if (err != E_OK)	{ return err; }
		#endif									/* SWIC_OPT_PMIC */
#endif

	}

#if 0 /* For HND DTC */
	EthSwt_SWIC_DTC_SpiNG();
#endif

	swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_CRC);	/* リセット */
	return swic_Reg_SetTblErr(tbl, idx, val);
}
static Std_ReturnType swic_Reg_SetTblReadON(const Std_ReturnType ret, const swic_reg_data_t tbl[], const uint32 idx, const uint16 mask, const uint16 value)
{
	Std_ReturnType	err;
	uint16			val = 0u;
	uint32			i;
	uint16			cnt = 0u;
	const uint16	tim = swic_Reg_Inf.tim;
	for (i=0uL ; i<SWIC_REG_WAIT_L ; i++) {
		uint16	tmo;
		err = EthSwt_SWIC_Spi_ReadSPI(tbl, idx, &val);
		if (err == E_OK) {

#if 0 /* For HND DTC */
			EthSwt_SWIC_DTC_SpiOK();
#endif

			if (((val ^ value) & mask) == 0u) { return ret; }
			cnt = 0u;							/* 連続3回 */
		}
		else {
#if 0 /* For HND PMIC */
			#ifdef	SWIC_OPT_PMIC				/* Ether PMIC有 */
			err = swic_Reg_EtherPMIC_OFF();
			if (err != E_OK)	{ return err; }
			#endif								/* SWIC_OPT_PMIC */
#endif
			cnt = cnt + (uint16)1;
			if (cnt >= INIT_SEQ_RETRY_CNT) {
#if 0 /* For HND DTC */
				EthSwt_SWIC_DTC_SpiNG();
#endif
				swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_CRC);	/* リセット */
				return swic_Reg_SetTblErr(tbl, idx, val);
			}
		}
		tmo = swic_Reg_Inf.tim - tim;
		if (tmo > SWIC_REG_WAIT) { break; }
	}
	swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_BSY);	/* リセット */
	return swic_Reg_SetTblErr(tbl, idx, val);
}
static Std_ReturnType swic_Reg_SetTblWriteMask(const Std_ReturnType ret, const swic_reg_data_t tbl[], const uint32 idx, uint16 val)
{
	Std_ReturnType	err;
	uint32			i;
	val ^= val & tbl[idx].mask;
	val |= tbl[idx].value & tbl[idx].mask;
	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		err = EthSwt_SWIC_Spi_WriteSPI(tbl, idx, val);
		if (err == E_OK) {
#if 0 /* For HND DTC */
			EthSwt_SWIC_DTC_SpiOK();
#endif
			return ret;
		}
#if 0 /* For HND PMIC */
		#ifdef	SWIC_OPT_PMIC					/* Ether PMIC有 */
		err = swic_Reg_EtherPMIC_OFF();
		if (err != E_OK)	{ return err; }
		#endif									/* SWIC_OPT_PMIC */
#endif
	}
#if 0 /* For HND DTC */
	EthSwt_SWIC_DTC_SpiNG();
#endif
	swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_CRC);	/* リセット */
	return swic_Reg_SetTblErr(tbl, idx, val);
}
static Std_ReturnType swic_Reg_SetTblReadMask(const Std_ReturnType ret, const swic_reg_data_t tbl[], const uint32 idx, uint16 *const val)
{
	Std_ReturnType	err;
	uint32			i;
	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		err = EthSwt_SWIC_Spi_ReadSPI(tbl, idx, val);
		if (err == E_OK) {
#if 0 /* For HND DTC */
			EthSwt_SWIC_DTC_SpiOK();
#endif
			return ret;
		}
#if 0 /* For HND DTC */
		#ifdef	SWIC_OPT_PMIC					/* Ether PMIC有 */
		err = swic_Reg_EtherPMIC_OFF();
		if (err != E_OK)	{ return err; }
		#endif									/* SWIC_OPT_PMIC */
#endif
	}
#if 0 /* For HND DTC */
	EthSwt_SWIC_DTC_SpiNG();
#endif
	swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_CRC);	/* リセット */
	return swic_Reg_SetTblErr(tbl, idx, 0u);
}
static Std_ReturnType swic_Reg_SetTbl(const swic_reg_data_t tbl[], const uint32 cnt, uint32 * const dat)
{
	Std_ReturnType	ret = E_OK;
	uint32			idx;
	uint16			val = 0U;

	if (cnt <= 0uL) 		{ return E_OK; }
	if (tbl == NULL_PTR)	{ return E_NOT_OK; }
	EthSwt_SWIC_Spi_ReqInit();
	if (dat != NULL_PTR)	{ *dat = 0u; }
	for (idx=0U; idx < cnt ; idx++) {
		const EthSwt_SWIC_StateType	sts = swic_Reg_Inf.sts;
		if ((sts != ETHSWT_SWIC_STATE_INIT)
		&&  (sts != ETHSWT_SWIC_STATE_ACTIVE)) { return E_NOT_OK; }
		switch (((uint16)tbl[idx].regCtrl << 8) | tbl[idx].surveillance) {
		case ((uint16)REG_CTRL_WRITE << 8) | SURVEILLANCE_ON:	/* リードバック無 */
		case ((uint16)REG_CTRL_WRITE << 8) | SURVEILLANCE_OFF:
			ret = swic_Reg_SetTblWriteOFF(ret, tbl, cnt, idx);
			break;
		case ((uint16)REG_CTRL_READ << 8) | SURVEILLANCE_ON:
			ret = swic_Reg_SetTblReadON(ret, tbl, idx, tbl[idx].mask, tbl[idx].value);
			break;
		case ((uint16)REG_CTRL_READ << 8) | SURVEILLANCE_OFF:
			ret = swic_Reg_SetTblReadOFF(ret, tbl, cnt, idx, dat);
			break;
		case ((uint16)REG_CTRL_WRITE_MASK << 8) | SURVEILLANCE_OFF:
			ret = swic_Reg_SetTblWriteMask(ret, tbl, idx, val);
			break;
		case ((uint16)REG_CTRL_READ_TMP << 8) | SURVEILLANCE_OFF:
			ret = swic_Reg_SetTblReadMask(ret, tbl, idx, &val);
			break;
		default:
			ret = swic_Reg_SetTblErr(tbl, idx, 0u);
			break;
		}
	}
	return ret;
}
static Std_ReturnType swic_Reg_TblReg(const uint8 SwitchPortIdx, const struct swic_reg_tbl tbl[], const uint32 num)
{
	uint32		val;	/* g_regListSeqSet100BTxStartなどの余分な読み込み対策 */
	if (SwitchPortIdx >= num)				{ return E_NOT_OK; }
	if (tbl[SwitchPortIdx].num <= 0uL)		{ return E_NOT_OK; }
	if (tbl[SwitchPortIdx].tbl == NULL_PTR)	{ return E_NOT_OK; }
	return swic_Reg_SetTbl(tbl[SwitchPortIdx].tbl, tbl[SwitchPortIdx].num, &val);
}
static Std_ReturnType swic_Reg_SetSwitchPortModeACTIVE(const uint8 SwitchPortIdx)
{
#if 0 /* For HND RelayOn */
	static const struct swic_reg_tbl tbl[]
	=	{ {&g_regListSeqRelayOn[7],		1u}	/* P8 */
		, {&g_regListSeqRelayOn[0],		1u}	/* P1 */
		, {&g_regListSeqRelayOn[1],		1u}
		, {&g_regListSeqRelayOn[2],		1u}
		, {&g_regListSeqRelayOn[3],		1u}
		, {&g_regListSeqRelayOn[4],		1u}
		, {g_regListSeqSet100BTxStart,	SWIC_TBL_NUM(g_regListSeqSet100BTxStart)}
		};
	return swic_Reg_TblReg(SwitchPortIdx, tbl, SWIC_TBL_NUM(tbl));
#endif

#if 1 /* NCOS Soft idxに合わせて修正 */
	static const struct swic_reg_tbl phyon_tbl[]
	= { {NULL_PTR,					0u}												/* P9：未使用                  */
	  , {g_regListSeqP1PhyOn,			SWIC_TBL_NUM(g_regListSeqP1PhyOn)}			/* P1：ADC 1000BASE-T1         */
	  , {g_regListSeqP2PhyOn,			SWIC_TBL_NUM(g_regListSeqP2PhyOn)}			/* P2：DCM 1000BASE-T1         */
	  , {NULL_PTR,					0u}												/* P3：未使用                  */
	  , {NULL_PTR,					0u}												/* P4：未使用                  */
	  , {NULL_PTR,					0u}												/* P5：SIP SAILSS_RGMII0 RGMII */
	  , {g_regListSeqP6PhyOn,			SWIC_TBL_NUM(g_regListSeqP6PhyOn)}			/* P6：DLC 100BASE-TX          */
	  , {NULL_PTR,					0u}												/* P7：SIP SGMII0 SGMII        */
	  , {NULL_PTR,					0u}												/* P8：SIP SGMII1 SGMII        */
	  };
	static const struct swic_reg_tbl actdis_tbl[]
	= { {NULL_PTR,					0u}												/* P9：未使用                  */
	  , {g_regListSeqSetP1ActDis,		SWIC_TBL_NUM(g_regListSeqSetP1ActDis)}		/* P1：ADC 1000BASE-T1         */
	  , {g_regListSeqSetP2ActDis,		SWIC_TBL_NUM(g_regListSeqSetP2ActDis)}		/* P2：DCM 1000BASE-T1         */
	  , {NULL_PTR,					0u}												/* P3：未使用                  */
	  , {NULL_PTR,					0u}												/* P4：未使用                  */
	  , {NULL_PTR,					0u}												/* P5：SIP SAILSS_RGMII0 RGMII */
	  , {g_regListSeqSet100BTxStart,	SWIC_TBL_NUM(g_regListSeqSet100BTxStart)}	/* P6：DLC 100BASE-TX          */
	  , {NULL_PTR,					0u}												/* P7：SIP SGMII0 SGMII        */
	  , {NULL_PTR,					0u}												/* P8：SIP SGMII1 SGMII        */
	  };
	Std_ReturnType						ret;
	ret = swic_Reg_TblReg(SwitchPortIdx, phyon_tbl, SWIC_TBL_NUM(phyon_tbl));
	if (ret == E_NOT_OK) {return E_NOT_OK;}
	return swic_Reg_TblReg(SwitchPortIdx, actdis_tbl, SWIC_TBL_NUM(actdis_tbl));
#endif
}
static Std_ReturnType swic_Reg_SetSwitchPortModeDOWN(const uint8 SwitchPortIdx)
{
#if 0 /* For HND RelayOff */
	static const struct swic_reg_tbl tbl[]
	=	{ {&g_regListSeqRelayOff[14],	2u}	/* P8 */
		, {&g_regListSeqRelayOff[0],	2u}	/* P1 */
		, {&g_regListSeqRelayOff[2],	2u}
		, {&g_regListSeqRelayOff[4],	2u}
		, {&g_regListSeqRelayOff[6],	2u}
		, {&g_regListSeqRelayOff[8],	2u}
		, {g_regListSeqSet100BTxDown,	SWIC_TBL_NUM(g_regListSeqSet100BTxDown)}
		};
	return swic_Reg_TblReg(SwitchPortIdx, tbl, SWIC_TBL_NUM(tbl));
#endif

#if 1 /* NCOS Soft idxに合わせて修正 */
	static const struct swic_reg_tbl tbl[]
	=	{ {NULL_PTR,					0u}											/* P9：未使用                  */
		, {g_regListSeqP1PhyOff,		SWIC_TBL_NUM(g_regListSeqP1PhyOff)}			/* P1：ADC 1000BASE-T1         */
		, {g_regListSeqP2PhyOff,		SWIC_TBL_NUM(g_regListSeqP2PhyOff)}			/* P2：DCM 1000BASE-T1         */
		, {NULL_PTR,					0u}											/* P3：未使用                  */
		, {NULL_PTR,					0u}											/* P4：未使用                  */
		, {NULL_PTR,					0u}											/* P5：SIP SAILSS_RGMII0 RGMII */
		, {g_regListSeqSet100BTxDown,	SWIC_TBL_NUM(g_regListSeqSet100BTxDown)}	/* P6：DLC 100BASE-TX          */
		, {NULL_PTR,					0u}											/* P7：SIP SGMII0 SGMII        */
		, {NULL_PTR,					0u}											/* P8：SIP SGMII1 SGMII        */
		};
	return swic_Reg_TblReg(SwitchPortIdx, tbl, SWIC_TBL_NUM(tbl));
#endif
}
static Std_ReturnType swic_Reg_GetLink(const uint8 SwitchPortIdx, EthTrcv_LinkStateType *const LinkStatePtr)
{
	struct swic_tbl_lnk {
		const swic_reg_data_t	*tbl;
		const uint32			num;
		const uint32			msk;
		const uint32			dat;
	};

#if 0 /* For HND GetLink */
	static const struct swic_tbl_lnk	tbl[]
	=	{ {&g_regListSeqGetLinkIeee[25], 1u, 0x0800u, 0x0800u}	/* P8 */
		, {&g_regListSeqGetLinkIeee[ 0], 1u, 0x0800u, 0x0800u}	/* P1 */
		, {&g_regListSeqGetLinkIeee[ 1], 1u, 0x0800u, 0x0800u}
		, {&g_regListSeqGetLinkIeee[ 2], 7u, 0x0004u, 0x0004u}
		, {&g_regListSeqGetLinkIeee[ 9], 7u, 0x0004u, 0x0004u}
		, {&g_regListSeqGetLinkIeee[16], 7u, 0x0004u, 0x0004u}
		, {&g_regListSeqGetLinkIeee[23], 1u, 0x0800u, 0x0800u}
		};
#endif

#if 1 /* NCOS Soft idxに合わせて修正 */
	static const struct swic_tbl_lnk	tbl[]
	=	{ {&g_regListSeqGetLinkIeee[26], 1u, 0x0800u, 0x0800u}	/* P9：未使用                  */
		, {&g_regListSeqGetLinkIeee[ 0], 1u, 0x0800u, 0x0800u}	/* P1：ADC 1000BASE-T1         */
		, {&g_regListSeqGetLinkIeee[ 1], 1u, 0x0800u, 0x0800u}	/* P2：DCM 1000BASE-T1         */
		, {&g_regListSeqGetLinkIeee[ 2], 7u, 0x0004u, 0x0004u}	/* P3：未使用                  */
		, {&g_regListSeqGetLinkIeee[ 9], 7u, 0x0004u, 0x0004u}	/* P4：未使用                  */
		, {&g_regListSeqGetLinkIeee[16], 7u, 0x0004u, 0x0004u}	/* P5：SIP SAILSS_RGMII0 RGMII */
		, {&g_regListSeqGetLinkIeee[23], 1u, 0x0800u, 0x0800u}	/* P6：DLC 100BASE-TX          */
		, {&g_regListSeqGetLinkIeee[24], 1u, 0x0800u, 0x0800u}	/* P7：SIP SGMII0 SGMII        */
		, {&g_regListSeqGetLinkIeee[25], 1u, 0x0800u, 0x0800u}	/* P8：SIP SGMII1 SGMII        */
		};
#endif

	Std_ReturnType	err;
	uint32			val = 0uL;
	if (SwitchPortIdx >= SWIC_TBL_NUM(tbl))	{ return E_NOT_OK; }
	if (LinkStatePtr == NULL_PTR)			{ return E_NOT_OK; }
#if 0 /* For HND */
/*	if (tbl[SwitchPortIdx].num <= 0uL)		{ return E_NOT_OK; }	[C1対策]読めないポートが出たら戻す */
#endif
	err = swic_Reg_SetTbl(tbl[SwitchPortIdx].tbl, tbl[SwitchPortIdx].num, &val);
	if (err == E_OK) {
		*LinkStatePtr = ((val & tbl[SwitchPortIdx].msk) == tbl[SwitchPortIdx].dat) ? ETHTRCV_LINK_STATE_ACTIVE : ETHTRCV_LINK_STATE_DOWN;
	}
	return err;
}

#if 0 /* 未対応 IDS, 帯域制限 */
#ifdef	SWIC_REG_IDSPORT			/* IDS対象 */
static void swic_Reg_AddVal(uint32 *const num, const swic_reg_data_t tbl[], const uint32 cnt)
{
	Std_ReturnType	err;
	uint32			val = 0uL;
	err = swic_Reg_SetTbl(tbl, cnt, &val);
	if (err != E_OK)	{ return; }	/* 失敗 */
	if (num == NULL_PTR){ return; }	/* 空読み */
	LIB_DI();	/* 5msでクリアされる */
	*num = (((~0uL) - *num) >= val) ? *num + val : ~0uL;
	LIB_EI();
}
void EthSwt_SWIC_Reg_UpdStreamFilterCounter(const uint8 SwitchPortIdx, uint32 *const num)
{
	static const swic_reg_data_t	reg_bsy = {0x1cu,0x16u,0x01u,0x01u,0x8000u,0x0000u};	/* バージョンにより先頭2行が入れ替わるので暫くローカルで持つ */
	swic_reg_data_t					reg_tgt = {0x1cu,0x17u,0x00u,0x00u,0xFFFFu,0xF000u};
	Std_ReturnType					err;
	if (SwitchPortIdx >= SWIC_TBL_NUM(swic_Reg_IdsPort)){ return; }		/* StreamFilter無 */
	if (swic_Reg_IdsPort[SwitchPortIdx] == 0u)			{ return; }		/* StreamFilter無 */
	err = swic_Reg_SetTbl(&reg_bsy, 1uL, NULL_PTR);
	if (err != E_OK)									{ return; }
	reg_tgt.value = (uint16)0xEFFF + swic_Reg_IdsPort[SwitchPortIdx];	/* No1 = 0xF000u */
	err = swic_Reg_SetTbl(&reg_tgt, 1uL, NULL_PTR);						/* REG_CTRL_WRITEのみ */
	if (err == E_OK) {
		swic_Reg_AddVal(num, &g_regListSeqGetStreamFilterData[2], SWIC_TBL_NUM(g_regListSeqGetStreamFilterData) - 2uL);
	}
}
#else								/* IDS無効 */
void EthSwt_SWIC_Reg_UpdStreamFilterCounter(const uint8 SwitchPortIdx, uint32 *const num)
{ (void)SwitchPortIdx; if (num != NULL_PTR) { *num = 0uL; } }
#endif								/* SWIC_REG_IDSPORT */
#endif

#if 0 /* 未対応 SQI */
void EthSwt_SWIC_Reg_UpdSQI(const uint8 SwitchPortIdx)
{
	static const struct {
		const struct swic_reg_tbl	tbl;
		const uint32				sft;
	}	tbl[]
	=	{ {{NULL_PTR,                    0u}, 0uL}	/* P8 */
		, {{&g_regListSeqGetSqi1000B[0], 7u}, 0uL}	/* P1 */
		, {{&g_regListSeqGetSqi1000B[7], 7u}, 0uL}	/* bit[2:0] */
		, {{&g_regListSeqGetSqi100B[14], 7u}, 13uL}	/* bit[15:12]の上位3bit */
		, {{&g_regListSeqGetSqi100B[21], 7u}, 13uL}
		, {{&g_regListSeqGetSqi100B[28], 7u}, 13uL}
		, {{&g_regListSeqGetSqi100B[35], 7u}, 13uL}
		};
	Std_ReturnType	err;
	uint32			val = 0uL;
	if (SwitchPortIdx >= SWIC_TBL_NUM(tbl))	{ return; }
	if (tbl[SwitchPortIdx].tbl.num <= 0uL)	{ return; }
	err = swic_Reg_SetTbl(tbl[SwitchPortIdx].tbl.tbl, tbl[SwitchPortIdx].tbl.num, &val);
	if (err == E_OK) {	/* E_OKのみ更新、E_NOT_OK→E_OKのsqi_valは不定なので先に更新 */
		swic_Reg_Mode[SwitchPortIdx].sqi_val = (uint8)((val >> tbl[SwitchPortIdx].sft) & 7uL);
	}
	swic_Reg_Mode[SwitchPortIdx].sqi_err = err;	/* 現在値が欲しいのでアクセス失敗時も更新 */
}
#endif

#if 0 /* For HND PhyReset */
static Std_ReturnType swic_Reg_PortPhyReset(const uint8 SwitchPortIdx)
{
	static const struct swic_reg_tbl tbl[]
	=	{ {NULL_PTR,					0u}	/* P8 */
		, {&g_regListSeqPhyReset[ 0],	6u}	/* P1 */
		, {&g_regListSeqPhyReset[ 6],	6u}
		, {&g_regListSeqPhyReset[12],	6u}
		, {&g_regListSeqPhyReset[18],	6u}
		, {&g_regListSeqPhyReset[24],	6u}
		, {&g_regListSeqPhyReset[30],	6u}
		};
	return swic_Reg_TblReg(SwitchPortIdx, tbl, SWIC_TBL_NUM(tbl));
}
#endif

#if 0 /* 未対応 SWIC内部エラー検出*/
static void swic_Reg_PortMacResetRequest(void)
{
	static const struct {
		const struct swic_reg_tbl	tbl;	/* 処理テーブル */
		const sint32				tmo;	/* 処理後に待つ時間(ms) */
	}	tbl[]
	=	{ {SWIC_REG_TBL(g_regListSeqRelayOff),	2}	/* 2ms wait */
		, {SWIC_REG_TBL(g_regListSeqSWICReset),	0}	/* ↑余分な読み込みがあるのでチェックにできない */
		, {SWIC_REG_TBL(g_regListSeqRelayOn),	0}
		};
	static const struct swic_reg_tbl off[]
#if 0 /* For HND */
	=	{ {&g_regListSeqRelayOff[14],	2u}	/* P8 */
		, {&g_regListSeqRelayOff[0],	2u}	/* P1 */
		, {&g_regListSeqRelayOff[2],	2u}
		, {&g_regListSeqRelayOff[4],	2u}
		, {&g_regListSeqRelayOff[6],	2u}
		, {&g_regListSeqRelayOff[8],	2u}
		, {&g_regListSeqRelayOff[10],	2u}
		};
#endif

#if 1 /* NCOS Soft idxに合わせて修正 */
	=	{ {&g_regListSeqRelayOff[16],	2u}	/* P9：未使用                  */
		, {&g_regListSeqRelayOff[0],	2u}	/* P1：ADC 1000BASE-T1         */
		, {&g_regListSeqRelayOff[2],	2u}	/* P2：DCM 1000BASE-T1         */
		, {&g_regListSeqRelayOff[4],	2u}	/* P3：未使用                  */
		, {&g_regListSeqRelayOff[6],	2u}	/* P4：未使用                  */
		, {&g_regListSeqRelayOff[8],	2u}	/* P5：SIP SAILSS_RGMII0 RGMII */
		, {&g_regListSeqRelayOff[10],	2u}	/* P6：DLC 100BASE-TX          */
		, {&g_regListSeqRelayOff[12],	2u}	/* P7：SIP SGMII0 SGMII        */
		, {&g_regListSeqRelayOff[14],	2u}	/* P8：SIP SGMII1 SGMII        */
	};
#endif
	uint32	i;
	uint32	val;
	uint8	idx;
	for (i=0u ; i<SWIC_TBL_NUM(tbl) ; i++) {
		(void)swic_Reg_SetTbl(tbl[i].tbl.tbl, tbl[i].tbl.num, &val);
		if (tbl[i].tmo > 0) {
			EthSwt_SWIC_Org_WaitMS(tbl[i].tmo);
		}
	}
	for (idx=0U ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		if (swic_Reg_Mode[idx].mode != ETH_MODE_DOWN)	{ continue; }	/* リンクダウン不要 */
		(void)swic_Reg_TblReg(idx, off, SWIC_TBL_NUM(off));
	}
}
#endif

static Std_ReturnType swic_Reg_ResetSwitchPortMode(Std_ReturnType ret)
{	/* 初期化後EthSwt_SetSwitchPortModeの状態に戻す */
	Std_ReturnType	err;
	uint8			i;
	for (i=0U ; i<SWIC_TBL_NUM(swic_Reg_Mode) ; i++) {
		if (swic_Reg_Mode[i].mode == swic_Reg_PortDef[i].mode)	{ continue; }	/* 動作モード変更無 */
		switch (swic_Reg_Mode[i].mode) {
		case ETH_MODE_ACTIVE:
			err = swic_Reg_SetSwitchPortModeACTIVE(i);
			if (err != E_OK) { ret = err; }
			break;
		case ETH_MODE_DOWN:
			err = swic_Reg_SetSwitchPortModeDOWN(i);
			if (err != E_OK) { ret = err; }
			break;
		default:	/* default */
			break;
		}
	}
	return ret;
}
static void swic_Reg_SwitchInit(void)
{
	struct swic_reg_seq {				/* 余分な読み込みを有無 */
		struct swic_reg_tbl	tbl;
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
#if 0 /* 未対応　ACT定義 */
		, {SWIC_REG_TBL(g_regListAcl)					, STD_OFF}	/* ACL設定 */
#endif
		#ifndef	g_regListArp
		, {SWIC_REG_TBL(g_regListArp)					, STD_OFF}	/* ARP設定 */
		#endif														/* g_regListArp */
		, {SWIC_REG_TBL(g_regListTc10)					, STD_OFF}	/* TC10設定 */
		#ifndef	g_regListPTP
		, {SWIC_REG_TBL(g_regListPTP)					, STD_OFF}	/* PTP設定 */
		#endif														/* g_regListPTP */
#if 0 /* 未対応 帯域制限 */
		, {SWIC_REG_TBL(g_regListBandwidthLimit)		, STD_OFF}	/* 帯域制限設定 */
#endif
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
		};
	Std_ReturnType	ret = E_OK;								/* 設定値無し */
	Std_ReturnType	err = E_OK;
	uint32			idx;
	uint32			val;

#if 0 /* For HND EthDbg */
/*koko*/EthDbg_LOGCHG(89u, ETHSWT_SWIC_IDX, 0u, 2u)
#endif

	for (idx=0U ; idx < SWIC_TBL_NUM(tbl) ; idx++) {		/* リードバック無 */
		err = swic_Reg_SetTbl(tbl[idx].tbl.tbl, tbl[idx].tbl.num, (tbl[idx].rst == STD_OFF) ? &val : NULL_PTR);
		if (err == E_OK)			{ continue; }
		ret = err;
		if (tbl[idx].rst == STD_OFF){ continue; }
		swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_INIT);			/* 中断してリセット */
		break;
	}
	swic_Reg_Inf.err = swic_Reg_ResetSwitchPortMode(ret);	/* 起動時は何もしない */
	if (swic_Reg_Inf.sts != ETHSWT_SWIC_STATE_INIT) {		/* ハードリセット / 低電圧 */
#if 0 /* For HND DTC */
		EthSwt_SWIC_DTC_RstNG();
#endif
		return;
	}
	for (idx=0U ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {/* リンク状態未取得 */
		swic_Reg_Mode[idx].lnk_err = E_NOT_OK;
		if (swic_Reg_Mode[idx].lnk_chk == STD_ON) {
			swic_Reg_Mode[idx].lnk_tim = swic_Reg_Inf.tim;
		}
	}
	swic_Reg_TimClr();

#if 0 /* For HND  DTC */
	EthSwt_SWIC_DTC_RstOK();
#endif
	swic_Reg_SetState(ETHSWT_SWIC_STATE_ACTIVE);
#if 0 /* For HND PMM(起動時間計測用) */
	EthSwt_SWIC_Org_PMM();
#endif
}

#if 0 /* For HND DeInit */
static Std_ReturnType swic_Reg_DeInit(void)
{
	static const struct swic_reg_tbl	tbl[]
	=	{ SWIC_REG_TBL(g_regListSeqP1PhyOff)
		, SWIC_REG_TBL(g_regListSeqP2PhyOff)
		, SWIC_REG_TBL(g_regListSeqP3PhyOff)
		, SWIC_REG_TBL(g_regListSeqP4PhyOff)
		, SWIC_REG_TBL(g_regListSeqP5PhyOff)
		, SWIC_REG_TBL(g_regListSeqP6PhyOff)
		, SWIC_REG_TBL(g_regListSeqP7PhyOff)
		, SWIC_REG_TBL(g_regListSeqP8PhyOff)
		, SWIC_REG_TBL(g_regListSeqP9PhyOff)
		, SWIC_REG_TBL(g_regListSeqRelayOff)	/* 余分な読み込みがあるのでチェックにできない */
		};
	Std_ReturnType		ret = E_OK;
	Std_ReturnType		err;
	uint32				i;
	uint32				val;
	for (i=0u ; i<SWIC_TBL_NUM(tbl) ; i++) {
		err = swic_Reg_SetTbl(tbl[i].tbl, tbl[i].num, &val);
		if (err != E_OK)	{ ret = err; }
	}
	swic_Reg_SetState(ETHSWT_SWIC_STATE_UNINIT);
	return ret;
}
#endif

static void swic_Reg_SetSwitchPortMode(const uint8 SwitchPortIdx)
{
	Eth_ModeType	PortMode;
	Std_ReturnType	err;
	LIB_DI();
	swic_Reg_Mode[SwitchPortIdx].req_mode = STD_OFF;	/* 下との間で割り込まれると同じ状態を通知する */
	PortMode = swic_Reg_Mode[SwitchPortIdx].mode_chg;	/* 問題なければ排他不要 */
	LIB_EI();
	if (swic_Reg_Mode[SwitchPortIdx].mode != PortMode) {
		switch (PortMode) {
		default:									/* default */
			break;
		case ETH_MODE_ACTIVE_WITH_WAKEUP_REQUEST:
			PortMode = ETH_MODE_ACTIVE;				/* [SWS_EthSwt_00439] */
			break;
		case ETH_MODE_ACTIVE:
			err = swic_Reg_SetSwitchPortModeACTIVE(SwitchPortIdx);
			if (err != E_OK) {
				swic_Reg_Mode[SwitchPortIdx].req_mode = STD_ON;	/* リトライ:1msタスクと同じ値を書くだけなので排他はいいかな */
				return;											/* ハードリセットかアクセスしていないのでレジスタ値に変化無 */
			}
			break;
		case ETH_MODE_DOWN:
			err = swic_Reg_SetSwitchPortModeDOWN(SwitchPortIdx);
			if (err != E_OK) {
				swic_Reg_Mode[SwitchPortIdx].req_mode = STD_ON;	/* リトライ:1msタスクと同じ値を書くだけなので排他はいいかな */
				return;
			}
			swic_Reg_LinkTimSet(SwitchPortIdx, ETHTRCV_LINK_STATE_DOWN, 1u); /* ETH_MODE_DOWNは反応がいいので確認 */
			break;
		}
	}
	LIB_DI();
	swic_Reg_Mode[SwitchPortIdx].mode = PortMode;
	swic_Reg_Mode[SwitchPortIdx].ind_mode = STD_ON;
	LIB_EI();
}
static void swic_Reg_GetLinkState(const uint8 SwitchPortIdx)
{
	Std_ReturnType			err;
	EthTrcv_LinkStateType	sts;
	err = swic_Reg_GetLink(SwitchPortIdx, &sts);
	if (err == E_OK) {	/* アクセス失敗時は更新しない(前回値) */
#if 0 /* For HND EthDbg */
/*koko*/EthDbg_LOGCHG(89u, ETHSWT_SWIC_IDX | 0x02u, SwitchPortIdx, sts)
#endif
		swic_Reg_Mode[SwitchPortIdx].lnk_sts = sts;
		swic_Reg_Mode[SwitchPortIdx].lnk_err = err;
		if (swic_Reg_Mode[SwitchPortIdx].lnk_chk == STD_OFF){ return; }
		if (sts != swic_Reg_Mode[SwitchPortIdx].lnk_exp)	{ return; }
	}					/* アクセス失敗は確認を止める */
	swic_Reg_Mode[SwitchPortIdx].lnk_chk = STD_OFF;
}

#if 0 /* For HND DTC */
#ifdef	SWIC_OPT_DTC				/* DTC有 */
static void swic_Reg_ClrDTC(void)
{
	uint8	idx;
	for (idx=0u ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		EthSwt_SWIC_Reg_UpdStreamFilterCounter(idx, NULL_PTR);
	}
}
#endif								/* SWIC_OPT_DTC */
#endif

static Std_ReturnType swic_Reg_CycLink(void)
{	/* リンク取得 */
	uint8	idx;
	for (idx=0u ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		swic_Reg_GetLinkState(idx);
	}
	return E_OK;
}
static void swic_Reg_CycLnkChk(void)
{	/* リンク高速確認 */
	uint8	idx;
	uint16	tmo;
	for (idx=0u ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		if (swic_Reg_Mode[idx].lnk_chk != STD_ON) { continue; }
		tmo = swic_Reg_Inf.tim - swic_Reg_Mode[idx].lnk_tim;
		if (tmo > swic_Reg_Mode[idx].lnk_tmo) {	/* タイムアウト */
			swic_Reg_Mode[idx].lnk_chk = STD_OFF;
		}
		swic_Reg_GetLinkState(idx);
	}
}

#if 0 /* 未対応 SWIC内部エラー検出 */
static Std_ReturnType swic_Reg_CycMon(void)
{
	struct swic_reg_mon;
	struct swic_reg_bit {						/* レジスタ設定[割り込み時の処理]で灰色のbitは無効ビット */
		const uint32				bit;		/* 対象ビット */
		const struct swic_reg_mon	*tbl;		/* 継続先 */
		const sint32				prc;		/* 処理番号 */
	};
	struct swic_reg_itm {
		const struct swic_reg_bit	*tbl;
		const uint32				num;
	};
	struct swic_reg_mon {
		const struct swic_reg_tbl	tbl;
		const struct swic_reg_itm	fnc;
		const uint8					log;
	};
	static const struct swic_reg_bit bit_unc2[]	/* [WD_CTRL 0x3A] Secondary Uncorrectable ECC Watch Dog Event */
	=	{ {SWIC_REG_BIT(6), NULL_PTR,  1}		/* bit6:①ハードリセット [EgrAct UCECC Event]     */
		, {SWIC_REG_BIT(4), NULL_PTR,  1}		/* bit4:①ハードリセット [Ingress UCECCErr Event] */
		};
	static const struct swic_reg_mon seq_unc2 = {SWIC_REG_TBL(g_regListSeqGetWatchdog2ndUncorectECC), SWIC_REG_TBL(bit_unc2), 0x3Au};
	static const struct swic_reg_bit bit_unc[]	/* [WD_CTRL 0x26] Uncorrectable ECC Watch Dog Event */
	=	{ {SWIC_REG_BIT(7), NULL_PTR,  1}		/* bit7:①ハードリセット [PktUCECCErrEvent]       */
		, {SWIC_REG_BIT(6), NULL_PTR,  1}		/* bit6:①ハードリセット [PvtUCECCErrEvent]       */
		, {SWIC_REG_BIT(4), NULL_PTR,  1}		/* bit4:①ハードリセット [TcamActUCECCErrEvent]   */
		, {SWIC_REG_BIT(3), NULL_PTR,  1}		/* bit3:①ハードリセット [QUCECCErrEvent]         */
		, {SWIC_REG_BIT(2), NULL_PTR,  1}		/* bit2:①ハードリセット [VtuUCECCErrEvent]       */
		, {SWIC_REG_BIT(1), NULL_PTR,  1}		/* bit1:①ハードリセット [AtuUCECCErrEvent]       */
		, {SWIC_REG_BIT(0), &seq_unc2, 0}		/* bit0:[WD_CTRL 0x3A]   [SecondaryUCECCErrEvent] */
		};
	static const struct swic_reg_bit bit_misc[]	/* [WD_CTRL 0x16] Miscellaneous Watch Dog Event */
	=	{ {SWIC_REG_BIT(7), NULL_PTR,  1}		/* bit7:①ハードリセット [ECCOut MisEven]        */
		, {SWIC_REG_BIT(6), NULL_PTR,  1}		/* bit6:①ハードリセット [ECCErr InjectMisEvent] */
		, {SWIC_REG_BIT(5), NULL_PTR,  1}		/* bit5:①ハードリセット [MBus ParityErrEvent]   */
		, {SWIC_REG_BIT(4), NULL_PTR,  1}		/* bit4:①ハードリセット [Reg ParityErr Event]   */
		, {SWIC_REG_BIT(1), NULL_PTR,  1}		/* bit1:①ハードリセット [PLLWDEvent]            */
		};
	static const struct swic_reg_bit bit_data[]	/* [WD_CTRL 0x12] Data Path Watch Dog Event */
	=	{ {SWIC_REG_BIT(5), NULL_PTR,  2}		/* bit5:②FIRソフトリセット [FBus CRCErr Event] */
		, {SWIC_REG_BIT(2), NULL_PTR,  2}		/* bit2:②FIRソフトリセット [QC WD Event]       */
		, {SWIC_REG_BIT(1), NULL_PTR,  2}		/* bit1:②FIRソフトリセット [EgressWD Event]    */
		};
	static const struct swic_reg_mon seq_unc  = {SWIC_REG_TBL(g_regListSeqGetWatchdogUncorectECC),    SWIC_REG_TBL(bit_unc),  0x26u};
	static const struct swic_reg_mon seq_misc = {SWIC_REG_TBL(g_regListSeqGetWatchdogMiscellaneous),  SWIC_REG_TBL(bit_misc), 0x16u};
	static const struct swic_reg_mon seq_data = {SWIC_REG_TBL(g_regListSeqGetWatchdogDatePath),       SWIC_REG_TBL(bit_data), 0x12u};
	static const struct swic_reg_bit bit_src[]	/* [WD_CTRL 0x00] Watch Dog Interrupt Source */
	=	{ {SWIC_REG_BIT(7), NULL_PTR,  1}		/* bit7:①ハードリセット [SMHaltWD Int]  */
		, {SWIC_REG_BIT(5), &seq_unc,  0}		/* bit5:[WD_CTRL 0x26]   [ParityWD Int]  */
		, {SWIC_REG_BIT(1), &seq_misc, 0}		/* bit1:[WD_CTRL 0x16]   [MiscWDInt]     */
		, {SWIC_REG_BIT(0), &seq_data, 0}		/* bit0:[WD_CTRL 0x12]   [DataPathWDInt] */
		};
	static const struct swic_reg_mon seq_src  = {SWIC_REG_TBL(g_regListSeqGetWatchdogIntSource),      SWIC_REG_TBL(bit_src), 0x00u};
	Std_ReturnType				err;
	const struct swic_reg_mon	*tbl = &seq_src;
	uint32						val = 0uL;
	err = EthSwt_SWIC_Org_INTN();
	if (err == E_OK)	{ return E_NOT_OK; }	/* 異常なし */
	do {
		const struct swic_reg_bit	*const bit = tbl->fnc.tbl;
		const uint32				num = tbl->fnc.num;
		uint32						i;
		uint32						msk;
		err = swic_Reg_SetTbl(tbl->tbl.tbl, tbl->tbl.num, &val);
		if (err != E_OK) { return E_NOT_OK; }	/* 周期が短いので異常は継続しとく */
		swic_Reg_Err.mon_seq = tbl->log;		/* ただのログ */
		swic_Reg_Err.mon_val = (uint8)val;
/*koko*/EthDbg_LOG(89u, ETHSWT_SWIC_IDX, 0xFCu, (uint32)(tbl->log) << 8 | (uint8)val)
		tbl = NULL_PTR;
		msk = 0uL;								/* 有効ビット算出 */
		for (i=0uL ; i<num ; i++) { msk |= bit[i].bit; }
		val &= msk;
		if (val == 0uL) { return E_NOT_OK; }	/* 有効なbit無:③処置不要：読んでも落ちないbitもあるので継続 */
		for (i=0uL ; i<num ; i++) {
			if (val != bit[i].bit) { continue; }/* 1bit一致のみ */
			if (bit[i].tbl != NULL_PTR) {
				tbl = bit[i].tbl;
				break;
			}
			switch (bit[i].prc) {
			default:	/* 無(カバレッジマスタ対応) */
			case 1:		/* ①FIRハードリセット */
				swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_SWIC);
				break;
			case 2:		/* ②FIRソフトリセット */
				swic_Reg_PortMacResetRequest();
				break;
			}
			return E_OK;
		}
	}	while (tbl != NULL_PTR);
	swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_SWIC);	/* 複数ビット1:①FIRハードリセット */
	return E_OK;
}
#endif

#if 0 /* 未対応 SWICリセット(異常)検出 */
#ifndef	g_regListSeqSetResetDetect				/* SWICリセット検出 */
static Std_ReturnType swic_Reg_CycRst(void)
{	/* 常にON(G4MHリソース)なのでEtherPMIC_ENの確認不要 */
	uint32		i;
	SWIC_TBL_CHK(SWIC_TBL_NUM(g_regListSeqGetResetDetect) != 16uL);
	for (i=0uL ; i<SWIC_TBL_NUM(g_regListSeqGetResetDetect) ; i+=4uL) {
		Std_ReturnType	err;
		err = swic_Reg_SetTbl(&g_regListSeqGetResetDetect[i], 4uL, NULL_PTR);
		if (err == E_OK)									{ return E_OK; }	/* 全部異常値でない場合リセット無 */
		if (swic_Reg_Inf.sts != ETHSWT_SWIC_STATE_ACTIVE)	{ return E_OK; }	/* CRC異常中断 */
	}
	EthSwt_SWIC_DTC_RstTgt();
	swic_Reg_ResetFact(ETHSWT_SWIC_REG_FACT_GPIO);
	swic_Reg_SetState(ETHSWT_SWIC_STATE_PMIC);
	return E_OK;
}
#endif											/* g_regListSeqSetResetDetect */
#endif

static Std_ReturnType swic_Reg_SwitchActiveTim(struct swic_Reg_Timer *const tim, Std_ReturnType(*const fnc)(void))
{
	if (tim->req != STD_ON) { return E_NOT_OK; }
	tim->req = STD_OFF;
	return fnc();
}
static Std_ReturnType swic_Reg_SwitchActiveMode(void)
{
	Std_ReturnType	ret = E_NOT_OK;
	uint8			idx;
	for (idx=0u ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		if (swic_Reg_Mode[idx].req_mode != STD_ON) { continue; }
		swic_Reg_SetSwitchPortMode(idx);
		ret = E_OK;						/* 繰り返す可能性があるので継続 */
	}
	return ret;
}

#if 0 /* For HND PhyReset */
static Std_ReturnType swic_Reg_SwitchActivePhyReset(void)
{
	uint8	idx;
	for (idx=0u ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		if (swic_Reg_Mode[idx].req_rst != STD_ON) { continue; }
		swic_Reg_Mode[idx].req_rst = STD_OFF;
		(void)swic_Reg_PortPhyReset(idx);
		return E_OK;
	}
	return E_NOT_OK;
}
#endif

#if 0 /* 未対応 IDS */
static Std_ReturnType swic_Reg_SwitchActiveIDS(void)
{
	Std_ReturnType	ret = E_NOT_OK;
	uint8			idx;
	for (idx=0u ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		if (swic_Reg_Mode[idx].ids.req != STD_ON) { continue; }
		swic_Reg_Mode[idx].ids.req = STD_OFF;
		EthSwt_SWIC_Reg_UpdStreamFilterCounter(idx, &swic_Reg_Mode[idx].FiltFrm);
		ret = E_OK;
	}
	return ret;
}
#endif

#if 0 /* 未対応 SQI */
static Std_ReturnType swic_Reg_SwitchActiveSQI(void)
{
	Std_ReturnType	ret = E_NOT_OK;
	uint8			idx;
	for (idx=0u ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		if (swic_Reg_Mode[idx].sqi.req != STD_ON) { continue; }
		swic_Reg_Mode[idx].sqi.req = STD_OFF;
		EthSwt_SWIC_Reg_UpdSQI(idx);
		ret = E_OK;
	}
	return ret;
}
#endif

static Std_ReturnType swic_Reg_SwitchActive(void)
{	/* EthSwt_SWIC_BackgroundTask()が0ms周期専用 */
	Std_ReturnType	err;
	Std_ReturnType	ret;	/* swic_Reg_SwitchActiveModeの戻り値 */
#if 0 /* 未対応 SWICリセット(異常)検出*/
	#ifndef	g_regListSeqSetResetDetect	/* SWICリセット検出 */
	err = swic_Reg_SwitchActiveTim(&swic_Reg_Inf.timrst, swic_Reg_CycRst);
	if (err == E_OK) { return E_OK; }
	#endif								/* g_regListSeqSetResetDetect */
#endif

#if 0 /* 未対応 SWIC内部エラー検出 */
	err = swic_Reg_SwitchActiveTim(&swic_Reg_Inf.timerr, swic_Reg_CycMon);
	if (err == E_OK) { return E_OK; }
#endif

#if 0 /* For HND DTC */
	#ifdef	SWIC_OPT_DTC				/* DTC有 */
	if (swic_Reg_ReqClrDTC == STD_ON) {	/* 周期より先に実施 */
		swic_Reg_ReqClrDTC = STD_OFF;
		swic_Reg_ClrDTC();
		return E_OK;
	}
	#endif								/* SWIC_OPT_DTC */
#endif

#if 0 /* For HND PhyReset */
	err = swic_Reg_SwitchActivePhyReset();
	if (err == E_OK) { return E_OK; }
#endif

	ret = swic_Reg_SwitchActiveMode();	/* 繰り返す可能性があるので継続 */
	err = swic_Reg_SwitchActiveTim(&swic_Reg_Inf.timlnk, swic_Reg_CycLink);
	if (err == E_OK) { return E_OK; }

#if 0 /* 未対応 IDS */
	err = swic_Reg_SwitchActiveIDS();	/* カウンタが溢れないよう先 */
	if (err == E_OK) { return E_OK; }
#endif

#if 0 /* 未対応 SQI */
	err = swic_Reg_SwitchActiveSQI();	/* 現在値を覗くだけなので後 */
	if (err == E_OK) { return E_OK; }
#endif
	return ret;							/* swic_Reg_SwitchActiveMode結果 */
}
static Std_ReturnType swic_Reg_SwitchActive1MS(void)
{	/* EthSwt_SWIC_BackgroundTask()が1ms周期対応 */
	uint32	i;
	for (i=0uL ; i<80uL ; i++) {	/* とりあえず8周(×10分岐)で定数ガード */
		const Std_ReturnType err = swic_Reg_SwitchActive();
		if (err != E_OK) { return err; }
		if (swic_Reg_Inf.sts != ETHSWT_SWIC_STATE_ACTIVE) { break; }
	}
	return E_OK;
}

#if 0 /* For HND DeInit */
static void swic_Reg_ProcDeInit(void)
{
	if (swic_Reg_ReqDeInit != STD_ON) { return; }
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_INIT:
	case ETHSWT_SWIC_STATE_ACTIVE:
		swic_Reg_ReqDeInit = STD_OFF;
		(void)swic_Reg_DeInit();		/* ETHSWT_STATE_UNINITに移行 */
		EthSwt_SWIC_Org_GPIO();
		break;
	case ETHSWT_SWIC_STATE_PMIC:
		swic_Reg_ReqDeInit = STD_OFF;	/* EtherPMICはOFF中 */
		swic_Reg_SetState(ETHSWT_SWIC_STATE_UNINIT);
		break;
	case ETHSWT_SWIC_STATE_RESET:		/* リセット後実施 */
		break;
	case ETHSWT_SWIC_STATE_UNINIT:
	default:	/* default */
		swic_Reg_ReqDeInit = STD_OFF;
		break;
	}
}
#endif

void EthSwt_SWIC_BackgroundTask(void)
{
	Std_ReturnType	err;
    Std_ReturnType  swicState;
    swicState = EthSwt_SWIC_Pwr_GetSWICState();
#if 0 /* For HND DeInit */
	swic_Reg_ProcDeInit();
#endif
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_ACTIVE:
#if 0 /* For HND EthDbg */
/*koko*/#ifndef	EthDbg_GetMibOFF					/* [dbg]コマンド中はアクセスを止める */
/*koko*/if (EthDbg_GetMibOFF() != E_OK) { break; }
/*koko*/#endif										/* EthDbg_GetMibOFF */
#endif
        if (swicState == STD_OFF)
        {
            swic_Reg_SetState(ETHSWT_SWIC_STATE_PMIC);
            return;
        }
		err = swic_Reg_SwitchActive1MS();
		if (err == E_OK)	{ break; }
		swic_Reg_CycLnkChk();						/* 何も処理してないとき実施 */
		break;
	case ETHSWT_SWIC_STATE_INIT:
        if (swicState == STD_OFF)
        {
            swic_Reg_SetState(ETHSWT_SWIC_STATE_PMIC);
            return;
        }
		swic_Reg_SwitchInit();
#if 0 /* For HND GSS(竹版PreRun解除のため) */
		EthSwt_SWIC_Org_Run();
#endif
		break;
	case ETHSWT_SWIC_STATE_RESET:
		EthSwt_SWIC_Org_Reset();
		swic_Reg_Inf.sts = ETHSWT_SWIC_STATE_INIT;	/* レジスタ設定 */
		break;
	case ETHSWT_SWIC_STATE_PMIC:
#if 0 /* For HND PMIC */
		#ifdef	SWIC_OPT_PMIC						/* Ether PMIC有 */
		err = swic_Reg_EtherPMIC();					/* EtherPMIC OFF確認 */
		if (err != E_OK)	{ break; }				/* T9はこの間に経過 */
		#endif										/* SWIC_OPT_PMIC */
		EthSwt_SWIC_Org_PmicON();					/* Ether PMIC無→EthSwt_SWIC_Org_Reset() */
#endif

#if 0 /* NCOS Soft */
		EthSwt_SWIC_Org_WaitSPI();					/* T8 Wait */
#endif
        if (swicState == STD_ON)
        {
            swic_Reg_Inf.sts = ETHSWT_SWIC_STATE_INIT;	/* レジスタ設定 */
            return;
        }
		
		break;
	case ETHSWT_SWIC_STATE_UNINIT:
	default:	/* default */
		break;
	}
}
#define	ETHSWT_STOP_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
