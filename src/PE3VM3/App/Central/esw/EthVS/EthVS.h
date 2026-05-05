/* -------------------------------------------------------------------------- */
/* file name   : EthVS.h                                                      */
/* -------------------------------------------------------------------------- */
#ifndef ETHVS_H
#define ETHVS_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#define ETHVS_STATUS_INIT           (0U)        /* 未取得 */
#define ETHVS_STATUS_OK             (1U)        /* 取得成功 */
#define ETHVS_STATUS_FAIL           (2U)        /* 取得失敗 */
#define ETHVS_STATUS_UNKNOWN        (3U)        /* 受信情報不明（使用側で判断） */
/* -------------------------------------------------------------------------- */
void EthVS_Init(void);
void EthVS_LoProc(void);
Std_ReturnType EthVS_Get(const uint32 id, uint8 * const data, const uint32 size, uint32 * const status);
/* -------------------------------------------------------------------------- */
#endif/* ETHVS_H */
