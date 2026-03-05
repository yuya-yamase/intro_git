/* -------------------------------------------------------------------------- */
/* file name   : EthDLC_Cfg.c                                            */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include "EthDLC_Cfg.h"
/* -------------------------------------------------------------------------- */
#include <EthDLC.h>
#include <EthDLC_STM.h>
/* 26.2.16 doza Team-B edit sta */
/*#include <chipcom.h>*/
#include <ChipCom.h>
#include <ChipCom_Cfg.h>
/* 26.2.16 doza Team-B edit end */
/* -------------------------------------------------------------------------- */
#define EthDLC_START_SEC_CODE
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
/* Config for EthDLC_STM.c                                                    */
/* -------------------------------------------------------------------------- */
Std_ReturnType EthDLC_Port_GetState (void)
{
	Std_ReturnType	state = STD_ON;
	Std_ReturnType			retc;
	EthTrcv_LinkStateType	linkState;


	retc = EthSwt_SWIC_GetLinkState(D_ETH_SWITCH_DLC, D_ETH_PORT_DLC, &linkState);
	if (retc == E_OK)
	{
		if (linkState != ETHTRCV_LINK_STATE_ACTIVE)
		{
			state = STD_OFF;
		}
	} else {
		state = STD_OFF;    /* 取得できなければDONWとする */
	}

	return state;
}
/* -------------------------------------------------------------------------- */
void EthDLC_Indicate_Cycle(void)
{
	Std_ReturnType doipStart;
	Std_ReturnType txData = STD_OFF;

	doipStart = EthDLC_STM_GetDoIPStart();
	if(doipStart == E_OK) {
		/* ChipComへDoIP起動データセット */
		txData = STD_ON;
		(void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_DOIPMGR_DOIPCOMPWR, sizeof(txData), &txData);

	} else {
		/* ChipComへDoIP停止データセット*/
		(void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_DOIPMGR_DOIPCOMPWR, sizeof(txData), &txData);
	}

	return;
}
/* -------------------------------------------------------------------------- */
#define EthDLC_STOP_SEC_CODE
#include <EthDLC_MemMap.h>
