/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_RegAxsErr.h                                           */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_REGAXSERR_H
#define ETHSWT_SWIC_REGAXSERR_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RegAxsErr_Init (void);
void EthSwt_SWIC_RegAxsErr_TimerUpdate (void);
void EthSwt_SWIC_RegAxsErr_Clear (void);
Std_ReturnType EthSwt_SWIC_RegAxsErr_Action (uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_RegAxsErr_H */
/* -------------------------------------------------------------------------- */
