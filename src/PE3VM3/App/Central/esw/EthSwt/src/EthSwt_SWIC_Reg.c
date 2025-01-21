#include <Std_Types.h>
#include <LIB.h>
#include <EthSwt_SWIC.h>
#include <EthSwt_SWIC_initRegCommon.h>
#include <EthSwt_SWIC_initRegListPort.h>
#include <EthSwt_SWIC_initRegListVlan.h>
#include <EthSwt_SWIC_initRegListL2.h>
#include <EthSwt_SWIC_initRegListQos.h>
#include <EthSwt_SWIC_initRegListAcl.h>
#include <EthSwt_SWIC_initRegListArp.h>
#include <EthSwt_SWIC_initRegListTC10.h>
#include <EthSwt_SWIC_initRegListPTP.h>
#include <EthSwt_SWIC_initRegListBandwidthLimit.h>
#include <EthSwt_SWIC_initRegListSeqInitSeq.h>
#include <EthSwt_SWIC_initRegListSeqSetPortActDis.h>
#include <EthSwt_SWIC_initRegListSeqAclTbl.h>
#include <EthSwt_SWIC_initRegListSeqGetInterrupt.h>
#include <EthSwt_SWIC_initRegListSeqPhySwicOff.h>
#include <EthSwt_SWIC_initRegListSeqGetLink.h>
#include <EthSwt_SWIC_initRegListSeqPhyReset.h>
#include <EthSwt_SWIC_initRegListSeqMib.h>
#include <EthSwt_SWIC_initRegListSeqBaseT1.h>
#include <EthSwt_SWIC_initRegListGetResetDetect.h>
#include <EthSwt_SWIC_initRegListSeq100BTx.h>
#include <EthSwt_SWIC_Def.h>
#include <EthSwt_SWIC_Reg.h>
#include <EthSwt_SWIC_Spi.h>
#include <EthSwt_SWIC_Org.h>
#include <EthSwt_SWIC_Log.h>
#if 0  /* VM0_5msタスク配置用暫定 */
#include <app_VSM.h>
#include <chipcom.h>
#endif /* VM0_5msタスク配置用暫定 */

typedef enum										/* EthSwt_SWIC初期化状態 */
{	ETHSWT_SWIC_STATE_UNINIT = ETHSWT_STATE_UNINIT	/* 停止 -> ETHSWT_SWIC_STATE_INIT */
,	ETHSWT_SWIC_STATE_INIT   = ETHSWT_STATE_INIT	/* 初期化中 -> ETHSWT_SWIC_STATE_ACTIVE */
,	ETHSWT_SWIC_STATE_ACTIVE = ETHSWT_STATE_ACTIVE	/* 動作中 */
,	ETHSWT_SWIC_STATE_RESET							/* RESET中 -> ETHSWT_SWIC_STATE_ACTIVE */
,	ETHSWT_SWIC_STATE_PMIC							/* PMIC OFF検出 -> ETHSWT_SWIC_STATE_INIT */
}	EthSwt_SWIC_StateType;

#define	SWIC_REG_TBL(a)		{(a), SWIC_TBL_NUM(a)}	/* swic_reg_tbl設定用 */
#define	SWIC_REG_BIT(a)		(1uL << (a))			/* ビット */
#define	SWIC_REG_ADD_VAL(num, val)	((num) = (((~0uL) - (num)) >= (val)) ? (num) + (val) : ~0uL)
struct swic_reg_tbl {								/* レジスタテーブル */
	const swic_reg_data_t	*tbl;
	const uint32			num;
};

