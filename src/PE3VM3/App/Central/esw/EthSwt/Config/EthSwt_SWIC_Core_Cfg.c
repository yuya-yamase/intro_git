#include <Std_Types.h>
#include "EthSwt_SWIC_Core_Cfg.h"
/* -------------------------------------------------------------------------- */
/* Common */
const Eth_ModeType G_ETHSWT_SWIC_PORT_MODE[D_ETHSWT_SWIC_PORT_NUM] =
{
    ETH_MODE_DOWN           /* Port9 */
,   ETH_MODE_ACTIVE         /* Port1 */
,   ETH_MODE_ACTIVE         /* Port2 */
,   ETH_MODE_DOWN           /* Port3 */
,   ETH_MODE_DOWN           /* Port4 */
,   ETH_MODE_ACTIVE         /* Port5 */
,   ETH_MODE_DOWN           /* Port6 */
,   ETH_MODE_ACTIVE         /* Port7 */
,   ETH_MODE_ACTIVE         /* Port8 */
};

/* -------------------------------------------------------------------------- */
/* For EthSwt_SWIC_PWR */
#include <Dio.h>
#include <Dio_Symbols.h>
#include <Port_Cfg.h>
#include <Port.h>
void EthSwt_SWIC_PWR_SetGPIOMode(void)
{
    /* - Config: SPI通信ラインをGPIOモードへ変更　------------- */
    Port_SetPinMode( PORT_ID_PORT2_PIN13, PORT_MODE_CFG_P2_13_DO_LO );
    Port_SetPinMode( PORT_ID_PORT2_PIN11, PORT_MODE_CFG_P2_11_DI );
    Port_SetPinMode( PORT_ID_PORT2_PIN14, PORT_MODE_CFG_P2_14_DO_LO );
    Port_SetPinMode( PORT_ID_PORT2_PIN12, PORT_MODE_CFG_P2_12_DO_LO );

    return;
}

void EthSwt_SWIC_PWR_SetSpiMode(void)
{
    /* - Config: SPI通信ラインをSPIモードに変更 ------------- */
    Port_SetPinMode(PORT_ID_PORT2_PIN13, PORT_MODE_CFG_P2_13_MSPI0SO);
    Port_SetPinMode(PORT_ID_PORT2_PIN11, PORT_MODE_CFG_P2_11_MSPI0SI);
    Port_SetPinMode(PORT_ID_PORT2_PIN14, PORT_MODE_CFG_P2_14_MSPI0CSS0);
    Port_SetPinMode(PORT_ID_PORT2_PIN12, PORT_MODE_CFG_P2_12_MSPI0SC);

    return;
}

void EthSwt_SWIC_PWR_PowerOn(void)
{
    /* - Config: SWIC電源ON ------------- */
    /* ETHER_PWR_ENをHigh設定した後に、ETH_U2A_RESET_NをHigh設定 */
    Dio_WriteChannel(DIO_ID_APORT4_CH11, STD_HIGH);
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_HIGH);

    return;
}

void EthSwt_SWIC_PWR_PowerOff(void)
{
    /* - Config: SWIC電源OFF ------------- */
    /* ETH_U2A_RESET_NをLow設定した後に、ETHER_PWR_ENをLow設定 */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_LOW);
    Dio_WriteChannel(DIO_ID_APORT4_CH11, STD_LOW);

    return;
}

void EthSwt_SWIC_PWR_ResetAssert(void)
{
    /* - Config: リセットアサート ------------- */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_LOW);
    
    return;
}

void EthSwt_SWIC_PWR_ResetDeassert(void)
{
    /* - Config: リセットディアサート ------------- */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_HIGH);

    return;
}

/* -------------------------------------------------------------------------- */
/* For EthSwt_SWIC_STM */
#include <Port_Cfg.h>
#include <Port.h>
#include <EthSwt_SWIC_PWR.h>
#include <EthSwt_SWIC_Link.h>
#include <EthSwt_Stub.h> /* あとで消す */

const EthSwt_Func G_ETHSWT_SWIC_ACTIVE_FUNC_LIST[] =
{
    
    {EthSwt_SWIC_Link_TimerUpdate   , EthSwt_SWIC_Link_CheckAction  , EthSwt_SWIC_Link_Action}
};

Std_ReturnType EthSwt_SWIC_STM_CheckAvailable(void)
{
    Std_ReturnType swicAvailable = E_NOT_OK;
    Std_ReturnType swicPowerStatus;
    Std_ReturnType sailResoutN;

    swicPowerStatus = EthSwt_SWIC_PWR_GetSWICPower();
    sailResoutN = Dio_ReadChannel(DIO_ID_PORT8_CH8); /* SAIL_RESOUT_Nも見る */

    if (swicPowerStatus == STD_ON && sailResoutN == STD_ON) {
        swicAvailable = E_OK;
    }

    return swicAvailable;
}

Std_ReturnType EthSwt_SWIC_STM_CanRelay(void)
{
    /* ↓暫定　VISからEthernetチャネル起動電源を受け取る */
    Std_ReturnType ret = E_NOT_OK;
    volatile Std_ReturnType result;
    result = EthSwt_Driver_CheckEthChPwr();
    if (result == STD_ON) {
        ret = E_OK;
    }
    /* ↑暫定　VISからEthernetチャネル起動電源を受け取る */

    return ret;
}
/* -------------------------------------------------------------------------- */
