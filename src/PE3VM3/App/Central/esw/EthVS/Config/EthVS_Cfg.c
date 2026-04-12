/* -------------------------------------------------------------------------- */
/* file name   : EthVS_Cfg.c                                                  */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthVS.h>
#include <EthVS_Cfg.h>
#include <LIB.h>
#include <ivdsh.h>
#include <ChipCom.h>
#include <ChipCom_Cfg.h>
/* -------------------------------------------------------------------------- */
#define ETHVS_CFG_MAC_NWORD                                     (2)
/* -------------------------------------------------------------------------- */
void EthVS_Cfg_MAC_Update(uint8 * const data, const uint32 size, uint32 * const status)
{
    uint8   iVDshResult;
    uint8   macaddress[8];                                  /* MACアドレスは6byteだが、iVDshが4byte単位で読み出すため8byteにしておく */

    LIB_memset((uint8*)&macaddress, 0, sizeof(macaddress));
    iVDshResult = u1_g_iVDshReabyDid(IVDSH_DID_REA_VM1TO3_MAC_ADDRESS, (uint32*)macaddress, (uint16)ETHVS_CFG_MAC_NWORD);

    /* コア間通信のデータ取得できれば、データコピーする */
    if(iVDshResult != IVDSH_NO_REA) {
        LIB_memcpy(data, macaddress, size);                 /* 注意！エンディアン・ビット箇所確認する */
        *status = ETHVS_STATUS_UNKNOWN;
    }
    
    return;
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
