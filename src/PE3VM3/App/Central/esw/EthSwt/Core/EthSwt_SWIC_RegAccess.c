/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_RegAccess.c                                      */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include "EthSwt_SWIC_RegAccessErr.h"
#include "EthSwt_SWIC_Reg.h"
#include "EthSwt_SWIC_STM.h"
#include "EthSwt_SWIC_RegAccess_Cfg.h"
#include <LIB.h>
#include "EthSwt_SWIC_Time.h"
#include "EthSwt_SWIC_Define.h"
/* -------------------------------------------------------------------------- */
static struct {
	volatile Std_ReturnType			getRegAccessResult;
} S_ETHSWT_SWIC_REGACCESS

static struct {			/* タイマ */
	sint32			time;				/* タイマカウンタ */
	volatile uint8	req;				/* 処理要求 */
} S_ETHSWT_SWIC_REGACCESS_TIMER;

/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_regAccess_read(uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RegAccess_Init (void)/* レジスタアクセスエラー関連データの初期化 */
{
	uint8   idx;

	/* タイマクリア */
	S_ETHSWT_SWIC_REGACCESS_TIMER.time = 0;
	S_ETHSWT_SWIC_REGACCESS_TIMER.req = STD_ON;

	S_ETHSWT_SWIC_REGACCESS.getRegAccessResult         = E_NOT_OK;

	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RegAccess_TimerUpdate (void)
{
	S_ETHSWT_SWIC_REGACCESS_TIMER.time = S_ETHSWT_SWIC_REGACCESS_TIMER.time + D_ETHSWT_SWIC_PERIOD;
	if (D_ETHSWT_SWIC_REGACCESS_GET_CYCLE <= S_ETHSWT_SWIC_REGACCESS_TIMER.time) {
		S_ETHSWT_SWIC_REGACCESS_TIMER.time = S_ETHSWT_SWIC_REGACCESS_TIMER.time - D_ETHSWT_SWIC_REGACCESS_GET_CYCLE;
		S_ETHSWT_SWIC_REGACCESS_TIMER.req = STD_ON;
	}

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RegAccess_Clear (void)/* レジスタアクセスエラー関連データの初期化 */
{
	uint8   idx;

	LIB_DI();

	/* タイマクリア */
	S_ETHSWT_SWIC_REGACCESS_TIMER.time = 0;
	S_ETHSWT_SWIC_REGACCESS_TIMER.req = STD_ON;

	S_ETHSWT_SWIC_REGACCESS.getRegAccessResult         = E_NOT_OK;
	
	LIB_EI();
	
	return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_RegAccess_Action (uint32 * const errFactor)
{
    Std_ReturnType	result = E_OK;
	uint8			req;

	LIB_DI();
	req = S_ETHSWT_SWIC_REGACCESS_TIMER.req;
	LIB_EI();

	if (STD_ON == req) {
		LIB_DI();
		S_ETHSWT_SWIC_REGACCESS_TIMER.req = STD_OFF;
		LIB_EI();
		result = ethswt_swic_regAccess_read(errFactor);
	}

	return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_regAccess_read(uint32 * const errFactor)
{
	Std_ReturnType	result = E_OK;
	uint8			value;


	if(D_ETHSWT_SWIC_ERR_CRC == errFactor)		
		LIB_DI();
		S_ETHSWT_SWIC_REGACCESS.getRegAccessResult = E_NOT_OK;
		LIB_EI();
		result = E_NOT_OK;

	}

	ETHSWT_SWIC_REGACCESS_NOTIFY(result);

	return result;
}
