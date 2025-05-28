#include <Std_Types.h>
#include <EthSwt_SWIC.h>
#include <EthSwt.h>

void EthSwt_SWIC_Init(const EthSwt_ConfigType *CfgPtr)
{
	(void)CfgPtr;

}

void EthSwt_SWIC_HiProc(void)
{
	
}

void EthSwt_SWIC_LoProc(void)
{

}

void EthSwt_SWIC_BackgroundTask(void)
{
	
}

Std_ReturnType EthSwt_SWIC_GetLinkState(uint8 SwitchIdx, uint8 SwitchPortIdx, EthTrcv_LinkStateType* LinkStatePtr)
{
	// if (SwitchIdx != ETHSWT_SWIC_IDX)	{ return E_NOT_OK; }
	// return EthSwt_SWIC_Reg_GetLinkState(SwitchPortIdx, LinkStatePtr);
	return E_OK;
}
Std_ReturnType EthSwt_SWIC_SetSwitchPortMode(uint8 SwitchIdx, uint8 SwitchPortIdx, Eth_ModeType PortMode)
{
	// if (SwitchIdx != ETHSWT_SWIC_IDX)	{ return E_NOT_OK; }
	// return EthSwt_SWIC_Reg_SetSwitchPortMode(SwitchPortIdx, PortMode);
	return E_OK;
}

#define	ETHSWT_STOP_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
