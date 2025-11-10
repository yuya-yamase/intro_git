/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_PWR.h                                            */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_PWR_H
#define ETHSWT_SWIC_PWR_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_PWR_Init(void);
void EthSwt_SWIC_PWR_LoProc(void);
void EthSwt_SWIC_PWR_ForceOffReq(void);
void EthSwt_SWIC_PWR_ResetReq(void);
Std_ReturnType EthSwt_SWIC_PWR_GetSWICPower(void);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_PWR_H */
/* -------------------------------------------------------------------------- */