static void swic_Reg_CycIDS(void);
static void swic_Reg_CycMIB(void);
static void swic_Reg_CycLINK(void);
/* ★Debug_Start-------------------------------------------------------------- */
#ifdef EthswtDebugMode2
static void debugMib_init(void);
#endif /* EthswtDebugMode2 */
/* ★Debug_End---------------------------------------------------------------- */
#define ETHSWT_START_SEC_CONFIG_DATA_PREBUILD
#include <EthSwt_SWIC_MemMap.h>
static const Eth_ModeType	swic_Reg_InitPort[] = ETHSWT_SWIC_INITPORT; /* ポートモードテーブル */
static const uint8			swic_Reg_MibPort[]  = ETHSWT_SWIC_MIBPORT; /* MIB対象ポート */
static const uint8			swic_Reg_FastLinkChkPort[] = ETHSWT_SWIC_FASTLINKCHK;	/* 高速リンク確認ポート */
static const struct {
	sint32	tmo;						/* 周期(ms) */
	void	(*fnc)(void);				/* 周期処理:NULL_PTR禁止 */
	uint8	ini;						/* ACTIVE遷移時のswic_Reg_Inf.cyc[].req状態 */
}	swic_Reg_TimFnc[]					/* 優先度順 */
#if 0 /* VM0_5msタスク配置用暫定 */
=	{ {100, swic_Reg_CycLINK, STD_ON}	/* リンク状態 */
	, {100, swic_Reg_CycMIB,  STD_ON}	/* MIB取得 */
	, {100, swic_Reg_CycIDS,  STD_OFF}	/* IDS取得 */
#else /* VM0_5msタスク配置用暫定 */
=	{ {20, swic_Reg_CycLINK, STD_ON}	/* リンク状態 */
	, {20, swic_Reg_CycMIB,  STD_ON}	/* MIB取得 */
	, {20, swic_Reg_CycIDS,  STD_OFF}	/* IDS取得 */
#endif /* VM0_5msタスク配置用暫定 */
};
#define ETHSWT_STOP_SEC_CONFIG_DATA_PREBUILD
#include <EthSwt_SWIC_MemMap.h>

#define	ETHSWT_START_SEC_VAR_CLEARED
#include <EthSwt_SWIC_MemMap.h>
static struct {									/* 初期化情報 */
	volatile EthSwt_SWIC_StateType	sts;		/* 初期化状態 */
	volatile Std_ReturnType			err;		/* 初期化異常有無 */
	volatile uint16					tim;		/* タイマ:レジスタアクセスを抑えるため周期タスクでカウント */
	uint8							CycRstReq;	/* SWIC内部異常検出実行要求 */
	sint32							CycRstTim;	/* SWIC内部異常検出タイマカウンタ */
	uint8							CycMonReq;	/* SWIC内部エラー検出実行要求 */
	sint32							CycMonTim;	/* SWIC内部異常検出タイマカウンタ */
	struct {									/* 周期待ち */
		sint32						tim;		/* タイマカウンタ */
		uint8						req;		/* 処理要求 */
	}								cyc[SWIC_TBL_NUM(swic_Reg_TimFnc)];
}	swic_Reg_Inf;
static struct {									/* EthSwt_SetSwitchPortMode */
	Eth_ModeType					mode;
	volatile Eth_ModeType			mode_chg;	/* アクセス順不動なのでvolatile */
	volatile uint8					req_mode;	/* ↑ */
	volatile uint8					ind_mode;	/* ↑ */
	volatile Std_ReturnType			lnk_err;	/* アクセス順不動なのでvolatile */
	volatile EthTrcv_LinkStateType	lnk_sts;	/* ↑ */
	volatile uint8					req_clr;
	uint8							lnk_chk;
	EthTrcv_LinkStateType			lnk_exp;
	uint16							lnk_tim;
	uint16							lnk_tmo;
	EthSwt_DiscardInfoType			dinf;
	uint32							TcamFiltFrm;
	uint32							StreamFiltFrm;	/* Flow Meter Filtered Counter */
}	swic_Reg_Mode[SWIC_TBL_NUM(swic_Reg_InitPort)];	/* 0～8: 0=Port5,1=Port7,2=Port8 */
#define	ETHSWT_STOP_SEC_VAR_CLEARED
#include <EthSwt_SWIC_MemMap.h>

/* ★Debug_Start-------------------------------------------------------------- */
#ifdef EthswtDebugMode2
static struct {
	uint32 mibinfo[65]; /* 全MIB情報分 */
}debug_MIB[9];          /* 9ポート分 */
#endif /* EthswtDebugMode2 */
/* ★Debug_End---------------------------------------------------------------- */
#define	ETHSWT_START_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
/* ★Debug_Start-------------------------------------------------------------- */
#ifdef EthswtDebugMode2
static void debugMib_init(void){
    uint8 i;
    uint8 j;

	for(i=0;i<9;i++){
	    for(j=0;j<65;j++){
	        debug_MIB[i].mibinfo[j] = (uint32)0;
	    }
	}
}
#endif /* EthswtDebugMode2 */
/* ★Debug_End---------------------------------------------------------------- */
static void swic_Reg_InitLink(void)
{	/* ETHSWT_SWIC_STATE_INITになる状態に遷移するときに呼び出す */
	unsigned	idx;
	for (idx=0U ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) { swic_Reg_Mode[idx].lnk_err = E_NOT_OK; }
}
static void swic_Reg_SetState(const EthSwt_SWIC_StateType sts)
{
	swic_Reg_Inf.sts = sts;
	switch (sts) {
	case ETHSWT_SWIC_STATE_ACTIVE:
#if 0    /* VN-HILSでは、SWICのログ記録を行わない想定のため、実装しない。シス検以降で使用するかは検討が必要。 */
		EthSwt_SWIC_Log_Active();
#endif    /* VN-HILSでは、SWICのログ記録を行わない想定のため、実装しない。シス検以降で使用するかは検討が必要。 */
		break;
	case ETHSWT_SWIC_STATE_PMIC:
	case ETHSWT_SWIC_STATE_RESET:
		swic_Reg_InitLink();
		break;
	case ETHSWT_SWIC_STATE_UNINIT:
	case ETHSWT_SWIC_STATE_INIT:
	default:	/* default */
		break;
	}
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
#if 0  /* VM0_5msタスク配置用暫定 */
static void swic_Reg_CheckSleepNG(void)
{
	uint32		i;
	for (i=3u ; i<SWIC_TBL_NUM(swic_Reg_Mode) ; i++) { /* 自ポートは常にACTIVEのため確認対象外とする */
		if (swic_Reg_Mode[i].mode == ETH_MODE_ACTIVE) {
			PutCnSleepNG_Eth(K_VSM_SLEEPNG);
			return;
		}
	}
	PutCnSleepNG_Eth(K_VSM_SLEEPOK);
	return;
}
#endif /* VM0_5msタスク配置用暫定 */
void EthSwt_SWIC_Reg_Init(void)
{	/* 初期化タスク */
	uint8		i;
	EthSwt_SWIC_Spi_Init();
	EthSwt_SWIC_Org_Init();
#if 0    /* VN-HILSでは、SWICのログ記録を行わない想定のため、実装しない。シス検以降で使用するかは検討が必要。 */
	EthSwt_SWIC_Log_Wakeup();
#endif    /* VN-HILSでは、SWICのログ記録を行わない想定のため、実装しない。シス検以降で使用するかは検討が必要。 */
	swic_Reg_Inf.sts	= ETHSWT_SWIC_STATE_UNINIT;	/* 確認用 */
	swic_Reg_Inf.err	= E_OK;
	swic_Reg_Inf.tim	= 0u;
	swic_Reg_Inf.CycRstReq = STD_OFF;
	swic_Reg_Inf.CycRstTim = 0;
	swic_Reg_Inf.CycMonReq = STD_OFF;
	swic_Reg_Inf.CycMonTim = 0;
	for (i=0 ; i<SWIC_TBL_NUM(swic_Reg_Inf.cyc) ; i++) {
		swic_Reg_Inf.cyc[i].tim = 0;
		swic_Reg_Inf.cyc[i].req = swic_Reg_TimFnc[i].ini;
	}
	for (i=0U ; i<SWIC_TBL_NUM(swic_Reg_Mode) ; i++) {
		swic_Reg_Mode[i].mode					= swic_Reg_InitPort[i];
		swic_Reg_Mode[i].mode_chg				= swic_Reg_InitPort[i];
		swic_Reg_Mode[i].req_mode				= STD_OFF;
		swic_Reg_Mode[i].ind_mode				= STD_OFF;
		swic_Reg_Mode[i].lnk_err				= E_NOT_OK;
		swic_Reg_Mode[i].lnk_sts				= ETHTRCV_LINK_STATE_DOWN;
		swic_Reg_Mode[i].req_clr				= STD_OFF;
		swic_Reg_Mode[i].lnk_chk				= STD_OFF;
		swic_Reg_Mode[i].lnk_exp				= ETHTRCV_LINK_STATE_DOWN;
		swic_Reg_Mode[i].lnk_tim				= 0u;
		swic_Reg_Mode[i].lnk_tmo				= 0u;
		swic_Reg_Mode[i].dinf.Factor			= 0u;
		swic_Reg_Mode[i].dinf.IngressCount		= 0u;
		swic_Reg_Mode[i].dinf.EgressCount		= 0u;
		swic_Reg_Mode[i].TcamFiltFrm			= 0u;
		swic_Reg_Mode[i].StreamFiltFrm			= 0u;
		if (swic_Reg_FastLinkChkPort[i] == STD_ON) {
			swic_Reg_LinkTimSet(i, ETHTRCV_LINK_STATE_ACTIVE, SWIC_REG_LINK);
		}
	}
	swic_Reg_SetState(ETHSWT_SWIC_STATE_PMIC);
/* ★Debug_Start-------------------------------------------------------------- */
#ifdef EthswtDebugMode2
	debugMib_init();
#endif /* EthswtDebugMode2 */
/* ★Debug_End---------------------------------------------------------------- */
}

static void swic_Reg_TimUpd(sint32 *tim, sint32 tmo, uint8 *req)
{
	if (tmo > 0) {
		sint32	cnt = *tim + SWIC_ETH_PERIOD;
		if (cnt >= tmo) {
			cnt -= tmo;
			*req = STD_ON;		/* 定期動作:遅れても複数回処理しない */
		}
		*tim = cnt;
	}
	return;
}

void EthSwt_SWIC_MainFunction1MS(void)
{	/* 1ms周期タスク */
	uint32	i;
	swic_Reg_Inf.tim = swic_Reg_Inf.tim + (uint16)SWIC_ETH_PERIOD;
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_ACTIVE:
#if 0    /* VN-HILSとしては不要なため無効化 */
		swic_Reg_TimUpd(&swic_Reg_Inf.CycRstTim, SWIC_REG_TIMERR, &swic_Reg_Inf.CycRstReq);
#endif    /* VN-HILSとしては不要なため無効化 */
		swic_Reg_TimUpd(&swic_Reg_Inf.CycMonTim, SWIC_REG_TIMERR, &swic_Reg_Inf.CycMonReq);
		for (i=0 ; i<SWIC_TBL_NUM(swic_Reg_Inf.cyc) ; i++) {
			swic_Reg_TimUpd(&swic_Reg_Inf.cyc[i].tim, swic_Reg_TimFnc[i].tmo, &swic_Reg_Inf.cyc[i].req);
		}
		break;
	case ETHSWT_SWIC_STATE_PMIC:
	case ETHSWT_SWIC_STATE_RESET:
	case ETHSWT_SWIC_STATE_UNINIT:
	case ETHSWT_SWIC_STATE_INIT:
	default:	/* default */
		break;
	}
}
void EthSwt_SWIC_MainFunction5MS(void)
{	/* Ethの周期タスク */
#if 0  /* VM0_5msタスク配置用暫定 */
	uint8 transreq_mcu_info[MCUINFO_DATASIZE];
	uint8 idx;
	uint8 port;
	uint8 port_tbl[SWIC_PORT_NUM] =
	{
		SWIC_PORT1,
		SWIC_PORT2,
		SWIC_PORT5,
		SWIC_PORT6,
		SWIC_PORT7,
		SWIC_PORT8
	};
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_ACTIVE:
		swic_Reg_CheckSleepNG();
		break;
	case ETHSWT_SWIC_STATE_PMIC:
	case ETHSWT_SWIC_STATE_RESET:
	case ETHSWT_SWIC_STATE_UNINIT:
	case ETHSWT_SWIC_STATE_INIT:
	default:	/* default */
		PutCnSleepNG_Eth(K_VSM_SLEEPOK);
		break;
	}
#endif /* VM0_5msタスク配置用暫定 */
	EthSwt_SWIC_Org_MainFunction();
#if 0  /* VM0_5msタスク配置用暫定 */
	transreq_mcu_info[SWIC_STS_DATAPOS] = swic_Reg_Inf.sts;
	for (port = 0; port < SWIC_PORT_NUM; port++)	/* ポート毎に情報を格納 */
	{
		idx = port * MCUINFO_PORT_DATASIZE;	/* ポート毎の格納開始位置を決定 */
		transreq_mcu_info[idx +  PORT_MODE_DATAPOS1] = (uint8)(swic_Reg_Mode[port_tbl[port]].mode & TRANSREQ_1BYTE_DATA_MASK); 
		transreq_mcu_info[idx +  PORT_MODE_DATAPOS2] = (uint8)((swic_Reg_Mode[port_tbl[port]].mode >> (TRANSREQ_SHIFT_1BYTE)) & TRANSREQ_1BYTE_DATA_MASK);
		transreq_mcu_info[idx +  PORT_MODE_DATAPOS3] = (uint8)((swic_Reg_Mode[port_tbl[port]].mode >> (TRANSREQ_SHIFT_2BYTE)) & TRANSREQ_1BYTE_DATA_MASK);
		transreq_mcu_info[idx +  PORT_MODE_DATAPOS4] = (uint8)((swic_Reg_Mode[port_tbl[port]].mode >> (TRANSREQ_SHIFT_3BYTE)) & TRANSREQ_1BYTE_DATA_MASK);
		transreq_mcu_info[idx + IND_MODE_DATAPOS] = swic_Reg_Mode[port_tbl[port]].ind_mode;
		transreq_mcu_info[idx + LNK_STS_DATAPOS] = swic_Reg_Mode[port_tbl[port]].lnk_sts;
		transreq_mcu_info[idx + LNK_ERR_DATAPOS] = swic_Reg_Mode[port_tbl[port]].lnk_err;
		if(swic_Reg_Mode[port_tbl[port]].ind_mode == STD_ON){
			swic_Reg_Mode[port_tbl[port]].ind_mode = STD_OFF;			/* ポート設定の完了通知は1度のみ行う(ON格納後OFFにする) */
		}
	}
	(void)ChipCom_Transmit(CHIPCOM_DATAID_ETHERSWT_MCUINFO,(uint16)MCUINFO_DATASIZE, transreq_mcu_info);/* ChipComにポート状態、リンク状態、EthSWT内部状態を通知 */
#endif /* VM0_5msタスク配置用暫定 */
}
#if 0  /* VM0_5msタスク配置用暫定 */
void EthSwt_SWIC_Port1ModeReq(const uint16 transreq_len, const uint8* const transreq_data)
{
	Eth_ModeType port_mode = 0u;

	if ((transreq_data != NULL_PTR) && (transreq_len == (uint16)PORTMODE_DATASIZE))	/* NULLチェック */
	{   /* ChipComから受信したポートモードを格納 */   
		port_mode = (((Eth_ModeType)transreq_data[3]) << TRANSREQ_SHIFT_3BYTE);     
		port_mode |=  (((Eth_ModeType)transreq_data[2]) << TRANSREQ_SHIFT_2BYTE);
		port_mode |=  (((Eth_ModeType)transreq_data[1]) << TRANSREQ_SHIFT_1BYTE);
		port_mode |=  (((Eth_ModeType)transreq_data[0]) & TRANSREQ_1BYTE_DATA_MASK);
		swic_Reg_Mode[SWIC_PORT1].mode_chg = (Eth_ModeType)port_mode;
		swic_Reg_Mode[SWIC_PORT1].req_mode = (uint8)STD_ON;	/* 処理前に複数呼ばれた場合は最新が有効 */
	}
	return;
}
void EthSwt_SWIC_Port2ModeReq(const uint16 transreq_len, const uint8* const transreq_data)
{
	Eth_ModeType port_mode = 0u;

	if ((transreq_data != NULL_PTR) && (transreq_len == (uint16)PORTMODE_DATASIZE))	/* NULLチェック */
	{	/* ChipComから受信したポートモードを格納 */
		port_mode = (((Eth_ModeType)transreq_data[3]) << TRANSREQ_SHIFT_3BYTE);     
		port_mode |=  (((Eth_ModeType)transreq_data[2]) << TRANSREQ_SHIFT_2BYTE);
		port_mode |=  (((Eth_ModeType)transreq_data[1]) << TRANSREQ_SHIFT_1BYTE);
		port_mode |=  (((Eth_ModeType)transreq_data[0]) & TRANSREQ_1BYTE_DATA_MASK);
		swic_Reg_Mode[SWIC_PORT2].mode_chg = (Eth_ModeType)port_mode;
		swic_Reg_Mode[SWIC_PORT2].req_mode = (uint8)STD_ON;	/* 処理前に複数呼ばれた場合は最新が有効 */
	}
	return;
}
void EthSwt_SWIC_Port5ModeReq(const uint16 transreq_len, const uint8* const transreq_data)
{
	Eth_ModeType port_mode = 0u;

	if ((transreq_data != NULL_PTR) && (transreq_len == (uint16)PORTMODE_DATASIZE))	/* NULLチェック */
	{	/* ChipComから受信したポートモードを格納 */
		port_mode = (((Eth_ModeType)transreq_data[3]) << TRANSREQ_SHIFT_3BYTE);     
		port_mode |=  (((Eth_ModeType)transreq_data[2]) << TRANSREQ_SHIFT_2BYTE);
		port_mode |=  (((Eth_ModeType)transreq_data[1]) << TRANSREQ_SHIFT_1BYTE);
		port_mode |=  (((Eth_ModeType)transreq_data[0]) & TRANSREQ_1BYTE_DATA_MASK);
		swic_Reg_Mode[SWIC_PORT5].mode_chg = (Eth_ModeType)port_mode;
		swic_Reg_Mode[SWIC_PORT5].req_mode = (uint8)STD_ON;	/* 処理前に複数呼ばれた場合は最新が有効 */
	}
	return;
}
void EthSwt_SWIC_Port6ModeReq(const uint16 transreq_len, const uint8* const transreq_data)
{
	Eth_ModeType port_mode = 0u;

	if ((transreq_data != NULL_PTR) && (transreq_len == (uint16)PORTMODE_DATASIZE))	/* NULLチェック */
	{	/* ChipComから受信したポートモードを格納 */
		port_mode = (((Eth_ModeType)transreq_data[3]) << TRANSREQ_SHIFT_3BYTE);     
		port_mode |=  (((Eth_ModeType)transreq_data[2]) << TRANSREQ_SHIFT_2BYTE);
		port_mode |=  (((Eth_ModeType)transreq_data[1]) << TRANSREQ_SHIFT_1BYTE);
		port_mode |=  (((Eth_ModeType)transreq_data[0]) & TRANSREQ_1BYTE_DATA_MASK);
		swic_Reg_Mode[SWIC_PORT6].mode_chg = (Eth_ModeType)port_mode;
		swic_Reg_Mode[SWIC_PORT6].req_mode = (uint8)STD_ON;	/* 処理前に複数呼ばれた場合は最新が有効 */
	}
	return;
}
void EthSwt_SWIC_Port7ModeReq(const uint16 transreq_len, const uint8* const transreq_data)
{
	Eth_ModeType port_mode = 0u;

	if ((transreq_data != NULL_PTR) && (transreq_len == (uint16)PORTMODE_DATASIZE))	/* NULLチェック */
	{	/* ChipComから受信したポートモードを格納 */
		port_mode = (((Eth_ModeType)transreq_data[3]) << TRANSREQ_SHIFT_3BYTE);     
		port_mode |=  (((Eth_ModeType)transreq_data[2]) << TRANSREQ_SHIFT_2BYTE);
		port_mode |=  (((Eth_ModeType)transreq_data[1]) << TRANSREQ_SHIFT_1BYTE);
		port_mode |=  (((Eth_ModeType)transreq_data[0]) & TRANSREQ_1BYTE_DATA_MASK);
		swic_Reg_Mode[SWIC_PORT7].mode_chg = (Eth_ModeType)port_mode;
		swic_Reg_Mode[SWIC_PORT7].req_mode = (uint8)STD_ON;	/* 処理前に複数呼ばれた場合は最新が有効 */
	}
	return;
}
void EthSwt_SWIC_Port8ModeReq(const uint16 transreq_len, const uint8* const transreq_data)
{
	Eth_ModeType port_mode = 0u;

	if ((transreq_data != NULL_PTR) && (transreq_len == (uint16)PORTMODE_DATASIZE))	/* NULLチェック */
	{	/* ChipComから受信したポートモードを格納 */
		port_mode = (((Eth_ModeType)transreq_data[3]) << TRANSREQ_SHIFT_3BYTE);     
		port_mode |=  (((Eth_ModeType)transreq_data[2]) << TRANSREQ_SHIFT_2BYTE);
		port_mode |=  (((Eth_ModeType)transreq_data[1]) << TRANSREQ_SHIFT_1BYTE);
		port_mode |=  (((Eth_ModeType)transreq_data[0]) & TRANSREQ_1BYTE_DATA_MASK);
		swic_Reg_Mode[SWIC_PORT8].mode_chg = (Eth_ModeType)port_mode;
		swic_Reg_Mode[SWIC_PORT8].req_mode = (uint8)STD_ON;	/* 処理前に複数呼ばれた場合は最新が有効 */
	}
	return;
}
#endif /* VM0_5msタスク配置用暫定 */
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
#if 0    /* VN-HILSとしては不要なため無効化 */
Std_ReturnType EthSwt_SWIC_Reg_GetLinkState(const uint8 SwitchPortIdx, EthTrcv_LinkStateType* const LinkStatePtr)
{	/* 1msタスク */
	Std_ReturnType ret;
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_ACTIVE:
		if (SwitchPortIdx >= SWIC_TBL_NUM(swic_Reg_Mode))	{ return E_NOT_OK; }
		if (LinkStatePtr == NULL_PTR)						{ return E_NOT_OK; }
		*LinkStatePtr = swic_Reg_Mode[SwitchPortIdx].lnk_sts;
		ret = swic_Reg_Mode[SwitchPortIdx].lnk_err;
		break;
	case ETHSWT_SWIC_STATE_UNINIT:
	case ETHSWT_SWIC_STATE_PMIC:
	case ETHSWT_SWIC_STATE_RESET:
	case ETHSWT_SWIC_STATE_INIT:
	default:	/* default */
		ret = E_NOT_OK;
		break;
	}
	return ret;
}
static void swic_Reg_ClearDInf(const uint8 SwitchPortIdx)
{
	swic_Reg_Mode[SwitchPortIdx].dinf.Factor= 0u;
	swic_Reg_Mode[SwitchPortIdx].dinf.IngressCount	= 0u;
	swic_Reg_Mode[SwitchPortIdx].dinf.EgressCount		= 0u;
}
Std_ReturnType EthSwt_SWIC_Reg_GetFrameInfo(const uint8 SwitchPortIdx, EthSwt_DiscardInfoType *const FrameInfoPtr)
{	/* 5msタスク */
	Std_ReturnType ret;
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_ACTIVE:
		if (SwitchPortIdx >= SWIC_TBL_NUM(swic_Reg_Mode))	{ return E_NOT_OK; }
		if (FrameInfoPtr == NULL_PTR)						{ return E_NOT_OK; }
		FrameInfoPtr->Factor= swic_Reg_Mode[SwitchPortIdx].dinf.Factor;
		FrameInfoPtr->IngressCount	= swic_Reg_Mode[SwitchPortIdx].dinf.IngressCount;
		FrameInfoPtr->EgressCount		= swic_Reg_Mode[SwitchPortIdx].dinf.EgressCount;
		swic_Reg_ClearDInf(SwitchPortIdx);	/* 異なるタスクから呼ばれる場合排他 */
		ret = E_OK;
		break;
	case ETHSWT_SWIC_STATE_UNINIT:
	case ETHSWT_SWIC_STATE_PMIC:
	case ETHSWT_SWIC_STATE_RESET:
	case ETHSWT_SWIC_STATE_INIT:
	default:	/* default */
		ret = E_NOT_OK;
		break;
	}
	return ret;
}
Std_ReturnType EthSwt_SWIC_Reg_ClearFrameInfo(const uint8 SwitchPortIdx)
{	/* 5msタスク */
	Std_ReturnType ret;
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_ACTIVE:
		if (SwitchPortIdx >= SWIC_TBL_NUM(swic_Reg_Mode))	{ return E_NOT_OK; }
		swic_Reg_ClearDInf(SwitchPortIdx);
		swic_Reg_Mode[SwitchPortIdx].req_clr = STD_ON;
		ret = E_OK;
		break;
	case ETHSWT_SWIC_STATE_UNINIT:
	case ETHSWT_SWIC_STATE_PMIC:
	case ETHSWT_SWIC_STATE_RESET:
	case ETHSWT_SWIC_STATE_INIT:
	default:	/* default */
		ret = E_NOT_OK;
		break;
	}
	return ret;
}
Std_ReturnType EthSwt_SWIC_Reg_GetIDS_TcamInfo(const uint8 SwitchPortIdx, uint32 *const IDSInfo)
{	/* 5msタスク */
	Std_ReturnType ret;
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_ACTIVE:
		if (SwitchPortIdx >= SWIC_TBL_NUM(swic_Reg_Mode))	{ return E_NOT_OK; }
		if (IDSInfo == NULL_PTR)							{ return E_NOT_OK; }
		*IDSInfo = swic_Reg_Mode[SwitchPortIdx].TcamFiltFrm;
		swic_Reg_Mode[SwitchPortIdx].TcamFiltFrm = 0uL;
		ret = E_OK;
		break;
	case ETHSWT_SWIC_STATE_UNINIT:
	case ETHSWT_SWIC_STATE_PMIC:
	case ETHSWT_SWIC_STATE_RESET:
	case ETHSWT_SWIC_STATE_INIT:
	default:	/* default */
		ret = E_NOT_OK;
		break;
	}
	return ret;
}
Std_ReturnType EthSwt_SWIC_Reg_GetIDS_FiltFrmInfo(const uint8 SwitchPortIdx, uint32 *const IDSInfo)
{	/* 5msタスク */
	Std_ReturnType ret;
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_ACTIVE:
		if (SwitchPortIdx >= SWIC_TBL_NUM(swic_Reg_Mode))	{ return E_NOT_OK; }
		if (IDSInfo == NULL_PTR)							{ return E_NOT_OK; }
		*IDSInfo = swic_Reg_Mode[SwitchPortIdx].StreamFiltFrm;
		swic_Reg_Mode[SwitchPortIdx].StreamFiltFrm = 0uL;
		ret = E_OK;
		break;
	case ETHSWT_SWIC_STATE_UNINIT:
	case ETHSWT_SWIC_STATE_PMIC:
	case ETHSWT_SWIC_STATE_RESET:
	case ETHSWT_SWIC_STATE_INIT:
	default:	/* default */
		ret = E_NOT_OK;
		break;
	}
	return ret;
}
EthSwt_StateType EthSwt_SWIC_GetState(void)
{	/* 1msタスク */
	EthSwt_StateType	ret;
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_UNINIT:
		ret = ETHSWT_STATE_UNINIT;
		break;
	case ETHSWT_SWIC_STATE_ACTIVE:
		ret = ETHSWT_STATE_ACTIVE;
		break;
	case ETHSWT_SWIC_STATE_INIT:
	case ETHSWT_SWIC_STATE_RESET:
	default:	/* default */
		ret = ETHSWT_STATE_INIT;
		break;
	}
	return ret;
}
#endif    /* VN-HILSとしては不要なため無効化 */
static void swic_Reg_Reset(const uint32 fact)
{
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_UNINIT:	/* 停止中は遷移しない */
	case ETHSWT_SWIC_STATE_PMIC:	/* Ether PMICが優先 */
		break;
	case ETHSWT_SWIC_STATE_RESET:
		swic_Reg_SetState(ETHSWT_SWIC_STATE_RESET); /* 一度リセット状態になった場合、SWICハードリセットするまではログは残さない */
		break;
	case ETHSWT_SWIC_STATE_ACTIVE:
	case ETHSWT_SWIC_STATE_INIT:
	default:
#if 0    /* VN-HILSでは、SWICのログ記録を行わない想定のため、実装しない。シス検以降で使用するかは検討が必要。*/
		EthSwt_SWIC_Log_Reset(fact);
#endif    /* VN-HILSでは、SWICのログ記録を行わない想定のため、実装しない。シス検以降で使用するかは検討が必要。*/
		swic_Reg_SetState(ETHSWT_SWIC_STATE_RESET);
		break;
	}
}
static Std_ReturnType swic_Reg_SetTblWriteOFF(const Std_ReturnType ret, const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx)
{
	Std_ReturnType	err;
	uint32			i;
	uint8			spi_err;
	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		err = EthSwt_SWIC_Spi_Write(tbl, cnt, idx);
		if (err == E_OK)	{ return ret; }
	}
	spi_err = EthSwt_SWIC_Spi_GetSpiRegErr();
	swic_Reg_Reset((spi_err == STD_OFF) ? ETHSWT_SWIC_REG_FACT_CRC : ETHSWT_SWIC_REG_FACT_SPI);	/* リセット */
	return E_NOT_OK;
}
static Std_ReturnType swic_Reg_SetTblReadOFF(const Std_ReturnType ret, const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx, uint32 * const dat)
{
	Std_ReturnType	err;
	uint16			val = 0u;
	uint32			i;
	uint8			spi_err;
	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		err = EthSwt_SWIC_Spi_Read(tbl, cnt, idx, &val);
		if (err == E_OK) {
			if (dat != NULL_PTR) {	/* データ取得 */
				*dat = (*dat << 16) | ((uint32)val & (uint32)tbl[idx].mask);
				return ret;
			}
			if (((val ^ tbl[idx].value) & tbl[idx].mask) == 0u)	{ return ret; }	/* 一致 */
			return E_NOT_OK;
		}
	}
	spi_err = EthSwt_SWIC_Spi_GetSpiRegErr();
	swic_Reg_Reset((spi_err == STD_OFF) ? ETHSWT_SWIC_REG_FACT_CRC : ETHSWT_SWIC_REG_FACT_SPI);	/* リセット */
	return E_NOT_OK;
}
static Std_ReturnType swic_Reg_SetTblReadON(const Std_ReturnType ret, const swic_reg_data_t tbl[], const uint32 idx, const uint16 mask, const uint16 value)
{
	Std_ReturnType	err;
	uint16			val = 0u;
	uint32			i;
	uint16			cnt = 0u;
	uint32			reset_fact;
	const uint16	tim = swic_Reg_Inf.tim;
	for (i=0uL ; i<SWIC_REG_WAIT_L ; i++) {
		uint16	tmo;
		err = EthSwt_SWIC_Spi_ReadSPI(tbl, idx, &val);
		if (err == E_OK) {
			if (((val ^ value) & mask) == 0u) { return ret; }
		} else {
			cnt = cnt + (uint16)1u;
			if (cnt >= INIT_SEQ_RETRY_CNT) { break; }
		}
		tmo = swic_Reg_Inf.tim - tim;
		if (tmo > SWIC_REG_WAIT) { break; }
	}
	reset_fact = EthSwt_SWIC_Spi_GetSpiRegErr();
	reset_fact = ((reset_fact == STD_OFF) ? ETHSWT_SWIC_REG_FACT_CRC : ETHSWT_SWIC_REG_FACT_SPI);	/* リセット */
	swic_Reg_Reset((cnt >= INIT_SEQ_RETRY_CNT) ? reset_fact: ETHSWT_SWIC_REG_FACT_BSY);	/* リセット */
	return E_NOT_OK;
}
static Std_ReturnType swic_Reg_SetTblWriteMask(const Std_ReturnType ret, const swic_reg_data_t tbl[], const uint32 idx, uint16 val)
{
	Std_ReturnType	err;
	uint32			i;
	uint8			spi_err;
	val ^= val & tbl[idx].mask;
	val |= tbl[idx].value & tbl[idx].mask;
	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		err = EthSwt_SWIC_Spi_WriteSPI(tbl, idx, val);
		if (err == E_OK)	{ return ret; }
	}
	spi_err = EthSwt_SWIC_Spi_GetSpiRegErr();
	swic_Reg_Reset((spi_err == STD_OFF) ? ETHSWT_SWIC_REG_FACT_CRC : ETHSWT_SWIC_REG_FACT_SPI);	/* リセット */
	return E_NOT_OK;
}
static Std_ReturnType swic_Reg_SetTblReadMask(const Std_ReturnType ret, const swic_reg_data_t tbl[], const uint32 idx, uint16 *const val)
{
	Std_ReturnType	err;
	uint32			i;
	uint8			spi_err;
	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		err = EthSwt_SWIC_Spi_ReadSPI(tbl, idx, val);
		if (err == E_OK)	{ return ret; }
	}
	spi_err = EthSwt_SWIC_Spi_GetSpiRegErr();
	swic_Reg_Reset((spi_err == STD_OFF) ? ETHSWT_SWIC_REG_FACT_CRC : ETHSWT_SWIC_REG_FACT_SPI);	/* リセット */
	return E_NOT_OK;
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
		switch (swic_Reg_Inf.sts) {
		case ETHSWT_SWIC_STATE_INIT:
		case ETHSWT_SWIC_STATE_ACTIVE:
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
				ret = E_NOT_OK;
				break;
			}
			break;
		case ETHSWT_SWIC_STATE_UNINIT:
		case ETHSWT_SWIC_STATE_PMIC:
		case ETHSWT_SWIC_STATE_RESET:
		default:	/* default */
			ret = E_NOT_OK;
			break;
		}
		/* SPIのエラー情報を次に残さないために読み捨てする */
		(void)EthSwt_SWIC_Spi_GetSpiRegErr();
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
	static const struct swic_reg_tbl phyon_tbl[]
	=	{ {NULL_PTR,					0u}											/* P5：SIP SAILSS_RGMII0 RGMII */
		, {NULL_PTR,					0u}											/* P7：SIP SGMII0 SGMII        */
		, {NULL_PTR,					0u}											/* P8：SIP SGMII1 SGMII        */
		, {g_regListSeqP1PhyOn,			SWIC_TBL_NUM(g_regListSeqP1PhyOn)}			/* P1：ADC 1000BASE-T1         */
		, {g_regListSeqP2PhyOn,			SWIC_TBL_NUM(g_regListSeqP2PhyOn)}			/* P2：DCM 1000BASE-T1         */
		, {NULL_PTR,					0u}											/* P3：未使用                  */
		, {NULL_PTR,					0u}											/* P4：未使用                  */
		, {NULL_PTR,					0u}											/* P6：DLC 100BASE-TX          */
		, {NULL_PTR,					0u}											/* P9：未使用                  */
		};
	static const struct swic_reg_tbl actdis_tbl[]
	=	{ {NULL_PTR,					0u}											/* P5：SIP SAILSS_RGMII0 RGMII */
		, {NULL_PTR,					0u}											/* P7：SIP SGMII0 SGMII        */
		, {NULL_PTR,					0u}											/* P8：SIP SGMII1 SGMII        */
		, {g_regListSeqSetP1ActDis,		SWIC_TBL_NUM(g_regListSeqSetP1ActDis)}		/* P1：ADC 1000BASE-T1         */
		, {g_regListSeqSetP2ActDis,		SWIC_TBL_NUM(g_regListSeqSetP2ActDis)}		/* P2：DCM 1000BASE-T1         */
		, {NULL_PTR,					0u}											/* P3：未使用                  */
		, {NULL_PTR,					0u}											/* P4：未使用                  */
		, {g_regListSeqSet100BTxStart,	SWIC_TBL_NUM(g_regListSeqSet100BTxStart)}	/* P6：DLC 100BASE-TX          */
		, {NULL_PTR,					0u}											/* P9：未使用                  */
		};
	Std_ReturnType						ret;
	ret = swic_Reg_TblReg(SwitchPortIdx, phyon_tbl, SWIC_TBL_NUM(phyon_tbl));
	if (ret == E_NOT_OK) {return E_NOT_OK;}
	return swic_Reg_TblReg(SwitchPortIdx, actdis_tbl, SWIC_TBL_NUM(actdis_tbl));
}
static Std_ReturnType swic_Reg_SetSwitchPortModeDOWN(const uint8 SwitchPortIdx)
{
	static const struct swic_reg_tbl tbl[]
	=	{ {NULL_PTR,					0u}											/* P5：SIP SAILSS_RGMII0 RGMII */
		, {NULL_PTR,					0u}											/* P7：SIP SGMII0 SGMII        */
		, {NULL_PTR,					0u}											/* P8：SIP SGMII1 SGMII        */
		, {g_regListSeqP1PhyOff,		SWIC_TBL_NUM(g_regListSeqP1PhyOff)}			/* P1：ADC 1000BASE-T1         */
		, {g_regListSeqP2PhyOff,		SWIC_TBL_NUM(g_regListSeqP2PhyOff)}			/* P2：DCM 1000BASE-T1         */
		, {NULL_PTR,					0u}											/* P3：未使用                  */
		, {NULL_PTR,					0u}											/* P4：未使用                  */
		, {g_regListSeqSet100BTxDown,	SWIC_TBL_NUM(g_regListSeqSet100BTxDown)}	/* P6：DLC 100BASE-TX          */
		, {NULL_PTR,					0u}											/* P9：未使用                  */
		};
	return swic_Reg_TblReg(SwitchPortIdx, tbl, SWIC_TBL_NUM(tbl));
}
static Std_ReturnType swic_Reg_GetLink(const uint8 SwitchPortIdx, EthTrcv_LinkStateType *const LinkStatePtr)
{
	struct swic_tbl_lnk {
		const swic_reg_data_t	*tbl;
		const uint32			num;
		const uint32			msk;
		const uint32			dat;
	};
	/* Bit 11: Link Status. */
	/* Bit 2: Copper Link(real time) */
	/* 0 : Link Down */
	/* 1 : Link Up */
	static const struct swic_tbl_lnk	tbl[]
	=	{ {&g_regListSeqGetLinkIeee[16], 7u, 0x0004u, 0x0004u}	/* P5：SIP SAILSS_RGMII0 RGMII */
		, {&g_regListSeqGetLinkIeee[24], 1u, 0x0800u, 0x0800u}	/* P7：SIP SGMII0 SGMII        */
		, {&g_regListSeqGetLinkIeee[25], 1u, 0x0800u, 0x0800u}	/* P8：SIP SGMII1 SGMII        */
		, {&g_regListSeqGetLinkIeee[ 0], 1u, 0x0800u, 0x0800u}	/* P1：ADC 1000BASE-T1         */
		, {&g_regListSeqGetLinkIeee[ 1], 1u, 0x0800u, 0x0800u}	/* P2：DCM 1000BASE-T1         */
		, {&g_regListSeqGetLinkIeee[ 2], 7u, 0x0004u, 0x0004u}	/* P3：未使用                  */
		, {&g_regListSeqGetLinkIeee[ 9], 7u, 0x0004u, 0x0004u}	/* P4：未使用                  */
		, {&g_regListSeqGetLinkIeee[23], 1u, 0x0800u, 0x0800u}	/* P6：DLC 100BASE-TX          */
		, {&g_regListSeqGetLinkIeee[26], 1u, 0x0800u, 0x0800u}	/* P9：未使用                  */
		};
	Std_ReturnType	err;
	uint32			val = 0uL;
	if (SwitchPortIdx >= SWIC_TBL_NUM(tbl))		{ return E_NOT_OK; }
	if (LinkStatePtr == NULL_PTR)		{ return E_NOT_OK; }
	err = swic_Reg_SetTbl(tbl[SwitchPortIdx].tbl, tbl[SwitchPortIdx].num, &val);
	if (err == E_OK) {
		*LinkStatePtr = ((val & tbl[SwitchPortIdx].msk) == tbl[SwitchPortIdx].dat) ? ETHTRCV_LINK_STATE_ACTIVE : ETHTRCV_LINK_STATE_DOWN;
	}
	return err;
}
static Std_ReturnType swic_Reg_MibSelectCLR(const uint8 SwitchPortIdx)
{
	static const struct swic_reg_tbl tbl[]
	=	{ {&g_regListSeqSelectPort[ 8],	2u}	/* P5：SIP SAILSS_RGMII0 RGMII */
		, {&g_regListSeqSelectPort[12],	2u}	/* P7：SIP SGMII0 SGMII        */
		, {&g_regListSeqSelectPort[14],	2u}	/* P8：SIP SGMII1 SGMII        */
		, {&g_regListSeqSelectPort[ 0],	2u}	/* P1：ADC 1000BASE-T1         */
		, {&g_regListSeqSelectPort[ 2],	2u}	/* P2：DCM 1000BASE-T1         */
		, {&g_regListSeqSelectPort[ 4],	2u}	/* P3：未使用                  */
		, {&g_regListSeqSelectPort[ 6],	2u}	/* P4：未使用                  */
		, {&g_regListSeqSelectPort[10],	2u}	/* P6：DLC 100BASE-TX          */
		, {&g_regListSeqSelectPort[16],	2u}	/* P9：未使用                  */
		};
	return swic_Reg_TblReg(SwitchPortIdx, tbl, SWIC_TBL_NUM(tbl));
}
/* ★Debug_Start-------------------------------------------------------------- */
#ifdef EthswtDebugMode2
static void swic_Reg_AddVal(uint32 *const num, const swic_reg_data_t tbl[], const uint32 cnt)
{
	Std_ReturnType	err;
	uint32			val = 0uL;
	err = swic_Reg_SetTbl(tbl, cnt, &val);
	if (err == E_OK) {
		LIB_DI();	/* 5msでクリアされる */
		*num = (((~0uL) - *num) >= val) ? *num + val : ~0uL;
		LIB_EI();
	}
}
#endif /* EthswtDebugMode2 */
/* ★Debug_End---------------------------------------------------------------- */
static void EthSwt_SWIC_Reg_UpdFrameInfo(const uint8 SwitchPortIdx)
{
	Std_ReturnType	err;
#if 0    /* VN-HILSとしては不要なため無効化 */
	uint32	TcamFiltFrmCnt = 0u;
#endif    /* VN-HILSとしては不要なため無効化 */
/* ★Debug_Start-------------------------------------------------------------- */
#ifdef EthswtDebugMode2
	uint8	cnt;
#endif /* EthswtDebugMode2 */
/* ★Debug_End---------------------------------------------------------------- */
	err = swic_Reg_MibSelectCLR(SwitchPortIdx);	/* キャプチャする */
	if (err != E_OK)						{ return; }
#if 0    /* VN-HILSとしては不要なため無効化 */
	swic_Reg_AddVal(&swic_Reg_Mode[SwitchPortIdx].dinf.IngressCount,	g_regListSeqMibInUnderSize, SWIC_TBL_NUM(g_regListSeqMibInUnderSize));	/* 受信ポートの能力以上に送信すると送信側で上がる */
	swic_Reg_AddVal(&swic_Reg_Mode[SwitchPortIdx].dinf.IngressCount,	g_regListSeqMibInFragments, SWIC_TBL_NUM(g_regListSeqMibInFragments));
	swic_Reg_AddVal(&swic_Reg_Mode[SwitchPortIdx].dinf.IngressCount,	g_regListSeqMibInOverSize,  SWIC_TBL_NUM(g_regListSeqMibInOverSize));
	swic_Reg_AddVal(&swic_Reg_Mode[SwitchPortIdx].dinf.IngressCount,	g_regListSeqMibInJabber,    SWIC_TBL_NUM(g_regListSeqMibInJabber));
	swic_Reg_AddVal(&swic_Reg_Mode[SwitchPortIdx].dinf.IngressCount,	g_regListSeqMibInFCSErr,    SWIC_TBL_NUM(g_regListSeqMibInFCSErr));
	swic_Reg_AddVal(&swic_Reg_Mode[SwitchPortIdx].dinf.IngressCount,	g_regListSeqMibInDiscards,  SWIC_TBL_NUM(g_regListSeqMibInDiscards));
	swic_Reg_AddVal(&swic_Reg_Mode[SwitchPortIdx].dinf.IngressCount,	g_regListSeqMibInFiltered,  SWIC_TBL_NUM(g_regListSeqMibInFiltered));
	swic_Reg_AddVal(&TcamFiltFrmCnt,									g_regListSeqMibTcamCnt0,  	SWIC_TBL_NUM(g_regListSeqMibTcamCnt0));
	LIB_DI();	/* 5msでクリアされる */
	SWIC_REG_ADD_VAL(swic_Reg_Mode[SwitchPortIdx].TcamFiltFrm, TcamFiltFrmCnt);
	SWIC_REG_ADD_VAL(swic_Reg_Mode[SwitchPortIdx].dinf.IngressCount, TcamFiltFrmCnt);
	LIB_EI();
#endif    /* VN-HILSとしては不要なため無効化 */
/* ★Debug_Start-------------------------------------------------------------- */
#ifdef EthswtDebugMode2
/* ---------デバッグ用：MIB取得処理-------------- */
		cnt =(uint8)0;
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInOctetLo, SWIC_TBL_NUM(g_regListSeqMibInOctetLo));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInOctetHi, SWIC_TBL_NUM(g_regListSeqMibInOctetHi));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInBadOctet, SWIC_TBL_NUM(g_regListSeqMibInBadOctet));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInUnicast, SWIC_TBL_NUM(g_regListSeqMibInUnicast));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInBroadcast, SWIC_TBL_NUM(g_regListSeqMibInBroadcast));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInMulticast, SWIC_TBL_NUM(g_regListSeqMibInMulticast));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInPause, SWIC_TBL_NUM(g_regListSeqMibInPause));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInUnderSize, SWIC_TBL_NUM(g_regListSeqMibInUnderSize));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInFragments, SWIC_TBL_NUM(g_regListSeqMibInFragments));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInOverSize, SWIC_TBL_NUM(g_regListSeqMibInOverSize));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInJabber, SWIC_TBL_NUM(g_regListSeqMibInJabber));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInRxErr, SWIC_TBL_NUM(g_regListSeqMibInRxErr));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInFCSErr, SWIC_TBL_NUM(g_regListSeqMibInFCSErr));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInDiscards, SWIC_TBL_NUM(g_regListSeqMibInDiscards));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInDiscardsYel, SWIC_TBL_NUM(g_regListSeqMibInDiscardsYel));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInFiltered, SWIC_TBL_NUM(g_regListSeqMibInFiltered));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInAccepted, SWIC_TBL_NUM(g_regListSeqMibInAccepted));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInBadAccepted, SWIC_TBL_NUM(g_regListSeqMibInBadAccepted));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInAVBClassA, SWIC_TBL_NUM(g_regListSeqMibInAVBClassA));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInAVBClassB, SWIC_TBL_NUM(g_regListSeqMibInAVBClassB));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInBadAVBClassA, SWIC_TBL_NUM(g_regListSeqMibInBadAVBClassA));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInBadAVBClassB, SWIC_TBL_NUM(g_regListSeqMibInBadAVBClassB));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInBadQbv, SWIC_TBL_NUM(g_regListSeqMibInBadQbv));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibTcamCnt0, SWIC_TBL_NUM(g_regListSeqMibTcamCnt0));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibTcamCnt1, SWIC_TBL_NUM(g_regListSeqMibTcamCnt1));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibTcamCnt2, SWIC_TBL_NUM(g_regListSeqMibTcamCnt2));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibTcamCnt3, SWIC_TBL_NUM(g_regListSeqMibTcamCnt3));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInDroppedAvbA, SWIC_TBL_NUM(g_regListSeqMibInDroppedAvbA));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInDroppedAvbB, SWIC_TBL_NUM(g_regListSeqMibInDroppedAvbB));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInDaUnknown, SWIC_TBL_NUM(g_regListSeqMibInDaUnknown));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibInMGMT, SWIC_TBL_NUM(g_regListSeqMibInMGMT));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutOctetLo, SWIC_TBL_NUM(g_regListSeqMibOutOctetLo));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutOctetHi, SWIC_TBL_NUM(g_regListSeqMibOutOctetHi));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutUnicast, SWIC_TBL_NUM(g_regListSeqMibOutUnicast));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutBroadcast, SWIC_TBL_NUM(g_regListSeqMibOutBroadcast));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutMulticast, SWIC_TBL_NUM(g_regListSeqMibOutMulticast));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutPause, SWIC_TBL_NUM(g_regListSeqMibOutPause));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibCollisions, SWIC_TBL_NUM(g_regListSeqMibCollisions));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibDeferred, SWIC_TBL_NUM(g_regListSeqMibDeferred));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibSingle, SWIC_TBL_NUM(g_regListSeqMibSingle));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibMultiple, SWIC_TBL_NUM(g_regListSeqMibMultiple));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutFCSErr, SWIC_TBL_NUM(g_regListSeqMibOutFCSErr));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibExcessive, SWIC_TBL_NUM(g_regListSeqMibExcessive));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibLate, SWIC_TBL_NUM(g_regListSeqMibLate));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutQueue0, SWIC_TBL_NUM(g_regListSeqMibOutQueue0));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutQueue1, SWIC_TBL_NUM(g_regListSeqMibOutQueue1));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutQueue2, SWIC_TBL_NUM(g_regListSeqMibOutQueue2));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutQueue3, SWIC_TBL_NUM(g_regListSeqMibOutQueue3));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutQueue4, SWIC_TBL_NUM(g_regListSeqMibOutQueue4));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutQueue5, SWIC_TBL_NUM(g_regListSeqMibOutQueue5));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutQueue6, SWIC_TBL_NUM(g_regListSeqMibOutQueue6));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutQueue7, SWIC_TBL_NUM(g_regListSeqMibOutQueue7));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutOctetsA, SWIC_TBL_NUM(g_regListSeqMibOutOctetsA));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutOctetsB, SWIC_TBL_NUM(g_regListSeqMibOutOctetsB));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutYellow, SWIC_TBL_NUM(g_regListSeqMibOutYellow));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutDiscards, SWIC_TBL_NUM(g_regListSeqMibOutDiscards));
		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibOutMGMT, SWIC_TBL_NUM(g_regListSeqMibOutMGMT));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMib64Octets, SWIC_TBL_NUM(g_regListSeqMib64Octets));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMib65to127Octets, SWIC_TBL_NUM(g_regListSeqMib65to127Octets));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMib128to255Octets, SWIC_TBL_NUM(g_regListSeqMib128to255Octets));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMib256to511Octets, SWIC_TBL_NUM(g_regListSeqMib256to511Octets));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMib512to1023Octets, SWIC_TBL_NUM(g_regListSeqMib512to1023Octets));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMib1024toMaxOctets, SWIC_TBL_NUM(g_regListSeqMib1024toMaxOctets));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibDropEvents, SWIC_TBL_NUM(g_regListSeqMibDropEvents));
