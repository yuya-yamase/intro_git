/* -------------------------------------------------------------------------- */
/* file name   : EthDLC_PortState.h                                           */
/* -------------------------------------------------------------------------- */
#ifndef ETHDLC_PORTSTATE_H
#define ETHDLC_PORTSTATE_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
Std_ReturnType EthDLC_Port_GetState(void);
void EthDLC_Port_SetActive(void);
void EthDLC_Port_SetInactive(void);
/* -------------------------------------------------------------------------- */
#endif/* ETHDLC_PORTSTATE_H */
