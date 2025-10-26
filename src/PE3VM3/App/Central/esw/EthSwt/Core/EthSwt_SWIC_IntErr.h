/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_IntErr.h                                         */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_INTERR_H
#define ETHSWT_SWIC_INTERR_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_initRegCommon.h>
#include <EthSwt_SWIC_Cfg.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_IntErr_Init (void);
void EthSwt_SWIC_IntErr_Clear(void);
void EthSwt_SWIC_IntErr_TimerUpdate (void);
Std_ReturnType EthSwt_SWIC_IntErr_Action(uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_INTERR_H */
/* -------------------------------------------------------------------------- */
