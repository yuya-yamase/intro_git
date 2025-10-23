#ifndef ETHSWT_SWIC_H
#define ETHSWT_SWIC_H
#include <Std_Types.h>
#include <EthSwt_SWIC_Cfg.h>
#include <EthSwt.h>
#include <EthSwt_SWIC_MIB.h>

void EthSwt_SWIC_Init(const EthSwt_ConfigType *CfgPtr);
Std_ReturnType EthSwt_SWIC_SetSwitchPortMode(uint8 SwitchIdx, uint8 SwitchPortIdx, Eth_ModeType PortMode);
Std_ReturnType EthSwt_SWIC_GetLinkState(uint8 SwitchIdx, uint8 SwitchPortIdx, EthTrcv_LinkStateType *LinkStatePtr);
Std_ReturnType EthSwt_SWIC_GetMIB(uint8 SwitchIdx, uint8 SwitchPortIdx, uint32 Mib, uint32 *MibCountPtr);
Std_ReturnType EthSwt_SWIC_GetQci(uint8 SwitchIdx, uint8 QciId, uint32 * const QciDataPtr);
Std_ReturnType EthSwt_SWIC_GetSqi(const uint8 SwitchIdx, const uint8 SwitchPortIdx, uint8 *const SqiValuePtr);
void EthSwt_SWIC_HiProc(void);
void EthSwt_SWIC_LoProc(void);
void EthSwt_SWIC_BackgroundTask(void);
void EthSwt_SWIC_PowerOn(void);
void EthSwt_SWIC_PowerOff(void);
EthSwt_StateType EthSwt_SWIC_GetEthSwtState(uint8 SwitchIdx);
#endif /*ETHSWT_SWIC_H*/
