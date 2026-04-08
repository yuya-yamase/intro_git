/* -------------------------------------------------------------------------- */
/* file name   : EthVS.h                                                      */
/* -------------------------------------------------------------------------- */
#ifndef ETHVS_H
#define ETHVS_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>

#define ETHVS_STATUS_INITVALUE              (0U)
#define ETHVS_STATUS_UPDATE                 (1U)
#define ETHVS_STATUS_PREVIOUS               (2U)
/* -------------------------------------------------------------------------- */
void EthVS_Init(void);
void EthVS_LoProc(void);
Std_ReturnType EthVS_Get(const uint32 id, uint8 * const data, const uint32 size, uint8 * const status);
/* -------------------------------------------------------------------------- */
#endif/* ETHVS_H */
