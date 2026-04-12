/* -------------------------------------------------------------------------- */
/* file name   : EthVS_Cfg.h                                                  */
/* -------------------------------------------------------------------------- */
#ifndef ETHVS_CFG_H
#define ETHVS_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthVS_MAC.h>
/* -------------------------------------------------------------------------- */
typedef enum {              /* 確認！外部向けにcfgを分けて.hファイルを作るか。IDとサイズが外部から知りたい情報。 */
    E_ETHVS_MACADDRESS = 0,
    E_ETHVS_ID_NUM
} E_ETHVS_ID_LIST;
/* -------------------------------------------------------------------------- */
typedef struct {
    uint32          id;
    uint32          size;
    void            (*initFunc)();
    void            (*updateFunc)();
    Std_ReturnType  (*getFunc)(uint8*, uint32, uint32*);     /* 引数は、格納先(uint8*)・データサイズ(uint32)・状態(uint8*)で統一 */
} S_ETHVS_CFG_LIST;
/* -------------------------------------------------------------------------- */
static const S_ETHVS_CFG_LIST G_ETHVS_CFG_TABLE[E_ETHVS_ID_NUM] = {
/*      ID                      , size                      , initFunc                  , updateFunc                , getFunc                   */
    {   E_ETHVS_MACADDRESS      , ETHVS_MAC_SIZE            , EthVS_MAC_Init            , EthVS_MAC_Update          , EthVS_MAC_Get             }   /* MACアドレス */
};
/* -------------------------------------------------------------------------- */
void EthVS_Cfg_MAC_Update(uint8 * const data, const uint32 size, uint32 * const status);
void EthVS_Cfg_MAC_Notify(uint8 * const data, const uint32 size, const uint32 status);
/* -------------------------------------------------------------------------- */
#endif/* ETHVS_CFG_H */
