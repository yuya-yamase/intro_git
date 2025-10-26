/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_SQI.c                                           */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include "EthSwt_SWIC_SQI.h"
#include "EthSwt_SWIC_Reg.h"
#include "EthSwt_SWIC_STM.h"
#include "EthSwt_SWIC_SQI_Cfg.h"
#include <LIB.h>
#include "EthSwt_SWIC_Time.h"
#include "EthSwt_SWIC_Define.h"
/* -------------------------------------------------------------------------- */
static struct {
	volatile Std_ReturnType			getSqiResult;
	volatile uint8					SqiValue;
} S_ETHSWT_SWIC_SQI[D_ETHSWT_SWIC_PORT_NUM];	/* SQI取得を想定してRAM持ち */

static struct {			/* タイマ */
	sint32			time;				/* タイマカウンタ */
	volatile uint8	req;				/* 処理要求 */
} S_ETHSWT_SWIC_SQI_TIMER;

/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_sqi_read(uint32 * const errFactor);
static Std_ReturnType ethswt_swic_sqi_readPerPort(const uint8 SwitchPortIdx, uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_SQI_Init (void)/* SQI関連データの初期化 */
{
	uint8   idx;

	/* タイマクリア */
	S_ETHSWT_SWIC_SQI_TIMER.time = 0;
	S_ETHSWT_SWIC_SQI_TIMER.req = STD_ON;

	for (idx = 0; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
		S_ETHSWT_SWIC_SQI[idx].getSqiResult         = E_NOT_OK;
		S_ETHSWT_SWIC_SQI[idx].SqiValue             = 0;
    }

	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_SQI_TimerUpdate (void)
{
	S_ETHSWT_SWIC_SQI_TIMER.time = S_ETHSWT_SWIC_SQI_TIMER.time + D_ETHSWT_SWIC_PERIOD;
	if (D_ETHSWT_SWIC_SQI_GET_CYCLE <= S_ETHSWT_SWIC_SQI_TIMER.time) {
		S_ETHSWT_SWIC_SQI_TIMER.time = S_ETHSWT_SWIC_SQI_TIMER.time - D_ETHSWT_SWIC_SQI_GET_CYCLE;
		S_ETHSWT_SWIC_SQI_TIMER.req = STD_ON;
	}

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_SQI_Clear (void)/* SQI関連データの初期化 */
{
	uint8   idx;

	LIB_DI();
	for (idx = 0; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
		S_ETHSWT_SWIC_SQI[idx].getSqiResult         = E_NOT_OK;
		S_ETHSWT_SWIC_SQI[idx].SqiValue             = 0;
    }
	/* タイマクリア */
	S_ETHSWT_SWIC_SQI_TIMER.time = 0;
	S_ETHSWT_SWIC_SQI_TIMER.req = STD_ON;
	LIB_EI();
	
	for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
		if (G_ETHSWT_SWIC_SQI_VAILD[idx] == STD_ON) {
			ETHSWT_SWIC_SQI_NOTIFY(idx, E_NOT_OK, 0u);
		}
	}
	
	return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_SQI_Action (uint32 * const errFactor)
{
    Std_ReturnType	result = E_OK;
	uint8			req;

	LIB_DI();
	req = S_ETHSWT_SWIC_SQI_TIMER.req;
	LIB_EI();

	if (STD_ON == req) {
		LIB_DI();
		S_ETHSWT_SWIC_SQI_TIMER.req = STD_OFF;
		LIB_EI();
		result = ethswt_swic_sqi_read(errFactor);
	}

	return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_sqi_read(uint32 * const errFactor)
{
	Std_ReturnType	result = E_NOT_OK;
	uint8			idx;

	for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
		if (G_ETHSWT_SWIC_SQI_VAILD[idx] == STD_ON) {
			result = ethswt_swic_sqi_readPerPort(idx, errFactor);
			if (result == E_NOT_OK) {break;}
		}
	}

	return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_sqi_readPerPort(const uint8 SwitchPortIdx, uint32 * const errFactor)
{
	Std_ReturnType	result = E_NOT_OK;
	uint32			val = 0uL;
	uint8			value;

	do {
		if ((sizeof(G_ETHSWT_SWIC_GET_SQI_TABLE)/sizeof(G_ETHSWT_SWIC_GET_SQI_TABLE[0])) <= SwitchPortIdx)	{ break; }
		if (0uL >= G_ETHSWT_SWIC_GET_SQI_TABLE[SwitchPortIdx].tbl.num)										{ break; }
		result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_GET_SQI_TABLE[SwitchPortIdx].tbl.tbl, G_ETHSWT_SWIC_GET_SQI_TABLE[SwitchPortIdx].tbl.num, &val, errFactor);
		if (E_OK == result) {
			value = (uint8)((val >> G_ETHSWT_SWIC_GET_SQI_TABLE[SwitchPortIdx].sft) & 7uL);
			LIB_DI();
			S_ETHSWT_SWIC_SQI[SwitchPortIdx].SqiValue = value;
			S_ETHSWT_SWIC_SQI[SwitchPortIdx].getSqiResult = result;
			LIB_EI();

			ETHSWT_SWIC_SQI_NOTIFY(SwitchPortIdx, result, value);
		}	/* E_NOT_OK時は、状態遷移時にRAMをリセットする */
	} while(0);

	return result;
}
