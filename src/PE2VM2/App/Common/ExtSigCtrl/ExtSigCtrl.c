/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  External Signal Control                                                                                                          */
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
#include "ExtSigCtrl.h"
#include "ExtSigCtrl_Main.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 車両信号ポーリング状態定義 */
#define U1_EXTSIGCTRL_POLL_STS_STOP			(U1)0x00U		/* ポーリング停止中	*/
#define U1_EXTSIGCTRL_POLL_STS_CYC			(U1)0x01U		/* ポーリング定期	*/

/* 同一論理取得回数カウント処理 */
#define U1_EXTSIGCTRL_SAME_CNT_INIT			(U1)0x01U		/* 同一論理取得カウント初期値	*/
#define U1_EXTSIGCTRL_PORT_LEVEL_INIT		(U1)0xFFU		/* DIOレベル初期値 */

/* 時間計測用 */
#define U1_EXTSIGCTRL_MAIN_TICK				(U1)5U			/* メインタスク周期(5ms)	*/
#define U1_EXTSIGCTRL_POLLTRGTIMCNT_MIN		(U1)1U			/* ポーリング開始トリガタイマカウンタ最小値 */
#define U1_EXTSIGCTRL_POLLTIMCNT_MIN		(U1)1U			/* ポーリングタイマカウンタ最小値 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 外部信号ステータステーブル */
typedef	struct	{
	Dio_ChannelType	DioChannelId;	/* DIOチャネルID */
	U1	u1t_CycTim;						/* 定周期時間 */
	U1	u1t_SameCntNum;					/* 同一論理判定確定回数 */
	U1	u1t_StrTim;						/* ポーリング開始待ち時間 */
} ST_EXTSIGCTRL_STS;

