/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_RegAccess.h                                           */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_REGACCESS_H
#define ETHSWT_SWIC_REGACCESS_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_RegAccess_Init (void);
void EthSwt_SWIC_RegAccess_TimerUpdate (void);
void EthSwt_SWIC_RegAccess_Clear (void);
void EthSwt_SWIC_RegAccess_RegAccessNotify(const swic_reg_data_t tbl[], const uint32 idx);
Std_ReturnType EthSwt_SWIC_RegAccess_Action (uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_RegAccess_H */
/* -------------------------------------------------------------------------- */
