/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_RstDtct.h                                        */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_RSTDTCT_H
#define ETHSWT_SWIC_RSTDTCT_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_initRegCommon.h>
#include <EthSwt_SWIC_Cfg.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RstDtct_Init (void);
void EthSwt_SWIC_RstDtct_Clear(void);
void EthSwt_SWIC_RstDtct_TimerUpdate(void);
Std_ReturnType EthSwt_SWIC_RstDtct_Action(uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_RSTDTCT_H */
/* -------------------------------------------------------------------------- */
