/* -------------------------------------------------------------------------- */
/* file name   : EthVS.h                                                      */
/* -------------------------------------------------------------------------- */
#ifndef ETHVS_H
#define ETHVS_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>

#define ETHVS_STATUS_OK             (0U)
#define ETHVS_STATUS_FAIL           (1U)
#define ETHVS_STATUS_UNKNOWN        (2U)
/* -------------------------------------------------------------------------- */
void EthVS_Init(void);
void EthVS_LoProc(void);
Std_ReturnType EthVS_Get(const uint32 id, uint8 * const data, const uint32 size, uint32 * const status);
/* -------------------------------------------------------------------------- */
#endif/* ETHVS_H */
