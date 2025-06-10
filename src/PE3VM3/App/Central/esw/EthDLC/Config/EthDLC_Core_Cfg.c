/* -------------------------------------------------------------------------- */
/* file name   : EthDLC_Core_Cfg.c                                            */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include "EthDLC_Core_Cfg.h"
/* -------------------------------------------------------------------------- */

#define EthDLC_START_SEC_CODE
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
/* Config for EthDLC_STM.c                                                    */
/* -------------------------------------------------------------------------- */
#include <VIS.h>
Std_ReturnType EthDLC_Power_GetState (void)
{
	/* TMC C-DC VISから車両電源基本ステートを取得して判断する	*/
	Std_ReturnType	ret = STD_OFF;
	uint8			getResult;
	uint8			basicState;

	getResult = u1_g_VISPwrGetBasicState(&basicState);

	if (getResult == VIS_COMMUNICATION_OK) {
		if (basicState == VIS_BASICSTATE_RIDING || basicState == VIS_BASICSTATE_POWERON_NORMAL || basicState == VIS_BASICSTATE_POWERON_EMERGENCY) {
			ret = STD_ON;
		}
	}

	return ret;
}
/* -------------------------------------------------------------------------- */
#include <EthDLC.h>
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
#include <chipcom.h>
void EthDLC_Indicate_DLCOn (void)
{
    /* ChipComへDoIP起動データセット*/
	Std_ReturnType txData = STD_ON;
	(void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_DOIPMGR_DOIPCOMPWR, sizeof(txData), &txData);

    return;
}
/* -------------------------------------------------------------------------- */
#include <chipcom.h>
void EthDLC_Indicate_DLCOff (void)
{
    /* ChipComへDoIP停止データセット*/
    Std_ReturnType txData = STD_OFF;
	(void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_DOIPMGR_DOIPCOMPWR, sizeof(txData), &txData);

    return;
}
/* -------------------------------------------------------------------------- */
#include <EthDLC_STM.h>
#include <chipcom.h>
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