/* ポーリングステータス */
typedef struct {
	Dio_LevelType	PollTmnlPreCnc;	/* ポーリング端子前回レベル */
	U1				u1t_PollSts;		/* ポーリング状態 */
	U1				u1t_PollTimCnt;		/* ポーリングタイマカウンタ */
	U1				u1t_PollSigSts;		/* ポーリング信号状態 */
	U1				u1t_PollSameCnt;	/* ポーリング端子同一状態カウンタ */
	U1				u1t_PollTrgTimCnt;	/* ポーリング開始トリガタイマカウンタ */
} ST_EXTSIGCTRL_POLL_STS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_EXTSIGCTRL_POLL_STS stsa_ExtSigCtrl_PollSts[EXTSIGCTRL_KIND_NUM];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void ExtSigCtrl_InitSigSts(const U1 u1t_Kind);
static void ExtSigCtrl_TrgTimCtrl(const U1 u1t_Kind);
static void ExtSigCtrl_Poll(const U1 u1t_Kind);
static void ExtSigCtrl_Cyc(const U1 u1t_Kind);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_EXTSIGCTRL_STS stsa_ExtSigCtrl_Sts[EXTSIGCTRL_KIND_NUM]
= {
	/* TEST */
	{
		DIO_ID_PORT5_CH6,						/* DIOチャネルID */
		(U1)(100U/U1_EXTSIGCTRL_MAIN_TICK),		/* サンプリング周期 */
		(U1)3U,									/* 同一論理判定確定回数 */
		(U1)(100U/U1_EXTSIGCTRL_MAIN_TICK),		/* ポーリング開始待ち時間 */
	},
	/* BOOT */
	{
		DIO_ID_PORT0_CH2,						/* DIOチャネルID */
		(U1)(100U/U1_EXTSIGCTRL_MAIN_TICK),		/* サンプリング周期 */
		(U1)3U,									/* 同一論理判定確定回数 */
		(U1)(100U/U1_EXTSIGCTRL_MAIN_TICK),		/* ポーリング開始待ち時間 */
	},
	/* EXT-PWR-SW */
	{
		DIO_ID_PORT8_CH1,						/* DIOチャネルID */
		(U1)(25U/U1_EXTSIGCTRL_MAIN_TICK),		/* サンプリング周期 */
		(U1)2U,									/* 同一論理判定確定回数 */
		(U1)(100U/U1_EXTSIGCTRL_MAIN_TICK),		/* ポーリング開始待ち時間 */
	}
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void ExtSigCtrl_Init(void)
{
	U1 u1t_Kind;

	for (u1t_Kind = (U1)0U; u1t_Kind < (U1)EXTSIGCTRL_KIND_NUM; u1t_Kind++) {
		ExtSigCtrl_InitSigSts(u1t_Kind);
	}

	return;
}

void ExtSigCtrl_MainFunction(void)
{
	U1 u1t_Kind;
	Dio_LevelType v33PeriOn;

	for (u1t_Kind = (U1)0U; u1t_Kind < (U1)EXTSIGCTRL_KIND_NUM; u1t_Kind++) {
		switch (u1t_Kind) {
			case EXTSIGCTRL_KIND_TEST:
				v33PeriOn = Dio_ReadChannel(DIO_ID_PORT10_CH2);
				if (v33PeriOn != STD_HIGH) {
					ExtSigCtrl_InitSigSts(u1t_Kind);
				}
				break;
			default:
				break;
		}

		if (stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSts == U1_EXTSIGCTRL_POLL_STS_CYC) {
			/* ポーリング処理 */
			ExtSigCtrl_Poll(u1t_Kind);
		} else {
			/* 回路安定待ち処理  */
			ExtSigCtrl_TrgTimCtrl(u1t_Kind);
		}
	}

	return;
}

U1 ExtSigCtrl_GetSigSts(const E_EXTSIGCTRL_KIND e_Kind)
{
	U1 u1t_Sts = U1_EXTSIGCTRL_INVALID_PARAM;

	/* コンパイルエラーとなるため、if文の条件式から e_Kind >= EXTSIGCTRL_KIND_TEST を意図的に外しています */
	if (e_Kind < EXTSIGCTRL_KIND_NUM) {
		u1t_Sts =  stsa_ExtSigCtrl_PollSts[e_Kind].u1t_PollSigSts;
	}

	return u1t_Sts;
}

static void ExtSigCtrl_InitSigSts(const U1 u1t_Kind)
{
	stsa_ExtSigCtrl_PollSts[u1t_Kind].PollTmnlPreCnc = U1_EXTSIGCTRL_PORT_LEVEL_INIT;
	stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSts = U1_EXTSIGCTRL_POLL_STS_STOP;
	stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTimCnt = U1_EXTSIGCTRL_POLLTIMCNT_MIN;
	stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSigSts = U1_EXTSIGCTRL_SIG_STS_UNKNOWN;
	stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSameCnt = U1_EXTSIGCTRL_SAME_CNT_INIT;
	stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTrgTimCnt = stsa_ExtSigCtrl_Sts[u1t_Kind].u1t_StrTim;

	return;
}

static void ExtSigCtrl_TrgTimCtrl(const U1 u1t_Kind)
{
	if (stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTrgTimCnt <= U1_EXTSIGCTRL_POLLTRGTIMCNT_MIN) {
		stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSts = U1_EXTSIGCTRL_POLL_STS_CYC;
	} else {
		stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTrgTimCnt--;
	}

	return;
}

static void ExtSigCtrl_Poll(const U1 u1t_Kind)
{
	if (stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTimCnt <= U1_EXTSIGCTRL_POLLTIMCNT_MIN) {
		ExtSigCtrl_Cyc(u1t_Kind);
		stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTimCnt = stsa_ExtSigCtrl_Sts[u1t_Kind].u1t_CycTim;
	} else {
		stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTimCnt--;
	}

	return;
}

static void ExtSigCtrl_Cyc(const U1 u1t_Kind)
{
	Dio_LevelType nowCnc;

	nowCnc = Dio_ReadChannel(stsa_ExtSigCtrl_Sts[u1t_Kind].DioChannelId);

	if (nowCnc == stsa_ExtSigCtrl_PollSts[u1t_Kind].PollTmnlPreCnc) {
		if (stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSameCnt < stsa_ExtSigCtrl_Sts[u1t_Kind].u1t_SameCntNum) {
			stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSameCnt++;
		}
	} else {
		stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSameCnt = U1_EXTSIGCTRL_SAME_CNT_INIT;
	}

	if (stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSameCnt >= stsa_ExtSigCtrl_Sts[u1t_Kind].u1t_SameCntNum) {
		if (nowCnc == STD_HIGH) {
			stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSigSts = U1_EXTSIGCTRL_SIG_STS_ON;
		} else {
			stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSigSts = U1_EXTSIGCTRL_SIG_STS_OFF;
		}
	}

	stsa_ExtSigCtrl_PollSts[u1t_Kind].PollTmnlPreCnc = nowCnc;

	return;
}
