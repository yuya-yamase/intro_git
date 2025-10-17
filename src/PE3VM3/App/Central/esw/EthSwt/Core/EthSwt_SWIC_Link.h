/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Link.h                                           */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_LINK_H
#define ETHSWT_SWIC_LINK_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Link_Init (void);
void EthSwt_SWIC_Link_TimerUpdate (void);
void EthSwt_SWIC_Link_Clear (void);
Std_ReturnType EthSwt_SWIC_Link_Action (uint32 * const errFactor);
Std_ReturnType EthSwt_SWIC_Link_GetLinkState(const uint8 SwitchPortIdx, EthTrcv_LinkStateType * const LinkStatePtr);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_LINK_H */
/* -------------------------------------------------------------------------- */
