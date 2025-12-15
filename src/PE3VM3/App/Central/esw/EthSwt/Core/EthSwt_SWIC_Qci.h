/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_QCI.h                                           */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_QCI_H
#define ETHSWT_SWIC_QCI_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Qci_Init (void);
void EthSwt_SWIC_Qci_TimerUpdate (void);
void EthSwt_SWIC_Qci_Clear (void);
Std_ReturnType EthSwt_SWIC_Qci_ReadDiscard (uint32 * const errFactor);
Std_ReturnType EthSwt_SWIC_Qci_Action (uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_QCI_H */
/* -------------------------------------------------------------------------- */
