/* -------------------------------------------------------------------------- */
/* file name   : EthVS_MAC.c                                                  */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthVS_MAC.h>
#include <EthVS_Cfg.h>
#include <EthVS.h>
#include <LIB.h>
/* -------------------------------------------------------------------------- */
static uint8    G_EthVS_MAC_ADDRESS[ETHVS_MAC_SIZE];
static uint8    G_EthVS_MAC_STATUS;
/* -------------------------------------------------------------------------- */
void EthVS_MAC_Init(void)
{
    LIB_memset((uint8*)&G_EthVS_MAC_ADDRESS, 0, ETHVS_MAC_SIZE);
    G_EthVS_MAC_STATUS = ETHVS_STATUS_INITVALUE;

    return;
}
/* -------------------------------------------------------------------------- */
void EthVS_MAC_Update(void)
{
    Std_ReturnType update;

    update = EthVS_Cfg_MAC_Update(G_EthVS_MAC_ADDRESS, ETHVS_MAC_SIZE);
    if (update == E_OK) {
        /* 更新に成功した場合、UPDATE状態にする */
        G_EthVS_MAC_STATUS = ETHVS_STATUS_UPDATE;
    } else {
        /* 更新に失敗した場合、初期値の状態であれば初期値状態、一度でも更新できていれば過去値状態にする */
        if (G_EthVS_MAC_STATUS != ETHVS_STATUS_INITVALUE) {
            G_EthVS_MAC_STATUS = ETHVS_STATUS_PREVIOUS;
        }
    }

    EthVS_Cfg_MAC_Notify(G_EthVS_MAC_ADDRESS, ETHVS_MAC_SIZE, G_EthVS_MAC_STATUS);

    return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthVS_MAC_Get(uint8 * const data, const uint32 size, uint8 * const status)
{
    LIB_memcpy((uint8*)data, (uint8*)G_EthVS_MAC_ADDRESS, size);
    *status = G_EthVS_MAC_STATUS;

    return E_OK;    /* 取得側がstatusにより使用判断することを期待して、常にE_OKを返す */
}
/* -------------------------------------------------------------------------- */
