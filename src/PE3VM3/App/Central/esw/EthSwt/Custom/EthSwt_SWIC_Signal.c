#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Signal.h>
#include <Dio.h>
#include <Dio_Symbols.h>
#include <Port_Cfg.h>
#include <Port.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Signal_GPIOMode(void)
{
    /* - OEM Custom：SPI通信ラインをGPIOモードへ変更 - */
    Port_SetPinMode( PORT_ID_PORT2_PIN11, PORT_MODE_CFG_P2_11_DI );         /* ETHERSW-RXD */
    Port_SetPinMode( PORT_ID_PORT2_PIN12, PORT_MODE_CFG_P2_12_DO_LO );      /* ETHERSW-CLK */
    Port_SetPinMode( PORT_ID_PORT2_PIN13, PORT_MODE_CFG_P2_13_DO_LO );      /* ETHERSW-TXD */
    Port_SetPinMode( PORT_ID_PORT2_PIN14, PORT_MODE_CFG_P2_14_DO_LO );      /* ETHERSW-CS */

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Signal_SPIMode(void)
{
    /* - OEM Custom：SPI通信ラインをSPIモードへ変更 - */
    Port_SetPinMode(PORT_ID_PORT2_PIN11, PORT_MODE_CFG_P2_11_MSPI0SI);      /* ETHERSW-RXD */
    Port_SetPinMode(PORT_ID_PORT2_PIN12, PORT_MODE_CFG_P2_12_MSPI0SC);      /* ETHERSW-CLK */
    Port_SetPinMode(PORT_ID_PORT2_PIN13, PORT_MODE_CFG_P2_13_MSPI0SO);      /* ETHERSW-TXD */
    Port_SetPinMode(PORT_ID_PORT2_PIN14, PORT_MODE_CFG_P2_14_MSPI0CSS0);    /* ETHERSW-CS */

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Signal_PowerOn(void)
{
    /* - OEM Custom：SWIC電源ON - */
    /* ETHER_PWR_ENをHigh設定した後に、ETH_U2A_RESET_NをHigh設定 */
    Dio_WriteChannel(DIO_ID_APORT4_CH11, STD_HIGH);                         /* ETHER_PWR_EN */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_HIGH);                          /* ETH_U2A_RESET_N */

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Signal_PowerOff(void)
{
    /* - OEM Custom：SWIC電源OFF - */
    /* ETH_U2A_RESET_NをLow設定した後に、ETHER_PWR_ENをLow設定 */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_LOW);                           /* ETH_U2A_RESET_N */
    Dio_WriteChannel(DIO_ID_APORT4_CH11, STD_LOW);                          /* ETHER_PWR_EN */

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Signal_ResetAssert(void)
{
    /* - OEM Custom：SWICリセットアサート - */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_LOW);                           /* ETH_U2A_RESET_N */

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Signal_ResetDeassert(void)
{
    /* - OEM Custom：SWICリセットディアサート - */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_HIGH);                          /* ETH_U2A_RESET_N */
}