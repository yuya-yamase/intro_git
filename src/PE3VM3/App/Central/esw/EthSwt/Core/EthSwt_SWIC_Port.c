/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Port.c                                           */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include <LIB.h>
#include <EthSwt_SWIC_Port_Cfg.h>
#include "EthSwt_SWIC_Port.h"
#include "EthSwt_SWIC_Reg.h"
#include "EthSwt_SWIC_Define.h"
/* -------------------------------------------------------------------------- */
static struct {
    Eth_ModeType                mode;
    volatile Eth_ModeType       mode_chg;
    volatile uint8              modeChangeRequest;
    volatile uint8              modeChangeIndication;
} swicPort[D_ETHSWT_SWIC_PORT_NUM];
/* -------------------------------------------------------------------------- */
static Std_ReturnType EthSwt_SWIC_Port_ResetSwitchPortMode(uint32 *errFactor);
static Std_ReturnType swic_Reg_SetSwitchPortMode(const uint8 SwitchPortIdx, uint32 * const errFactor);
static Std_ReturnType swic_Reg_SetSwitchPortModeACTIVE(const uint8 SwitchPortIdx, uint32 * const errFactor);
static Std_ReturnType swic_Reg_SetSwitchPortModeDOWN(const uint8 SwitchPortIdx, uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Port_Init (void)
{
    uint8   idx;

    for (idx = 0; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        swicPort[idx].mode                  = G_ETHSWT_SWIC_PORT_DEFINE[idx];
        swicPort[idx].mode_chg              = G_ETHSWT_SWIC_PORT_DEFINE[idx];
        swicPort[idx].modeChangeRequest     = STD_OFF;
        swicPort[idx].modeChangeIndication  = STD_OFF;
    }

    return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Port_RelayOn(uint32 *errFactor)
{    
    Std_ReturnType	result = E_OK;
	uint32			idx;
	uint32			val;

	do {
		for (idx=0U ; idx < SWIC_TBL_NUM(G_ETHSWT_SWIC_RELAY_ON_TABLE) ; idx++) {
			result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_RELAY_ON_TABLE[idx].tbl, G_ETHSWT_SWIC_RELAY_ON_TABLE[idx].num, &val , errFactor);
			if (result == E_NOT_OK) { break; }
		}
		if (result == E_NOT_OK) { break; }

		EthSwt_SWIC_Port_ResetSwitchPortMode(errFactor);
	} while (0);

	return result;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Port_RelayOff(uint32 *errFactor)
{
    Std_ReturnType	result = E_OK;
	uint32			idx;
	uint32			val;

    for (idx=0U ; idx < SWIC_TBL_NUM(G_ETHSWT_SWIC_RELAY_OFF_TABLE) ; idx++) {
        result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_RELAY_OFF_TABLE[idx].tbl, G_ETHSWT_SWIC_RELAY_OFF_TABLE[idx].num, &val , errFactor);
		if (result == E_NOT_OK) { break; }
	}

    return result;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Port_SetSwitchPortMode(const uint8 SwitchPortIdx, const Eth_ModeType PortMode)
{
	// if (swic_Reg_Inf.sts == ETHSWT_SWIC_STATE_UNINIT)	{ return E_NOT_OK; } /* どの状態でも受け付けるように変更 */
    Std_ReturnType ret = E_OK;
	if (SwitchPortIdx >= D_ETHSWT_SWIC_PORT_NUM) {
        ret = E_NOT_OK;
    } else {
        ret = E_OK;
        swicPort[SwitchPortIdx].mode_chg	        = PortMode;
	    swicPort[SwitchPortIdx].modeChangeRequest	= STD_ON;	/* 処理前に複数呼ばれた場合は最新が有効 */
    }
	
	return ret;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Port_Action (uint32 * const errFactor)
{
    Std_ReturnType  result = E_OK;
    uint8           idx;
	uint8			req;

    for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
		LIB_DI();
		req = swicPort[idx].modeChangeRequest;
		LIB_EI();
        if (req != STD_ON) { continue; }
        result = swic_Reg_SetSwitchPortMode(idx, errFactor);
        if (result == E_NOT_OK) {break;}
    }

    return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType EthSwt_SWIC_Port_ResetSwitchPortMode(uint32 *errFactor)
{
	Std_ReturnType	ret = E_OK;
	uint8			idx;

	for (idx = 0; idx < D_ETHSWT_SWIC_PORT_NUM; idx++ ) {
		if (swicPort[idx].mode == G_ETHSWT_SWIC_PORT_DEFINE[idx]) { continue; }	/* 動作モード変更なし */
		switch (swicPort[idx].mode) {
		case ETH_MODE_ACTIVE:
			ret = swic_Reg_SetSwitchPortModeACTIVE(idx, errFactor);
			if (ret != E_OK) { break; }
			break;
		case ETH_MODE_DOWN:
			ret = swic_Reg_SetSwitchPortModeDOWN(idx, errFactor);
			if (ret != E_OK) { break; }
			break;
		default:
			break;
		}
	}

	return ret;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetSwitchPortMode(const uint8 SwitchPortIdx, uint32 * const errFactor)
{
	Eth_ModeType	PortMode;
	Std_ReturnType	result = E_OK;
	LIB_DI();
	swicPort[SwitchPortIdx].modeChangeRequest = STD_OFF;	/* 下との間で割り込まれると同じ状態を通知する */
	PortMode = swicPort[SwitchPortIdx].mode_chg;	/* 問題なければ排他不要 */
	LIB_EI();
	if (swicPort[SwitchPortIdx].mode != PortMode) {
		switch (PortMode) {
		case ETH_MODE_ACTIVE:
			result = swic_Reg_SetSwitchPortModeACTIVE(SwitchPortIdx, errFactor);
			break;
		case ETH_MODE_DOWN:
			result = swic_Reg_SetSwitchPortModeDOWN(SwitchPortIdx, errFactor);
			// swic_Reg_LinkTimSet(SwitchPortIdx, ETHTRCV_LINK_STATE_DOWN, 1u); /* ETH_MODE_DOWNは反応がいいので確認 */  /* ★ 必要？ */
			break;
		default:
			break;
		}
	}
    if (result == E_OK) {
        LIB_DI();
        swicPort[SwitchPortIdx].mode = PortMode;
	    swicPort[SwitchPortIdx].modeChangeIndication = STD_ON;
        LIB_EI();
    } else {
		LIB_DI();
        swicPort[SwitchPortIdx].modeChangeRequest = STD_ON;
		LIB_EI();
    }

    return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetSwitchPortModeACTIVE(const uint8 SwitchPortIdx, uint32 * const errFactor)
{
    Std_ReturnType  result = E_OK;
    uint32          val;

    result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_PHY_ON_TABLE[SwitchPortIdx].tbl, G_ETHSWT_SWIC_PHY_ON_TABLE[SwitchPortIdx].num, &val, errFactor);
    
    return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetSwitchPortModeDOWN(const uint8 SwitchPortIdx, uint32 * const errFactor)
{
    Std_ReturnType  result = E_OK;
    uint32          val;

    result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_PHY_OFF_TABLE[SwitchPortIdx].tbl, G_ETHSWT_SWIC_PHY_OFF_TABLE[SwitchPortIdx].num, &val, errFactor);

	return result;
}