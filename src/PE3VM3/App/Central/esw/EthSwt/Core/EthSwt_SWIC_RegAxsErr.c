/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_RegAxsErr.c                                      */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include "EthSwt_SWIC_RegAxsErr.h"
#include "EthSwt_SWIC_Reg.h"
#include "EthSwt_SWIC_STM.h"
#include "EthSwt_SWIC_RegAxsErr_Cfg.h"
#include <LIB.h>
#include "EthSwt_SWIC_Time.h"
#include "EthSwt_SWIC_Define.h"
/* -------------------------------------------------------------------------- */
static struct {
	volatile Std_ReturnType			getRegAxsErrResult;
	volatile uint8					RegAxsErrValue;
} S_ETHSWT_SWIC_REGAXSERR

static struct {			/* タイマ */
	sint32			time;				/* タイマカウンタ */
	volatile uint8	req;				/* 処理要求 */
} S_ETHSWT_SWIC_REGAXSERR_TIMER;

/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_sqi_read(uint32 * const errFactor);
static Std_ReturnType ethswt_swic_sqi_readPerPort(const uint8 SwitchPortIdx, uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RegAxsErr_Init (void)/* レジスタアクセスエラー関連データの初期化 */
{
	uint8   idx;

	/* タイマクリア */
	S_ETHSWT_SWIC_REGAXSERR_TIMER.time = 0;
	S_ETHSWT_SWIC_REGAXSERR_TIMER.req = STD_ON;

	S_ETHSWT_SWIC_REGAXSERR.getRegAxsErrResult         = E_NOT_OK;
	S_ETHSWT_SWIC_REGAXSERR.RegAxsErrValue             = 0;

	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RegAxsErr_TimerUpdate (void)
{
	S_ETHSWT_SWIC_REGAXSERR_TIMER.time = S_ETHSWT_SWIC_REGAXSERR_TIMER.time + D_ETHSWT_SWIC_PERIOD;
	if (D_ETHSWT_SWIC_REGAXSERR_GET_CYCLE <= S_ETHSWT_SWIC_REGAXSERR_TIMER.time) {
		S_ETHSWT_SWIC_REGAXSERR_TIMER.time = S_ETHSWT_SWIC_REGAXSERR_TIMER.time - D_ETHSWT_SWIC_REGAXSERR_GET_CYCLE;
		S_ETHSWT_SWIC_REGAXSERR_TIMER.req = STD_ON;
	}

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RegAxsErr_Clear (void)/* レジスタアクセスエラー関連データの初期化 */
{
	uint8   idx;

	LIB_DI();

	/* タイマクリア */
	S_ETHSWT_SWIC_REGAXSERR_TIMER.time = 0;
	S_ETHSWT_SWIC_REGAXSERR_TIMER.req = STD_ON;

	S_ETHSWT_SWIC_REGAXSERR.getRegAxsErrResult         = E_NOT_OK;
	S_ETHSWT_SWIC_REGAXSERR.RegAxsErrValue             = 0;
	
	LIB_EI();
	
	return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_RegAxsErr_Action (uint32 * const errFactor)
{
    Std_ReturnType	result = E_OK;
	uint8			req;

	LIB_DI();
	req = S_ETHSWT_SWIC_REGAXSERR_TIMER.req;
	LIB_EI();

	if (STD_ON == req) {
		LIB_DI();
		S_ETHSWT_SWIC_REGAXSERR_TIMER.req = STD_OFF;
		LIB_EI();
		result = ethswt_swic_regaxserr_read(errFactor);
	}

	return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_regaxserr_read(uint32 * const errFactor)
{
	Std_ReturnType	result = E_NOT_OK;
	uint8			idx;

	if(D_ETHSWT_SWIC_ERR_CRC == errFactor)
		LIB_DI();
		S_ETHSWT_SWIC_REGAXSERR.RegAxsErrValue = value;
		S_ETHSWT_SWIC_REGAXSERR.getRegAxsErrResult = result;
		LIB_EI();

		ETHSWT_SWIC_REGAXSERR_NOTIFY(SwitchPortIdx, result, value);
	}

	return result;
}
