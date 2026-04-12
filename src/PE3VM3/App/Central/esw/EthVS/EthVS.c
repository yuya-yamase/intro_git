/* -------------------------------------------------------------------------- */
/* file name   : EthVS.c                                                      */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthVS.h>
#include <EthVS_Cfg.h>
/* -------------------------------------------------------------------------- */
void EthVS_Init(void)
{
    /* 車両データ初期化 */
    uint8   id;
    for (id = 0u; id < E_ETHVS_ID_NUM; id++) {
        if(G_ETHVS_CFG_TABLE[id].initFunc != NULL_PTR) {
            G_ETHVS_CFG_TABLE[id].initFunc();
        }
    }

    return;
}
/* -------------------------------------------------------------------------- */
void EthVS_LoProc(void)
{
    /* 車両データ取得 */
    uint8   id;
    for (id = 0u; id < E_ETHVS_ID_NUM; id++) {
        if(G_ETHVS_CFG_TABLE[id].updateFunc != NULL_PTR){
            G_ETHVS_CFG_TABLE[id].updateFunc();
        }
    }

    return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthVS_Get(const uint32 id, uint8 * const data, const uint32 size, uint32 * const status)
{
    Std_ReturnType  result = E_NOT_OK;

    do {
        if (id >= E_ETHVS_ID_NUM)                       { break; }
        if (data == NULL_PTR)                           { break; }
        if (size != G_ETHVS_CFG_TABLE[id].size)         { break; }
        if (status == NULL_PTR)                         { break; }
        if (G_ETHVS_CFG_TABLE[id].getFunc == NULL_PTR)  { break; }

        result = G_ETHVS_CFG_TABLE[id].getFunc(data, size, status);
    } while (0);

    return result;
}
/* -------------------------------------------------------------------------- */
