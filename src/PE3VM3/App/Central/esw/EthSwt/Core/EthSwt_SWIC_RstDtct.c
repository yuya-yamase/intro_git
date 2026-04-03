/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_RstDtct.c                                        */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include <LIB.h>
#include <Dio.h>
#include <Dio_Symbols.h>
#include "EthSwt_SWIC_Reg.h"
#include "EthSwt_SWIC_Define.h"
#include "EthSwt_SWIC_RstDtct.h"
#include "EthSwt_SWIC_RstDtct_Cfg.h"
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_rstdtct_checkRstReg(uint32* const errFactor);

struct {
	sint32								time;
	volatile uint8						req;
} swicGetRstDtctTimer;
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RstDtct_Init(void)
{
	swicGetRstDtctTimer.time = 0;
	swicGetRstDtctTimer.req = STD_ON;

	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RstDtct_Clear(void)
{
	LIB_DI();
	
	swicGetRstDtctTimer.time = 0;
	swicGetRstDtctTimer.req = STD_ON;
	
	LIB_EI();

	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RstDtct_TimerUpdate(void)
{
	swicGetRstDtctTimer.time = swicGetRstDtctTimer.time + D_ETHSWT_SWIC_PERIOD;
	if (D_ETHSWT_SWIC_RSTDTCT_GET_CYCLE <= swicGetRstDtctTimer.time) {
		swicGetRstDtctTimer.time = swicGetRstDtctTimer.time - D_ETHSWT_SWIC_RSTDTCT_GET_CYCLE;
		swicGetRstDtctTimer.req = STD_ON;
	}

	return;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_rstdtct_checkRstReg(uint32 * const errFactor)
{
	Std_ReturnType result = E_OK;

	for (uint32 i = 0; i < G_ETHSWT_SWIC_RSTDTCT_TABLE_NUM; i++)
	{
		result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_RSTDTCT_TABLE[i].tbl, G_ETHSWT_SWIC_RSTDTCT_TABLE[i].num, NULL_PTR, errFactor);
		if (E_NOT_OK == result && *errFactor != D_ETHSWT_SWIC_ERR_WRONGVALUE) { break; }	/* 異常値読み出しではなく、レジスタアクセスが失敗した場合は、異常中断 */
		if (E_OK == result) { break; }														/* 1つでも正常である場合は、正常中断 */
	}

	if (E_NOT_OK == result && *errFactor == D_ETHSWT_SWIC_ERR_WRONGVALUE)					/* 異常値読み出しで失敗の場合、エラー要因をSWICリセット検出に上書き */
	{
		*errFactor = D_ETHSWT_SWIC_ERR_RESET;
	}

	return result;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_RstDtct_Action(uint32 * const errFactor)
{
	Std_ReturnType result = E_OK;
	Std_ReturnType isNeedDtct = E_NOT_OK;

	LIB_DI();
	uint8 req = swicGetRstDtctTimer.req;
	LIB_EI();

	if (STD_ON == req)
	{
		LIB_DI();
		swicGetRstDtctTimer.req = STD_OFF;
		LIB_EI();

		isNeedDtct = EthSwt_SWIC_RstDtct_IsNeedDtct();
		if (E_OK == isNeedDtct)
		{
			result = ethswt_swic_rstdtct_checkRstReg(errFactor);
		}
	}

	return result;
}
