#ifndef ETHSWT_SWIC_REG_H
#define ETHSWT_SWIC_REG_H
#include <Std_Types.h>
#include <EthSwt_SWIC.h>

void EthSwt_SWIC_Reg_Init(void);
void EthSwt_SWIC_Reg_MainFunction1MS(void);
void EthSwt_SWIC_Reg_BackgroundTask(void);
Std_ReturnType EthSwt_SWIC_Reg_GetLinkState(const uint8 SwitchPortIdx, EthTrcv_LinkStateType * const LinkStatePtr);
Std_ReturnType EthSwt_SWIC_Reg_SetSwitchPortMode(const uint8 SwitchPortIdx, const Eth_ModeType PortMode);
Std_ReturnType EthSwt_SWIC_Reg_GetLoggingFilteringValue(const uint8 SwitchPortIdx, uint32 *const LoggingFilteringValue);
#endif /* ETHSWT_SWIC_REG_H */
