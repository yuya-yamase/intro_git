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
#define U1_EXTSIGCTRL_POLL_STS_STOP		(U1)0x00U		/* ポーリング停止中	*/
#define U1_EXTSIGCTRL_POLL_STS_CYC			(U1)0x01U		/* ポーリング定期	*/

/* 同一論理取得回数カウント処理 */
#define U1_EXTSIGCTRL_SAME_CNT_INIT	(U1)0x01U		/* 同一論理取得カウント初期値	*/

#define U1_EXTSIGCTRL_PORT_LEVEL_INIT	(U1)0xFFU	/* DIOレベル初期値 */

/* 時間計測用 */
#define U1_EXTSIGCTRL_MAIN_TICK				(U1)5U		/* メインタスク周期(5ms)	*/
#define U1_EXTSIGCTRL_TIM_CNT_25MS			(U1)(25U/U1_EXTSIGCTRL_MAIN_TICK)	/* 25ms */
#define U1_EXTSIGCTRL_TIM_CNT_100MS			(U1)(100U/U1_EXTSIGCTRL_MAIN_TICK)	/* 100ms */


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 外部信号ステータステーブル */
typedef	struct	{
	Dio_ChannelType	u2t_DioChannelId;	/* DIOチャネルID */
	U1	u1t_CycTim;						/* 定周期時間 */
	U1	u1t_SameCntNum;					/* 同一論理判定確定回数 */
} ST_EXTSIGCTRL_STS;

/* ポーリングステータス */
typedef struct {
	U1				u1t_PollTimCnt;		/* ポーリングタイマカウンタ */
	Dio_LevelType	u1t_PollTmnlPreCnc;	/* ポーリング端子前回レベル */
	U1				u1t_PollTmnlSts;	/* ポーリング端子状態 */
	U1				u1t_PollSameCnt;	/* ポーリング端子同一状態カウンタ */
} ST_EXTSIGCTRL_POLL_STS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1s_ExtSigCtrl_PollSts;
static ST_EXTSIGCTRL_POLL_STS stsa_ExtSigCtrl_PollSts[EXTSIGCTRL_KIND_NUM];
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
const ST_EXTSIGCTRL_STS tb_ExtSigCtrl_Sts[EXTSIGCTRL_KIND_NUM]
= {
	/* TEST */
	{
		DIO_ID_PORT0_CH2,				/* DIOチャネルID */
		U1_EXTSIGCTRL_TIM_CNT_100MS,	/* サンプリング周期 */
		(U1)3U,							/* 同一論理判定確定回数 */
	},
	/* BOOT */
	{
		DIO_ID_PORT5_CH6,				/* DIOチャネルID */
		U1_EXTSIGCTRL_TIM_CNT_100MS,	/* サンプリング周期 */
		(U1)3U,							/* 同一論理判定確定回数 */
	},
	/* EXT-PWR-SW */
	{
		DIO_ID_PORT8_CH1,				/* DIOチャネルID */
		U1_EXTSIGCTRL_TIM_CNT_25MS,		/* サンプリング周期 */
		(U1)2U,							/* 同一論理判定確定回数 */
	}
};


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void ExtSigCtrl_Init(void)
{
	U1 u1t_Kind;

	u1s_ExtSigCtrl_PollSts = U1_EXTSIGCTRL_POLL_STS_STOP;

	for (u1t_Kind = (U1)0; u1t_Kind < (U1)EXTSIGCTRL_KIND_NUM; u1t_Kind++) {
		stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTimCnt = (U1)0;
		stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTmnlPreCnc = U1_EXTSIGCTRL_PORT_LEVEL_INIT;
		stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTmnlSts = EXTSIGCTRL_TMNL_STS_NON;
		stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSameCnt = U1_EXTSIGCTRL_SAME_CNT_INIT;
	}

	return;
}

void ExtSigCtrl_MainFunction(void)
{
	/* 回路安定待ち処理  */
	ExtSigCtrl_TrgTimCtrl();

	if (u1s_ExtSigCtrl_PollSts == U1_EXTSIGCTRL_POLL_STS_CYC) {
		/* ポーリング処理 */
		ExtSigCtrl_Poll();
	}

	return;
}

static void ExtSigCtrl_TrgTimCtrl(void)
{
	static U1 u1t_ExtSigCtrl_TrgTim = U1_EXTSIGCTRL_TIM_CNT_100MS;

	if (u1t_ExtSigCtrl_TrgTim <= (U1)0) {
		u1s_ExtSigCtrl_PollSts = U1_EXTSIGCTRL_POLL_STS_CYC;
	} else {
		u1t_ExtSigCtrl_TrgTim--;
	}

	return;
}

static void ExtSigCtrl_Poll(void)
{
	U1 u1t_Kind;

	for (u1t_Kind = (U1)0; u1t_Kind < (U1)EXTSIGCTRL_KIND_NUM; u1t_Kind++) {
		if (stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTimCnt <= (U1)0) {
			ExtSigCtrl_Cyc(u1t_Kind);
			stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTimCnt = tb_ExtSigCtrl_Sts[u1t_Kind].u1t_CycTim;
		} else {
			stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTimCnt--;
		}
	}

	return;
}

static void ExtSigCtrl_Cyc(const U1 u1t_Kind)
{
	Dio_LevelType u1t_NowCnc;

	u1t_NowCnc = Dio_ReadChannel(tb_ExtSigCtrl_Sts[u1t_Kind].u2t_DioChannelId);

	if (u1t_NowCnc == stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTmnlPreCnc) {
		if (stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSameCnt < tb_ExtSigCtrl_Sts[u1t_Kind].u1t_SameCntNum) {
			stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSameCnt++;
		}
	} else {
		stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSameCnt = U1_EXTSIGCTRL_SAME_CNT_INIT;
	}

	if (stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollSameCnt >= tb_ExtSigCtrl_Sts[u1t_Kind].u1t_SameCntNum) {
		if (u1t_NowCnc == STD_HIGH) {
			stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTmnlSts = EXTSIGCTRL_TMNL_STS_ON;
		} else {
			stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTmnlSts = EXTSIGCTRL_TMNL_STS_OFF;
		}
	}

	stsa_ExtSigCtrl_PollSts[u1t_Kind].u1t_PollTmnlPreCnc = u1t_NowCnc;

	return;
}
