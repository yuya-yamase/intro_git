#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Allow.h>
#include <EthSwt_SWIC_PWR.h>
#include <Dio.h>
#include <Dio_Symbols.h>
#include <EthSwt_StubDriver.h>
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Allow_SetRegister(void)
{
    /* - OEM Custom：レジスタ設定が可能な状態か確認する - */
    /* C-DCの場合は、PWRモジュールに加え、SAIL_RESOUT_Nも確認する */
    Std_ReturnType swicAvailable = E_NOT_OK;
    Std_ReturnType swicPowerStatus;
    Std_ReturnType sailResoutN;

    swicPowerStatus = EthSwt_SWIC_PWR_GetSWICPower();
    sailResoutN = Dio_ReadChannel(DIO_ID_PORT8_CH8);

    if (swicPowerStatus == STD_ON && sailResoutN == STD_ON) {
        swicAvailable = E_OK;
    }

    return swicAvailable;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Allow_Relay(void)
{
    /* - OEM Custom：中継が可能な状態か確認する - */

    Std_ReturnType ret = E_NOT_OK;
    volatile Std_ReturnType result;
    result = u1_g_VISPwrGetEthChPwr();
    if (result == STD_ON) {
        ret = E_OK;
    }
    
    return ret;
}
