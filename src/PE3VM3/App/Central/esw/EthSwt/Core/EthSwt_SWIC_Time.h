/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Time.h                                           */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_Time_H
#define ETHSWT_SWIC_Time_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Time_Init(void);
void EthSwt_SWIC_Time_HiProc(void);
uint32 EthSwt_SWIC_Time_GetCurrentTime(void);
uint32 EthSwt_SWIC_Time_GetPastTime(uint32 start);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_TIME_H */
/* -------------------------------------------------------------------------- */
