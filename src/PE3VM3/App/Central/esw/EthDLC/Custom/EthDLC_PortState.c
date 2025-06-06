/* -------------------------------------------------------------------------- */
/* file name   : EthDLC_PortState.c                                           */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <NetworkParameter.h>
/* -------------------------------------------------------------------------- */
/* - OEM Custom --------- */
/* - OEM Custom --------- */
/* -------------------------------------------------------------------------- */
#define EthDLC_START_SEC_CODE
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
Std_ReturnType EthDLC_Port_GetState (void)
{
	Std_ReturnType	state = STD_ON;

/* - OEM Custom --------- */
	Std_ReturnType			retc;
	EthTrcv_LinkStateType	linkState;


	retc = EthSwt_SWIC_GetLinkState(D_ETH_SWITCH_DLC, D_ETH_PORT_DLC, &linkState);
	if (retc == E_OK)
	{
		if (linkState != ETHTRCV_LINK_STATE_ACTIVE)
		{
			state = STD_OFF;
		}
	}
	else
	{	/* Žæ“¾‚Å‚«‚È‚¯‚ê‚ÎDONW‚Æ‚·‚é */
		state = STD_OFF;
	}
/* - OEM Custom --------- */

	return state;
}
/* -------------------------------------------------------------------------- */
void EthDLC_Port_SetActive (void)
{
/* - OEM Custom --------- */
	(void)EthSwt_SWIC_SetSwitchPortMode(D_ETH_SWITCH_DLC, D_ETH_PORT_DLC, ETH_MODE_ACTIVE);
/* - OEM Custom --------- */

	return;
}
/* -------------------------------------------------------------------------- */
void EthDLC_Port_SetInactive (void)
{
/* - OEM Custom --------- */
	(void)EthSwt_SWIC_SetSwitchPortMode(D_ETH_SWITCH_DLC, D_ETH_PORT_DLC, ETH_MODE_DOWN);
/* - OEM Custom --------- */

	return;
}
/* -------------------------------------------------------------------------- */
#define EthDLC_STOP_SEC_CODE
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