//		swic_Reg_AddVal(&debug_MIB[SwitchPortIdx].mibinfo[cnt++],g_regListSeqMibAtsFiltered, SWIC_TBL_NUM(g_regListSeqMibAtsFiltered));
#endif /* EthswtDebugMode2 */
/* ★Debug_End---------------------------------------------------------------- */
	return;
}
#if 0    /* VN-HILSとしては不要なため無効化 */
static void EthSwt_SWIC_Reg_UpdStreamFilterCounter(const uint8 SwitchPortIdx)
{
	static const struct swic_reg_tbl tbl[]
	=	{ {NULL_PTR,		0u}							/* P5 */
		, {NULL_PTR,		0u}							/* P7 */
		, {NULL_PTR,		0u}							/* P8 */
		, {NULL_PTR,		0u}							/* P1 */ /* VN-HILSでは未対応のためテーブル未登録 */
		, {NULL_PTR,		0u}							/* P2 */ /* VN-HILSでは未対応のためテーブル未登録 */
		, {NULL_PTR,		0u}							/* P3 */
		, {NULL_PTR,		0u}							/* P4 */
		, {NULL_PTR,		0u}							/* P5 */
		, {NULL_PTR,		0u}							/* P6 */
		};
	Std_ReturnType	err;
	err = swic_Reg_TblReg(SwitchPortIdx, tbl, SWIC_TBL_NUM(tbl));
	if (err == E_OK) {
		swic_Reg_AddVal(&swic_Reg_Mode[SwitchPortIdx].StreamFiltFrm, &g_regListSeqGetStreamFilterData[0], SWIC_TBL_NUM(g_regListSeqGetStreamFilterData));
	}
}
#endif    /* VN-HILSとしては不要なため無効化 */
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
	=	{ {&g_regListSeqRelayOff[8],	2u}	/* P5：SIP SAILSS_RGMII0 RGMII */
		, {&g_regListSeqRelayOff[12],	2u}	/* P7：SIP SGMII0 SGMII        */
		, {&g_regListSeqRelayOff[14],	2u}	/* P8：SIP SGMII1 SGMII        */
		, {&g_regListSeqRelayOff[0],	2u}	/* P1：ADC 1000BASE-T1         */
		, {&g_regListSeqRelayOff[2],	2u}	/* P2：DCM 1000BASE-T1         */
		, {&g_regListSeqRelayOff[4],	2u}	/* P3：未使用                  */
		, {&g_regListSeqRelayOff[6],	2u}	/* P4：未使用                  */
		, {&g_regListSeqRelayOff[10],	2u}	/* P6：DLC 100BASE-TX          */
		, {&g_regListSeqRelayOff[16],	2u}	/* P9：未使用                  */
		};
	uint32	i;
	uint32	val;
	uint8	idx;
	for (i=0u ; i<SWIC_TBL_NUM(tbl) ; i++) {
		(void)swic_Reg_SetTbl(tbl[i].tbl.tbl, tbl[i].tbl.num, &val);
		if (tbl[i].tmo > 0) {
			EthSwt_SWIC_Org_WaitMS((uint32)tbl[i].tmo);
		}
	}
	for (idx=0U ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		if (swic_Reg_Mode[idx].mode != ETH_MODE_DOWN)	{ continue; }	/* リンクダウン不要 */
		(void)swic_Reg_TblReg(idx, off, SWIC_TBL_NUM(off));
	}
}
static Std_ReturnType swic_Reg_ResetSwitchPortMode(Std_ReturnType ret)
{	/* 初期化後EthSwt_SetSwitchPortModeの状態に戻す */
	Std_ReturnType	err;
	uint8			i;
	for (i=0U ; i<SWIC_TBL_NUM(swic_Reg_Mode) ; i++) {
		if (swic_Reg_Mode[i].mode == swic_Reg_InitPort[i])	{ continue; }	/* 動作モード変更無 */
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
	=	{ {SWIC_REG_TBL(g_regListSeqSetResetDetect)		, STD_OFF}	/* リセット検知用設定 */
		, {SWIC_REG_TBL(g_regListPort)					, STD_OFF}	/* ポート設定 */
		, {SWIC_REG_TBL(g_regListVlan)					, STD_OFF}	/* VLAN設定 */
		, {SWIC_REG_TBL(g_regListL2)					, STD_OFF}	/* L2設定 */
		, {SWIC_REG_TBL(g_regListQos)					, STD_OFF}	/* QoS設定 */
#if 0   /* VN-HILSとしては不要(テーブルNULL)なため無効化 */
		, {SWIC_REG_TBL(g_regListAcl)					, STD_OFF}	/* ACL設定 */
		, {SWIC_REG_TBL(g_regListArp)					, STD_OFF}	/* ARP設定 */
#endif  /* VN-HILSとしては不要(テーブルNULL)なため無効化 */
		, {SWIC_REG_TBL(g_regListTc10)					, STD_OFF}	/* TC10設定 */
		/*, {SWIC_REG_TBL(g_regListPTP)					, STD_OFF}*//* PTP設定 */
#if 0   /* VN-HILSとしては不要(設定なし)なため無効化 */
		, {SWIC_REG_TBL(g_regListBandwidthLimit)		, STD_OFF}	/* 帯域制限設定 */
#endif  /* VN-HILSとしては不要(設定なし)なため無効化 */
		, {SWIC_REG_TBL(g_regListSeqInterruptClear)		, STD_OFF}	/* 割り込み要因クリア */
		, {SWIC_REG_TBL(g_regListSeqSWICReset)			, STD_OFF}	/* ソフトウェアリセット */
		, {SWIC_REG_TBL(g_regListSeqPPUOff)				, STD_OFF}	/* PPU OFF */
		, {SWIC_REG_TBL(g_regListSeqGetWatchdogError)	, STD_ON}	/* レジスタ/テーブル化け確認レジスタ */
		, {SWIC_REG_TBL(g_regListSeqRelayOn)			, STD_OFF}	/* 中継ON */
		, {SWIC_REG_TBL(g_regListSeqSetP5ActDis)		, STD_OFF}	/* P5：SIP SAILSS_RGMII0 RGMII設定 */
		, {SWIC_REG_TBL(g_regListSeqSetP7ActDis)		, STD_OFF}	/* P7：SIP SGMII0 SGMII設定 */
		, {SWIC_REG_TBL(g_regListSeqSetP8ActDis)		, STD_OFF}	/* P8：SIP SGMII1 SGMII設定 */
#if 1   /* ★暫定対応：MCU側のみでリンクアップさせる★ */
		, {SWIC_REG_TBL(g_regListSeqSetP1ActDis)		, STD_OFF}	/* P1：ADC 1000BASE-T1設定 */
		, {SWIC_REG_TBL(g_regListSeqSetP2ActDis)		, STD_OFF}	/* P2：DCM 1000BASE-T1設定 */
#endif  /* ★暫定対応：MCU側のみでリンクアップさせる★ */
		};
	Std_ReturnType	ret = E_OK;						/* 設定値無し */
	Std_ReturnType	err = E_OK;
	uint32			idx;
	uint32			val;
	for (idx=0U ; idx < SWIC_TBL_NUM(tbl) ; idx++) {			/* リードバック無 */
		err = swic_Reg_SetTbl(tbl[idx].tbl.tbl, tbl[idx].tbl.num, (tbl[idx].rst == STD_OFF) ? &val : NULL_PTR);
		if (err == E_OK)			{ continue; }
		ret = err;
		if (tbl[idx].rst == STD_OFF){ continue; }
		swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_INIT);				/* 中断してリセット */
		break;
	}
	swic_Reg_Inf.err = swic_Reg_ResetSwitchPortMode(ret);		/* 起動時は何もしない */
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_INIT:
		for (idx=0U ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {	/* リンク状態未取得 */
			swic_Reg_Mode[idx].lnk_err = E_NOT_OK;
			if (swic_Reg_Mode[idx].lnk_chk == STD_ON) {
				swic_Reg_Mode[idx].lnk_tim = swic_Reg_Inf.tim;
			}
		}
		/* 周期タイマと実行リクエストを初期化 */
		swic_Reg_Inf.CycRstReq = STD_OFF;
		swic_Reg_Inf.CycRstTim = 0;
		swic_Reg_Inf.CycMonReq = STD_OFF;
		swic_Reg_Inf.CycMonTim = 0;
		for (idx=0 ; idx<SWIC_TBL_NUM(swic_Reg_Inf.cyc) ; idx++) {
			swic_Reg_Inf.cyc[idx].tim = 0;
			swic_Reg_Inf.cyc[idx].req = swic_Reg_TimFnc[idx].ini;
		}
		swic_Reg_SetState(ETHSWT_SWIC_STATE_ACTIVE);
		break;
	case ETHSWT_SWIC_STATE_ACTIVE: /* ハードリセット / 低電圧 */
	case ETHSWT_SWIC_STATE_UNINIT: /* ハードリセット / 低電圧 */
	case ETHSWT_SWIC_STATE_PMIC:   /* ハードリセット / 低電圧 */
	case ETHSWT_SWIC_STATE_RESET:  /* ハードリセット / 低電圧 */
	default:	/* default */
		break;
	}
	return;
}
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
		swic_Reg_Mode[SwitchPortIdx].lnk_sts = sts;
		swic_Reg_Mode[SwitchPortIdx].lnk_err = err;
		if (swic_Reg_Mode[SwitchPortIdx].lnk_chk == STD_OFF){ return; }
		if (sts != swic_Reg_Mode[SwitchPortIdx].lnk_exp)	{ return; }
	}					/* アクセス失敗は確認を止める */
	swic_Reg_Mode[SwitchPortIdx].lnk_chk = STD_OFF;
}
static void swic_Reg_CycIDS(void)
{
#if 0    /* VN-HILSとしては不要なため無効化 */
	uint8	idx;
	for (idx=0u ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		EthSwt_SWIC_Reg_UpdStreamFilterCounter(idx);
	}
#endif    /* VN-HILSとしては不要なため無効化 */
}
static void swic_Reg_CycMIB(void)
{	/* MIB取得 */
	uint8	idx;
	for (idx=0u ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		if (swic_Reg_MibPort[idx] != STD_OFF) {
			EthSwt_SWIC_Reg_UpdFrameInfo(idx);
		}
	}
}
static void swic_Reg_CycLINK(void)
{	/* リンク取得 */
	uint8	idx;
	for (idx=0u ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		swic_Reg_GetLinkState(idx);
	}
}
static void swic_Reg_CycLnk(void)
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
#if 0    /* VN-HILSとしては不要なため無効化 */
static Std_ReturnType swic_Reg_CycRst(void)
{	/* 常にPMIC ONのため、PMIC_ENの確認不要 */
	uint32		i;
	if (swic_Reg_Inf.CycRstReq != STD_ON) {return E_OK;}
	swic_Reg_Inf.CycRstReq = STD_OFF;
	SWIC_TBL_CHK(SWIC_TBL_NUM(g_regListSeqGetResetDetect) != 16uL);
	for (i=0uL ; i<SWIC_TBL_NUM(g_regListSeqGetResetDetect) ; i+=4uL) {
		Std_ReturnType	err;
		err = swic_Reg_SetTbl(&g_regListSeqGetResetDetect[i], 4uL, NULL_PTR);
		if (err == E_OK)									{ return E_OK; }	/* 全部異常値でない場合リセット無 */
		if ((uint32)swic_Reg_Inf.sts != (uint32)ETHSWT_SWIC_STATE_ACTIVE)	{ return E_OK; }	/* CRC異常中断 */
	}
	swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_GPIO);
	return E_NOT_OK;
}
#endif    /* VN-HILSとしては不要なため無効化 */
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

	if (swic_Reg_Inf.CycMonReq != STD_ON) {return E_OK;}
	swic_Reg_Inf.CycMonReq = STD_OFF;
	err = EthSwt_SWIC_Org_INTN();
	if (err == E_OK)	{ return E_OK;}				/* 異常なし */
	do {
		const struct swic_reg_bit	*const bit = tbl->fnc.tbl;
		const uint32				num = tbl->fnc.num;
		uint32						i;
		uint32						msk;
		err = swic_Reg_SetTbl(tbl->tbl.tbl, tbl->tbl.num, &val);
		if (err != E_OK) { return E_OK;}			/* 失敗は何もしない */
		tbl = NULL_PTR;
		msk = 0uL;								/* 有効ビット算出 */
		for (i=0uL ; i<num ; i++) { msk |= bit[i].bit; }
		val &= msk;
		if (val == 0uL) { return E_OK;}				/* 有効なbit無:③処置不要 */
		for (i=0uL ; i<num ; i++) {
			if (val != bit[i].bit) { continue; }/* 1bit一致のみ */
			if (bit[i].tbl != NULL_PTR) {
				tbl = bit[i].tbl;
				break;
			}
			switch (bit[i].prc) {
			default:	/* ③処置不要:無(カバレッジマスタ対応) */
			case 1:		/* ①FIRハードリセット */
				swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_SWIC);
				break;
			case 2:		/* ②FIRソフトリセット */
				swic_Reg_PortMacResetRequest();
				break;
			}
			return E_NOT_OK;
		}
	}	while (tbl != NULL_PTR);
	swic_Reg_Reset(ETHSWT_SWIC_REG_FACT_SWIC);	/* 複数ビット1:①FIRハードリセット */
	return E_NOT_OK;
}

