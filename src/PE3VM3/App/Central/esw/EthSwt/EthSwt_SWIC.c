#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC.h>
#include <EthSwt.h>
#include <EthSwt_SWIC_PWR.h>
#include <EthSwt_SWIC_STM.h>
#include <EthSwt_SWIC_Spi.h>
#include <EthSwt_SWIC_Reg.h>
#include <EthSwt_SWIC_Link.h>
#include <EthSwt_SWIC_Port.h>
#include <EthSwt_StubDriver.h> /* Ç†Ç∆Ç≈è¡Ç∑ */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Init(const EthSwt_ConfigType *CfgPtr)
{
	(void)CfgPtr;
	EthSwt_SWIC_PWR_Init();
	EthSwt_SWIC_Spi_Init();
	EthSwt_SWIC_Reg_Init();
	EthSwt_SWIC_Link_Init();
	EthSwt_SWIC_Port_Init();

	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_HiProc(void)
{
	EthSwt_SWIC_Reg_HiProc();		/* TimeÇ∆ÇµÇƒÇ‹Ç∆ÇﬂÇÈÇŸÇ§Ç™ÇÊÇ¢ */
	EthSwt_SWIC_Link_HiProc();		/* TimeÇ∆ÇµÇƒÇ‹Ç∆ÇﬂÇÈÇŸÇ§Ç™ÇÊÇ¢ */
	EthSwt_SWIC_STM_HiProc();	
	return;	
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_LoProc(void)
{
	EthSwt_StubDriver_LoProc();
	EthSwt_SWIC_PWR_LoProc();

	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_BackgroundTask(void)
{
	EthSwt_SWIC_STM_Background();
	return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_GetLinkState(uint8 SwitchIdx, uint8 SwitchPortIdx, EthTrcv_LinkStateType* LinkStatePtr)
{
	if (SwitchIdx != ETHSWT_SWIC_IDX)	{ return E_NOT_OK; }
	return EthSwt_SWIC_Link_GetLinkState(SwitchPortIdx, LinkStatePtr);
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_SetSwitchPortMode(uint8 SwitchIdx, uint8 SwitchPortIdx, Eth_ModeType PortMode)
{
	if (SwitchIdx != ETHSWT_SWIC_IDX)	{ return E_NOT_OK; }
	return EthSwt_SWIC_Port_SetSwitchPortMode(SwitchPortIdx, PortMode);
}
/* -------------------------------------------------------------------------- */
#define	ETHSWT_STOP_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
