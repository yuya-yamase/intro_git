/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  External Signal Controll                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "Dio.h"
#include "ExtSigCtrl_Main.h"
#include "ExtSigCtrl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 車両信号ポーリング状態定義 */
#define EXTSIG_POLL_STS_STOP		(U1)0x00U		/* ポーリング停止中	*/
#define EXTSIG_POLL_STS_CYC			(U1)0x01U		/* ポーリング定期	*/

/* 同一論理取得回数カウント処理 */
#define EXTSIG_SAME_CNT_INIT	(U1)0x01U		/* 同一論理取得カウント初期値	*/

/* Mainタスク周期 */
#define EXTSIG_MAIN_TICK			(U1)0x05U		/* 5ms	*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 車両信号ステータステーブル */
typedef	struct	{
	U1	u1t_CycTim;					/* 定周期時間 */
	U1	u1t_SameCntNum;				/* 同一論理判定確定回数 */
	U1	u1t_DioChannelId;			/* DIOチャネルID */
} ST_EXTSIG_STS;

/* ポーリングステータス */
typedef struct {
	U1	u1t_PollTimCnt;		/* ポーリングタイマカウンタ */
	U1	u1t_PollPreSts;		/* ポーリング端子前回状態 */
	U1	u1t_PollSts;		/* ポーリング端子状態 */
	U1	u1t_PollSameCnt;	/* ポーリング端子同一状態カウンタ */
} ST_EXTSIG_POLL_STS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1t_PollSts;
static ST_EXTSIG_POLL_STS ast_ExtSig_PollSts[EXTSIG_KIND_NUM];
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void ExtSigCtrl_TrgTimCtrl(void);
static void ExtSigCtrl_Poll(void);
static void ExtSigCtrl_Cyc(const U1 u1t_Kind);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_EXTSIG_STS tb_ExtSig_Sts[EXTSIG_KIND_NUM]
= {
	/* BOOT */
	{
		(100/EXTSIG_MAIN_TICK),	/* サンプリング周期 */
		3,						/* 同一論理判定確定回数 */
		DIO_ID_PORT5_CH6		/* DIOチャネルID */
	},
	/* TEST */
	{
		(100/EXTSIG_MAIN_TICK),	/* サンプリング周期 */
		3,						/* 同一論理判定確定回数 */
		DIO_ID_PORT0_CH2		/* DIOチャネルID */
	},
	/* EXT-PWR-SW */
	{
		(25/EXTSIG_MAIN_TICK),	/* サンプリング周期 */
		2,						/* 同一論理判定確定回数 */
		DIO_ID_PORT8_CH1		/* DIOチャネルID */
	}
};


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void ExtSigCtrl_Init(void)
{
	U1 u1t_Kind;

	u1t_PollSts = EXTSIG_POLL_STS_STOP;

	for (u1t_Kind = (U1)0; u1t_Kind < (U1)EXTSIG_KIND_NUM; u1t_Kind++) {
		ast_ExtSig_PollSts[u1t_Kind].u1t_PollPreSts = EXTSIG_TMNL_STS_NON;
		ast_ExtSig_PollSts[u1t_Kind].u1t_PollSts = EXTSIG_TMNL_STS_NON;
		ast_ExtSig_PollSts[u1t_Kind].u1t_PollSameCnt = EXTSIG_SAME_CNT_INIT;
		ast_ExtSig_PollSts[u1t_Kind].u1t_PollTimCnt = 0;
	}

	return;
}

void ExtSigCtrl_MainFunction(void)
{
	if (u1t_PollSts == EXTSIG_POLL_STS_STOP) {
		/* 回路安定待ち処理  */
		ExtSigCtrl_TrgTimCtrl();
	} else {
		/* ポーリング処理 */
		ExtSigCtrl_Poll();
	}

	return;
}

static void ExtSigCtrl_TrgTimCtrl(void)
{
	static U1 u1t_TrgTim = (U1)(100/EXTSIG_MAIN_TICK); /* 100ms */

	/* マイナスガード */
	if (u1t_TrgTim > 0) {
		u1t_TrgTim--;
	}

	if (u1t_TrgTim <= 0) {
		u1t_PollSts = EXTSIG_POLL_STS_CYC;
	} else {
		/* Do nothing */
	}

	return;
}

static void ExtSigCtrl_Poll(void)
{
	U1 u1t_Kind;

	for (u1t_Kind = (U1)0; u1t_Kind < (U1)EXTSIG_KIND_NUM; u1t_Kind++) {
		if (ast_ExtSig_PollSts[u1t_Kind].u1t_PollTimCnt <= 0) {
			ExtSigCtrl_Cyc(u1t_Kind);
			ast_ExtSig_PollSts[u1t_Kind].u1t_PollTimCnt = tb_ExtSig_Sts[u1t_Kind].u1t_CycTim;
		} else {
			/* マイナスガード */
			if (ast_ExtSig_PollSts[u1t_Kind].u1t_PollTimCnt > 0) {
				ast_ExtSig_PollSts[u1t_Kind].u1t_PollTimCnt--;
			}
		}
	}

	return;
}

static void ExtSigCtrl_Cyc(const U1 u1t_Kind)
{
	U1 u1t_NowCnc;

	u1t_NowCnc = Dio_ReadChannel(tb_ExtSig_Sts[u1t_Kind].u1t_DioChannelId);

	if (u1t_NowCnc == ast_ExtSig_PollSts[u1t_Kind].u1t_PollPreSts) {
		if (ast_ExtSig_PollSts[u1t_Kind].u1t_PollSameCnt < tb_ExtSig_Sts[u1t_Kind].u1t_SameCntNum) {
			ast_ExtSig_PollSts[u1t_Kind].u1t_PollSameCnt++;
		} else {
			/* Do nothing */
		}
	} else {
		ast_ExtSig_PollSts[u1t_Kind].u1t_PollSameCnt = EXTSIG_SAME_CNT_INIT;
	}

	ast_ExtSig_PollSts[u1t_Kind].u1t_PollPreSts = u1t_NowCnc;
	
	if (ast_ExtSig_PollSts[u1t_Kind].u1t_PollSameCnt >= tb_ExtSig_Sts[u1t_Kind].u1t_SameCntNum) {
		if (ast_ExtSig_PollSts[u1t_Kind].u1t_PollPreSts != ast_ExtSig_PollSts[u1t_Kind].u1t_PollSts) {
			ast_ExtSig_PollSts[u1t_Kind].u1t_PollSts = ast_ExtSig_PollSts[u1t_Kind].u1t_PollPreSts;
		} else {
			/* Do nothing */
		}
	} else {
		/* Do nothing */
	}

	return;
}
