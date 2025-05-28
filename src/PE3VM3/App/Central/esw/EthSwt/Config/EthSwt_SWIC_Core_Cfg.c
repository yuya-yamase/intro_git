#include <Std_Types.h>
#include "EthSwt_SWIC_Core_Cfg.h"
/* -------------------------------------------------------------------------- */
#include <Dio.h>
#include <Dio_Symbols.h>
#include <Port_Cfg.h>
#include <Port.h>

/* For EthSwt_SWIC_PWR */
void EthSwt_SWIC_PWR_PowerOn(void)
{
    /* ETHER_PWR_ENをHigh設定　-> ETH_U2A_RESET_NをHigh設定 */
    Dio_WriteChannel(DIO_ID_APORT4_CH11, STD_HIGH);
    Dio_WriteChannel( DIO_ID_APORT4_CH1, STD_HIGH);

    return;
}

void EthSwt_SWIC_PWR_SetSpiMode(void)
{
    /* SPI通信ラインをSPIモードに変更 */
    Port_SetPinMode(PORT_ID_PORT2_PIN13, PORT_MODE_CFG_P2_13_MSPI0SO);
    Port_SetPinMode(PORT_ID_PORT2_PIN11, PORT_MODE_CFG_P2_11_MSPI0SI);
    Port_SetPinMode(PORT_ID_PORT2_PIN14, PORT_MODE_CFG_P2_14_MSPI0CSS0);
    Port_SetPinMode(PORT_ID_PORT2_PIN12, PORT_MODE_CFG_P2_12_MSPI0SC);

    return;
}
