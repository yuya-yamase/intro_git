#ifndef ETHSWT_SWIC_H
#define ETHSWT_SWIC_H
#include <Std_Types.h>
#include <EthSwt_SWIC_Cfg.h>
#include <EthSwt.h>
#include <EthSwt_SWIC_MIB.h>

void EthSwt_SWIC_Init(const EthSwt_ConfigType *CfgPtr);
Std_ReturnType EthSwt_SWIC_SetSwitchPortMode(const uint8 SwitchIdx, const uint8 SwitchPortIdx, const Eth_ModeType PortMode);
Std_ReturnType EthSwt_SWIC_GetLinkState(const uint8 SwitchIdx, const uint8 SwitchPortIdx, EthTrcv_LinkStateType * const LinkStatePtr);
void EthSwt_SWIC_HiProc(void);
void EthSwt_SWIC_LoProc(void);
void EthSwt_SWIC_BackgroundTask(void);
void EthSwt_SWIC_PowerOn(void);
void EthSwt_SWIC_PowerOff(void);
Std_ReturnType EthSwt_SWIC_GetEthSwtState(const uint8 SwitchIdx, EthSwt_StateType * const State);
#endif /*ETHSWT_SWIC_H*/
