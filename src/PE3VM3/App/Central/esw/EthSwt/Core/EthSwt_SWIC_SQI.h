/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_SQI.h                                           */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_SQI_H
#define ETHSWT_SWIC_SQI_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_SQI_Init (void);
void EthSwt_SWIC_SQI_TimerUpdate (void);
void EthSwt_SWIC_SQI_Clear (void);
Std_ReturnType EthSwt_SWIC_SQI_Action (uint32 * const errFactor);
Std_ReturnType EthSwt_SWIC_SQI_Get (uint8 SwitchPortIdx, uint8 * const SQIValuePtr);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_SQI_H */
/* -------------------------------------------------------------------------- */
