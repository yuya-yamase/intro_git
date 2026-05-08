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
static uint32   G_EthVS_MAC_STATUS;
/* -------------------------------------------------------------------------- */
void EthVS_MAC_Init(void)
{
    LIB_memcpy(G_EthVS_MAC_ADDRESS, D_ETHVS_CFG_MAC_ADDRESS_INIT, ETHVS_MAC_SIZE);
    G_EthVS_MAC_STATUS = D_ETHVS_CFG_MAC_STATUS_INIT;

    return;
}
/* -------------------------------------------------------------------------- */
void EthVS_MAC_Update(void)
{
    EthVS_Cfg_MAC_Update(G_EthVS_MAC_ADDRESS, ETHVS_MAC_SIZE, &G_EthVS_MAC_STATUS);
    EthVS_Cfg_MAC_Notify(G_EthVS_MAC_ADDRESS, ETHVS_MAC_SIZE, G_EthVS_MAC_STATUS);

    return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthVS_MAC_Get(uint8 * const data, const uint32 size, uint32 * const status)
{
    LIB_memcpy((uint8*)data, (uint8*)G_EthVS_MAC_ADDRESS, size);
    *status = G_EthVS_MAC_STATUS;

    return E_OK;    /* éÊìæë§Ç™statusÇ…ÇÊÇËégópîªífÇ∑ÇÈÇ±Ç∆Çä˙ë“ÇµÇƒÅAèÌÇ…E_OKÇï‘Ç∑ */
}
/* -------------------------------------------------------------------------- */
