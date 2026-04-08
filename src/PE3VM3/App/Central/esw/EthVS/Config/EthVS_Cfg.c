/* -------------------------------------------------------------------------- */
/* file name   : EthVS_Cfg.c                                                  */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthVS_Cfg.h>
#include <LIB.h>
#include <ivdsh.h>
#include <ChipCom.h>
#include <ChipCom_Cfg.h>
/* -------------------------------------------------------------------------- */
#define ETHVS_CFG_MAC_NWORD                                     (2)
/* -------------------------------------------------------------------------- */
Std_ReturnType EthVS_Cfg_MAC_Update(uint8 * const data, const uint32 size)
{
    Std_ReturnType  result = E_NOT_OK;
    uint8   readResult;
    uint8   macaddress[8];                                  /* MACアドレスは6byteだが、iVDshが4byte単位で読み出すため8byteにしておく */

    LIB_memset((uint8*)&macaddress, 0, sizeof(macaddress));
    readResult = u1_g_iVDshReabyDid(IVDSH_DID_REA_VM1TO3_MAC_ADDRESS, (uint32*)macaddress, (uint16)ETHVS_CFG_MAC_NWORD);

    /* コア間通信のデータ取得できれば、データコピーする */
    if(readResult != IVDSH_NO_REA) {
        LIB_memcpy(data, macaddress, size);                 /* 注意！エンディアン・ビット箇所確認する */
        result = E_OK;
    }
    
    return result;
}
/* -------------------------------------------------------------------------- */
void EthVS_Cfg_MAC_Notify(uint8 * const data, const uint32 size, const uint32 status)
{
    /* 取得状態に関わらずChipComにデータセットする */
    (void)status;   /* QAC対策 */
    (void)ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERMGR_MACADDR, size, data);
    
    return;
}
/* -------------------------------------------------------------------------- */