static void swic_Reg_SwitchActive(void)
{
	uint32	i;
	uint8	idx;
	Std_ReturnType	err;
#if 0    /* VN-HILSとしては不要なため無効化 */
	/* SWIC内部異常 */
	err = swic_Reg_CycRst();
	if (err != E_OK) { return; } /* リセットした時は以下実施不要 */
#endif    /* VN-HILSとしては不要なため無効化 */
	/* SWIC内部エラー検出 */
	err = swic_Reg_CycMon();
	if (err != E_OK) { return; } /* リセットした時は以下実施不要 */

	for (idx=0u ; idx<SWIC_TBL_NUM(swic_Reg_Mode) ; idx++) {
		if (swic_Reg_Mode[idx].req_mode == STD_ON) {
			swic_Reg_SetSwitchPortMode(idx);
		}
#if 0    /* VN-HILSとしては不要なため無効化 */
		if (swic_Reg_Mode[idx].req_clr == STD_ON) {
			swic_Reg_Mode[idx].req_clr = STD_OFF;
			(void)swic_Reg_MibSelectCLR(idx);
		}
#endif    /* VN-HILSとしては不要なため無効化 */
	}
	for (i=0 ; i< SWIC_TBL_NUM(swic_Reg_TimFnc) ; i++) {
		if (swic_Reg_Inf.cyc[i].req != STD_ON) { continue; }
		swic_Reg_Inf.cyc[i].req = STD_OFF;
		swic_Reg_TimFnc[i].fnc();
		return;			/* 負荷が上がらないように1周期毎に確認する */
	}
	swic_Reg_CycLnk();	/* 何も処理してないとき実施 */
}
void EthSwt_SWIC_BackgroundTask(void)
{
/*	Std_ReturnType	err;	*/
	switch (swic_Reg_Inf.sts) {
	case ETHSWT_SWIC_STATE_INIT:
		swic_Reg_SwitchInit();
		break;
	case ETHSWT_SWIC_STATE_RESET:
		EthSwt_SWIC_Org_Reset();
		swic_Reg_Inf.sts = ETHSWT_SWIC_STATE_INIT;	/* レジスタ設定 */
		break;
	case ETHSWT_SWIC_STATE_PMIC:
		EthSwt_SWIC_Org_WaitSPI();					/* T8 Wait */
		swic_Reg_Inf.sts = ETHSWT_SWIC_STATE_RESET;	/* レジスタ設定 */
		break;
	case ETHSWT_SWIC_STATE_ACTIVE:
		swic_Reg_SwitchActive();
		break;
	case ETHSWT_SWIC_STATE_UNINIT:
	default:	/* default */
		break;
	}
}
#define	ETHSWT_STOP_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
