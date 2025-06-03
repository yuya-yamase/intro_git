/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Reg.h                                          */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_REG_H
#define ETHSWT_SWIC_REG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_initRegCommon.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Reg_Init (void);
void EthSwt_SWIC_Reg_HiProc (void);
Std_ReturnType EthSwt_SWIC_Reg_SetTbl(const swic_reg_data_t tbl[], const uint32 cnt, uint32 * const dat, uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_REG_H */
/* -------------------------------------------------------------------------- */
