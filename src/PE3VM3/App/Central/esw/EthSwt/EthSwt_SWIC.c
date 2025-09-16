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
#include <EthSwt_SWIC_Qci.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Init(const EthSwt_ConfigType *CfgPtr)
{
	(void)CfgPtr;
	EthSwt_SWIC_PWR_Init();
	EthSwt_SWIC_STM_Init();
	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_HiProc(void)
{
	EthSwt_SWIC_STM_HiProc();	
	return;	
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_LoProc(void)
{
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
Std_ReturnType EthSwt_SWIC_GetMIB(uint8 SwitchIdx, uint8 SwitchPortIdx, uint32 Mib, S_ETHSWT_SWIC_MIB_COUNT *MibCountPtr)
{
	if (SwitchIdx != ETHSWT_SWIC_IDX)	{ return E_NOT_OK; }
	return EthSwt_SWIC_MIB_GetMIB(SwitchPortIdx, Mib, MibCountPtr);
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_GetQci(uint8 SwitchIdx, uint32 * const QciInfoPtr)
{
	if (SwitchIdx != ETHSWT_SWIC_IDX)	{ return E_NOT_OK; }
	return EthSwt_SWIC_Qci_Get(QciInfoPtr);
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_PowerOn(void)
{
	EthSwt_SWIC_PWR_PowerOnReq();

	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_PowerOff(void)
{
	EthSwt_SWIC_PWR_PowerOffReq();

	return;
}
#define	ETHSWT_STOP_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
