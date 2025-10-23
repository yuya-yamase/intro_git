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
static struct {			/* タイマ */
	sint32			time;				/* タイマカウンタ */
	volatile uint8	req;				/* 処理要求 */
} swicGetSqiTimer;
static struct {
	volatile Std_ReturnType			getSqiResult; /* 旧 sqi_err */
	volatile uint8					SqiValue;     /* 旧 sqi_val */
} swicSQI[D_ETHSWT_SWIC_PORT_NUM];

/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_sqi_updateSQI (const uint8 SwitchPortIdx, uint32 * const errFactr);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_SQI_Init (void)/* SQI関連データの初期化 */
{
	uint8   idx;

	for (idx = 0; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
		swicSQI[idx].getSqiResult         = E_NOT_OK;
		swicSQI[idx].SqiValue             = 0;
    }
	/* タイマクリア */
	swicGetSqiTimer.time = 0;
	swicGetSqiTimer.req = STD_ON;

	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_SQI_TimerUpdate (void)
{
	swicGetSqiTimer.time = swicGetSqiTimer.time + D_ETHSWT_SWIC_PERIOD;
	if (D_ETHSWT_SWIC_SQI_GET_CYCLE <= swicGetSqiTimer.time) {
		swicGetSqiTimer.time = swicGetSqiTimer.time - D_ETHSWT_SWIC_SQI_GET_CYCLE;
		swicGetSqiTimer.req = STD_ON;
	}

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_SQI_Clear (void)/* SQI関連データの初期化 */
{
	uint8   idx;

	LIB_DI();
	for (idx = 0; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
		swicSQI[idx].getSqiResult         = E_NOT_OK;
		swicSQI[idx].SqiValue             = 0;
    }
	/* タイマクリア */
	swicGetSqiTimer.time = 0;
	swicGetSqiTimer.req = STD_ON;
	LIB_EI();
	
	return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType ethswt_swic_sqi_updateSQI (const uint8 SwitchPortIdx, uint32 * const errFactor)/* SQI値の更新 */
{
	Std_ReturnType result = E_NOT_OK;
	uint32			val = 0uL;
	
	do {
		if ((sizeof(G_ETHSWT_SWIC_GET_SQI_TABLE)/sizeof(G_ETHSWT_SWIC_GET_SQI_TABLE[0])) <= SwitchPortIdx)	{ break; }
		if (0uL >= G_ETHSWT_SWIC_GET_SQI_TABLE[SwitchPortIdx].tbl.num)										{ break; }
        result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_GET_SQI_TABLE[SwitchPortIdx].tbl.tbl, G_ETHSWT_SWIC_GET_SQI_TABLE[SwitchPortIdx].tbl.num, &val, errFactor);
        if (E_OK == result) {
            swicSQI[SwitchPortIdx].SqiValue = (uint8)((val >> G_ETHSWT_SWIC_GET_SQI_TABLE[SwitchPortIdx].sft) & 7uL);
        }
    } while(0);
	swicSQI[SwitchPortIdx].getSqiResult = result;

	return result;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_SQI_Action (uint32 * const errFactor)
{
    Std_ReturnType	result = E_OK;
	uint8			idx;
	uint8			req;

	LIB_DI();
	req = swicGetSqiTimer.req;
	LIB_EI();

	if (STD_ON == req) {
		LIB_DI();
		swicGetSqiTimer.req = STD_OFF;
		LIB_EI();
		for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
			result = ethswt_swic_sqi_updateSQI(idx, errFactor);
			if (E_NOT_OK == result) {break;}
		}
	}

	return result;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_SQI_Get (const uint8 SwitchPortIdx, uint8 * const SQIValuePtr)
{
	Std_ReturnType ret = E_NOT_OK;
    EthSwt_StateType status;
    status = EthSwt_SWIC_STM_GetStatus();

	do {
		if (ETHSWT_STATE_ACTIVE != status)				{ break; }
		if (D_ETHSWT_SWIC_PORT_NUM <= SwitchPortIdx)	{ break; }
		if (NULL_PTR == SQIValuePtr)					{ break; }
		*SQIValuePtr = swicSQI[SwitchPortIdx].SqiValue;
		ret = swicSQI[SwitchPortIdx].getSqiResult;
	} while (0);

	return ret;
}
/* -------------------------------------------------------------------------- */
