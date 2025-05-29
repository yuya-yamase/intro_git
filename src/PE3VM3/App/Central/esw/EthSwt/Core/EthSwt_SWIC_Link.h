/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Link.h                                          */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_LINK_H
#define ETHSWT_SWIC_LINK_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Link_Init (void);
void EthSwt_SWIC_Link_HiProc (void);
void EthSwt_SWIC_Link_Clear (void);
void EthSwt_SWIC_Link_TimerUpdate (void);
Std_ReturnType EthSwt_SWIC_Link_CheckAction (void);
Std_ReturnType EthSwt_SWIC_Link_Action (uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_LINK_H */
/* -------------------------------------------------------------------------- */
