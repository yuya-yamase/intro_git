/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Port.h                                           */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_PORT_H
#define ETHSWT_SWIC_PORT_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_initRegCommon.h>
#include <EthSwt_SWIC_Core_Cfg.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Port_Init (void);
Std_ReturnType EthSwt_SWIC_Port_RelayOn(uint32 *errFactor);
Std_ReturnType EthSwt_SWIC_Port_RelayOff(uint32 *errFactor);
Std_ReturnType EthSwt_SWIC_Port_SetSwitchPortMode(const uint8 SwitchPortIdx, const Eth_ModeType PortMode);
Std_ReturnType EthSwt_SWIC_Port_Action (uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_PORT_H */
/* -------------------------------------------------------------------------- */
