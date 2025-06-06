/* -------------------------------------------------------------------------- */
/* file name   : EthDLC_Indicator.h                                           */
/* -------------------------------------------------------------------------- */
#ifndef ETHDLC_INDICATOR_H
#define ETHDLC_INDICATOR_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
void EthDLC_Indicate_Init(void);
void EthDLC_Indicate_DLCOn(void);
void EthDLC_Indicate_DLCOff(void);
#define EthDLC_Indicate_ACTLOn()
#define EthDLC_Indicate_ACTLOff()
/* -------------------------------------------------------------------------- */
#ifndef EthDLC_Indicate_ACTLOn
void EthDLC_Indicate_ACTLOn(void);
#endif /* EthDLC_Indicate_ACTLOn */
#ifndef EthDLC_Indicate_ACTLOff
void EthDLC_Indicate_ACTLOff(void);
#endif /* EthDLC_Indicate_ACTLOff */
/* -------------------------------------------------------------------------- */
#endif/* ETHDLC_INDICATOR_H */
